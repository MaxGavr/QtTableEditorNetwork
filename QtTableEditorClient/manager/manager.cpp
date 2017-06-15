#include "manager.h"
#include "../model/searchpattern.h"
#include "../socket/socketadapter.h"

#include <QString>
#include <QDate>
#include <QTcpSocket>
#include <QHostAddress>

DatabaseManager::DatabaseManager()
{
    m_socket = new TcpSocketAdapter(new QTcpSocket());
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
    //return database->getXmlHandler()->writeToFile(fileName);
}

bool DatabaseManager::loadDatabaseFromFile(const QString &fileName)
{
    //return database->getXmlHandler()->readFromFile(fileName);
}

void DatabaseManager::addStudent(const QString &first, const QString &second, const QString &middle,
                                 const QDate &birth, const QDate &enrollment, const QDate &graduation)
{
    //database->addStudent(Student(first, second, middle, birth, enrollment, graduation));
}

void DatabaseManager::setSearchPattern(const StudentSearchPattern &pattern)
{
    //database->setSearchPattern(pattern);
}

void DatabaseManager::deleteStudents(const StudentSearchPattern &pattern)
{
    //database->removeStudents(pattern);
}

void DatabaseManager::resetSearchPattern()
{
    //database->setSearchPattern(StudentSearchPattern());
}
