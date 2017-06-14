#include "server.h"
#include <QNetworkInterface>
#include <QMessageBox>

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

void Server::incomingConnection(qintptr socketDescriptor)
{

}

