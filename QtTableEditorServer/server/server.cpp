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
    emit serverClosed();
    close();
    emit serverMessage(tr("Сервер успешно остановлен"));
}

void Server::clientConnected(const QHostAddress& clientAddress, quint16 clientPort)
{
    emit serverMessage(tr("Клиент подключился: %1:%2")
                       .arg(clientAddress.toString())
                       .arg(QString::number(clientPort)));
}

void Server::clientDisconnected(const QHostAddress& clientAddress, quint16 clientPort)
{
    emit serverMessage(tr("Клиент отключился: %1:%2").
                       arg(clientAddress.toString()).
                       arg(QString::number(clientPort)));
}

void Server::requestReceived(const QString& request)
{
    auto client = qobject_cast<ThreadableClientWrapper *>(QObject::sender());
    emit serverMessage(tr("[%1:%2] Получен запрос: %3")
                       .arg(client->getClientAddress().toString())
                       .arg(QString::number(client->getClientPort()))
                       .arg(request));
}

void Server::responseSent(const QString &response)
{
    auto client = qobject_cast<ThreadableClientWrapper *>(QObject::sender());
    emit serverMessage(tr("[%1:%2] Отправлен ответ: %3")
                       .arg(client->getClientAddress().toString())
                       .arg(QString::number(client->getClientPort()))
                       .arg(response));
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    ThreadableClientWrapper* client = new ThreadableClientWrapper(socketDescriptor);
    QThread* clientThread = new QThread();
    client->moveToThread(clientThread);

    connect(this, SIGNAL(serverClosed()), client, SLOT(stop()));
    connect(clientThread, SIGNAL(started()), client, SLOT(run()));
    connect(client, SIGNAL(finished()), clientThread, SLOT(quit()));
    connect(client, SIGNAL(finished()), client, SLOT(deleteLater()));
    connect(client, SIGNAL(finished()), clientThread, SLOT(deleteLater()));

    qRegisterMetaType<QHostAddress>();
    connect(client, SIGNAL(clientConnected(QHostAddress,quint16)), this, SLOT(clientConnected(QHostAddress,quint16)));
    connect(client, SIGNAL(clientDisconnected(QHostAddress,quint16)), this, SLOT(clientDisconnected(QHostAddress,quint16)));
    connect(client, SIGNAL(requestReceived(QString)), this, SLOT(requestReceived(QString)));
    connect(client, SIGNAL(responseSent(QString)), this, SLOT(responseSent(QString)));

    clientThread->start();
}

