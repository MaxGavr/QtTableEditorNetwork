#include "clientwrapper.h"
#include "../model/database.h"
#include "../socket/socketadapter.h"

#include <QTcpSocket>
#include <QHostAddress>

ThreadableClientWrapper::ThreadableClientWrapper(qintptr socketDescriptor, QObject *parent)
    : QObject(parent), socketDescriptor(socketDescriptor)
{

}

ThreadableClientWrapper::~ThreadableClientWrapper()
{
    if (database)
    {
        delete database;
    }
    if (socket)
    {
        delete socket;
    }
}

void ThreadableClientWrapper::run()
{
    QTcpSocket* sock = new QTcpSocket();
    // error handling needed
    sock->setSocketDescriptor(socketDescriptor);
    socket = new TcpSocketAdapter(sock, this);

    emit clientConnected(socket->getSocket()->localAddress().toString(),
                         socket->getSocket()->localPort());

    connect(socket, SIGNAL(requestReceived(TcpSocketAdapter::REQUESTS,QString)),
            this, SLOT(parseRequest(TcpSocketAdapter::REQUESTS,QString)));
    connect(socket->getSocket(), SIGNAL(disconnected()), this, SLOT(socketDisconnected()));

    database = new StudentDatabase();

    connect(database, SIGNAL(studentAdded()), this, SLOT(databaseUpdated()));
    connect(database, SIGNAL(studentDeleted()), this, SLOT(databaseUpdated()));
    connect(database, SIGNAL(studentsDeleted(int)), this, SLOT(studentsDeleted(int)));
    connect(database, SIGNAL(invalidInsertion()), this, SLOT(invalidStudentInserted()));
    connect(database, SIGNAL(duplicateInsertion()), this, SLOT(duplicateStudentInserted()));
}

void ThreadableClientWrapper::stop()
{
    disconnect(socket, SIGNAL(requestReceived(TcpSocketAdapter::REQUESTS,QString)),
               this, SLOT(parseRequest(TcpSocketAdapter::REQUESTS,QString)));
    disconnect(socket->getSocket(), SIGNAL(disconnected()), this, SLOT(stop()));

    disconnect(database, SIGNAL(studentAdded()), this, SLOT(databaseUpdated()));
    disconnect(database, SIGNAL(studentDeleted()), this, SLOT(databaseUpdated()));
    disconnect(database, SIGNAL(studentsDeleted(int)), this, SLOT(studentsDeleted(int)));
    disconnect(database, SIGNAL(invalidInsertion()), this, SLOT(invalidStudentInserted()));
    disconnect(database, SIGNAL(duplicateInsertion()), this, SLOT(duplicateStudentInserted()));

    emit finished();
}

void ThreadableClientWrapper::socketDisconnected()
{
    emit clientDisconnected(socket->getSocket()->localAddress().toString(),
                            socket->getSocket()->localPort());
    stop();
}

void ThreadableClientWrapper::parseRequest(TcpSocketAdapter::REQUESTS requestId, QString data)
{
    using Tcp = TcpSocketAdapter;
    switch (requestId)
    {
    case Tcp::REQUESTS::ADD_STUDENT:
    {
        Student student = Student::fromString(data);
        database->addStudent(student);
        break;
    }
    case Tcp::REQUESTS::SEARCH_STUDENTS:
    {
        StudentSearchPattern pattern = StudentSearchPattern::fromString(data);
        database->setSearchPattern(pattern);
        break;
    }
    case Tcp::REQUESTS::REMOVE_STUDENTS:
    {
        StudentSearchPattern pattern = StudentSearchPattern::fromString(data);
        database->removeStudents(pattern);
        break;
    }
    case Tcp::REQUESTS::GET_PAGE:
    {
        QStringList numbers = data.split(QChar(' '));
        Student::StudentSet page = database->getSetOfStudents(numbers[0].toInt(), numbers[1].toInt());
        socket->sendRequest(Tcp::REQUESTS::GET_PAGE, Student::studentsToString(page));
        break;
    }
    case Tcp::REQUESTS::COUNT_PAGES:
    {
        int studentsPerPage = data.toInt();
        int pages = database->countPages(studentsPerPage);
        socket->sendRequest(Tcp::REQUESTS::COUNT_PAGES, QString::number(pages));
        break;
    }
    case Tcp::REQUESTS::VALIDATE_PAGE:
    {
        QStringList numbers = data.split(QChar(' '));
        bool isValidPage = database->validatePageBounds(numbers[0].toInt(), numbers[1].toInt());
        socket->sendRequest(Tcp::REQUESTS::VALIDATE_PAGE, isValidPage ? "true" : "false");
        break;
    }
    case Tcp::REQUESTS::SAVE_DATABASE:
    {
        QString fileName = data;
        database->getXmlHandler()->writeToFile(fileName);
        break;
    }
    case Tcp::REQUESTS::LOAD_DATABASE:
    {
        QString fileName = data;
        database->getXmlHandler()->readFromFile(fileName);
        break;
    }
    }
}

void ThreadableClientWrapper::databaseUpdated()
{
    socket->sendRequest(TcpSocketAdapter::REQUESTS::DATABASE_UPDATED);
}

void ThreadableClientWrapper::studentsDeleted(int amount)
{
    QString data = QString::number(amount);
    socket->sendRequest(TcpSocketAdapter::REQUESTS::STUDENTS_DELETED, data);
}

void ThreadableClientWrapper::invalidStudentInserted()
{
    socket->sendRequest(TcpSocketAdapter::REQUESTS::INVALID_INSERTION);
}

void ThreadableClientWrapper::duplicateStudentInserted()
{
    socket->sendRequest(TcpSocketAdapter::REQUESTS::DUPLICATE_INSERTION);
}
