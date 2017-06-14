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

signals:
    void messageString(QString message);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};
