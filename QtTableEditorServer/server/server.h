#pragma once

#include <QTcpServer>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QWidget* parent = 0);

public slots:
    void runServer();
    void stopServer();

    void clientConnected(const QString& clientAddress, int clientPort);
    void clientDisconnected(const QString& clientAddress, int clientPort);

signals:
    void serverMessage(const QString& message);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};
