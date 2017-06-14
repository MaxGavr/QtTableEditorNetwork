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

    void clientConnected(QString clientAddress) const;

signals:
    void messageString(QString message) const;

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};
