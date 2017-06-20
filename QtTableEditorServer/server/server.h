#pragma once

#include <QTcpServer>

class ThreadableClientWrapper;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QWidget* parent = 0);

public slots:
    void runServer();
    void stopServer();

    void clientConnected(const QHostAddress& clientAddress, quint16 clientPort);
    void clientDisconnected(const QHostAddress& clientAddress, quint16 clientPort);
    void requestReceived(const QString& request);
    void responseSent(const QString& response);

signals:
    void serverMessage(const QString& message);
    void serverClosed();

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};
