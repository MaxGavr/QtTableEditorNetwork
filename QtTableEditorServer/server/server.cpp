#include "server.h"
#include "clientwrapper.h"

#include <QNetworkInterface>
#include <QMessageBox>
#include <QThread>

Server::Server(QWidget *parent)
    :QTcpServer(parent)
{

}

void Server::runServer()
{
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    foreach (QHostAddress ipAddress, ipAddressesList)
    {
        if (ipAddress != QHostAddress::LocalHost && ipAddress.toIPv4Address())
        {
            if (!listen(ipAddress))
            {
                emit messageString(tr("Unable to start server: %1").arg(errorString()));
                stopServer();
            }
            else
            {
                emit messageString(tr("Server started successfully. Address: %1. Port: %2")
                                   .arg(serverAddress().toString())
                                   .arg(QString::number(serverPort())));
            }
        }
    }
}

void Server::stopServer()
{
    close();
    emit messageString(tr("Server stopped successfully."));
}

void Server::clientConnected(QString clientAddress) const
{
    emit messageString(tr("Client connected. Address: %1").arg(clientAddress));
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    ThreadableClientWrapper* client = new ThreadableClientWrapper(socketDescriptor);
    QThread* clientThread = new QThread();
    client->moveToThread(clientThread);

    connect(clientThread, SIGNAL(started()), client, SLOT(run()));
    connect(client, SIGNAL(finished()), clientThread, SLOT(quit()));
    connect(client, SIGNAL(finished()), client, SLOT(deleteLater()));
    connect(client, SIGNAL(finished()), clientThread, SLOT(deleteLater()));

    connect(client, SIGNAL(clientConnected(QString)), this, SLOT(clientConnected(QString)));

    clientThread->start();
    emit messageString(tr("Client connected"));
}

