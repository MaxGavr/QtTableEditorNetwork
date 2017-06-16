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
                emit serverMessage(tr("Невозможно запустить сервер: %1").arg(errorString()));
                stopServer();
            }
            else
            {
                emit serverMessage(tr("Сервер успешно запущен по адресу: %1:%2")
                                   .arg(serverAddress().toString())
                                   .arg(QString::number(serverPort())));
            }
        }
    }
}

void Server::stopServer()
{
    close();
    emit serverMessage(tr("Сервер успешно остановлен"));
}

void Server::clientConnected(const QString &clientAddress, int clientPort)
{
    emit serverMessage(tr("Клиент подключился: %1:%2")
                       .arg(clientAddress)
                       .arg(QString::number(clientPort)));
}

void Server::clientDisconnected(const QString &clientAddress, int clientPort)
{
    emit serverMessage(tr("Клиент отключился: %1:%2").
                       arg(clientAddress).
                       arg(QString::number(clientPort)));
}

void Server::requestReceived(const QString& request)
{
    emit serverMessage(tr("Получен запрос: %1").arg(request));
}

void Server::responseSent(const QString &response)
{
    emit serverMessage(tr("Отправлен ответ: %1").arg(response));
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

    connect(client, SIGNAL(clientConnected(QString,int)), this, SLOT(clientConnected(QString,int)));
    connect(client, SIGNAL(clientDisconnected(QString,int)), this, SLOT(clientDisconnected(QString,int)));
    connect(client, SIGNAL(requestReceived(QString)), this, SLOT(requestReceived(QString)));
    connect(client, SIGNAL(responseSent(QString)), this, SLOT(responseSent(QString)));

    clientThread->start();
}

