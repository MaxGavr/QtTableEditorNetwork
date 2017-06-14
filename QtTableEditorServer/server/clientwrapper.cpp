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

    emit clientConnected(socket->getSocket()->localAddress().toString());

    database = new StudentDatabase();
}

void ThreadableClientWrapper::stop()
{

}
