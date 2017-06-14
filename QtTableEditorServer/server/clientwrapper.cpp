#include "clientwrapper.h"
#include "../model/database.h"

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
    socket = new QTcpSocket();
    // error handling needed
    socket->setSocketDescriptor(socketDescriptor);
    emit clientConnected(socket->localAddress().toString());

    database = new StudentDatabase();
}

void ThreadableClientWrapper::stop()
{

}



