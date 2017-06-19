#include "manager.h"
#include "../model/searchpattern.h"

#include <QString>
#include <QDate>
#include <QTcpSocket>
#include <QHostAddress>

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{
    m_socket = new TcpSocketAdapter(new QTcpSocket());
    connect(m_socket, SIGNAL(requestReceived(TcpSocketAdapter::REQUESTS,QString)),
            this, SLOT(parseRequest(TcpSocketAdapter::REQUESTS,QString)));
}

TcpSocketAdapter *DatabaseManager::getSocket()
{
    return m_socket;
}

void DatabaseManager::connectToServer(const QHostAddress& address, int port)
{
    m_socket->getSocket()->abort();
    m_socket->getSocket()->connectToHost(address, port);
}

bool DatabaseManager::saveDatabaseToFile(const QString &fileName)
{
    getSocket()->sendRequest(TcpSocketAdapter::SAVE_DATABASE, fileName);
}

bool DatabaseManager::loadDatabaseFromFile(const QString &fileName)
{
    getSocket()->sendRequest(TcpSocketAdapter::LOAD_DATABASE, fileName);
}

void DatabaseManager::addStudent(const QString &first, const QString &second, const QString &middle,
                                 const QDate &birth, const QDate &enrollment, const QDate &graduation)
{
    Student student(first, second, middle, birth, enrollment, graduation);
    getSocket()->sendRequest(TcpSocketAdapter::ADD_STUDENT, Student::toString(student));
}

void DatabaseManager::getPage(int index, int studentsPerPage)
{
    QString data = QString::number(index) + ' ' + QString::number(studentsPerPage);
    getSocket()->sendRequest(TcpSocketAdapter::GET_PAGE, data);
}

void DatabaseManager::countPages(int studentsPerPage)
{
    getSocket()->sendRequest(TcpSocketAdapter::COUNT_PAGES, QString::number(studentsPerPage));
}

void DatabaseManager::validatePageBounds(int index, int studentsPerPage)
{
    QString data = QString::number(index) + ' ' + QString::number(studentsPerPage);
    getSocket()->sendRequest(TcpSocketAdapter::VALIDATE_PAGE, data);
}

void DatabaseManager::setSearchPattern(const StudentSearchPattern &pattern)
{
    getSocket()->sendRequest(TcpSocketAdapter::SEARCH_STUDENTS,
                             StudentSearchPattern::toString(pattern));
}

void DatabaseManager::deleteStudents(const StudentSearchPattern &pattern)
{
    getSocket()->sendRequest(TcpSocketAdapter::REMOVE_STUDENTS,
                             StudentSearchPattern::toString(pattern));
}

void DatabaseManager::parseRequest(TcpSocketAdapter::REQUESTS requestId, const QString &data)
{
    switch (requestId)
    {
    case TcpSocketAdapter::DATABASE_UPDATED:
    {
        emit databaseUpdated();
        break;
    }
    case TcpSocketAdapter::GET_PAGE:
    {
        Student::StudentSet students = Student::studentsFromString(data);
        emit pageRetrieved(students);
        break;
    }
    case TcpSocketAdapter::INVALID_INSERTION:
    {
        emit invalidStudentInserted();
        break;
    }
    case TcpSocketAdapter::DUPLICATE_INSERTION:
    {
        emit duplicateStudentInserted();
        break;
    }
    case TcpSocketAdapter::COUNT_PAGES:
    {
        emit pageCounted(data.toInt());
        break;
    }
    case TcpSocketAdapter::VALIDATE_PAGE:
    {
        emit pageValidated("true" == data ? true : false);
        break;
    }
    case TcpSocketAdapter::STUDENTS_DELETED:
    {
        emit studentsDeleted(data.toInt());
        break;
    }
    }
}

void DatabaseManager::resetSearchPattern()
{
    setSearchPattern(StudentSearchPattern());
}
