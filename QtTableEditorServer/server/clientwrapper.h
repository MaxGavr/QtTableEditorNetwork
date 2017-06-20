#pragma once

#include <QObject>
#include <QHostAddress>
Q_DECLARE_METATYPE( QHostAddress)

#include "../socket/socketadapter.h"

class StudentDatabase;

class ThreadableClientWrapper : public QObject
{
    Q_OBJECT
public:
    explicit ThreadableClientWrapper(qintptr socketDescriptor, QObject *parent = 0);
    ~ThreadableClientWrapper();

    TcpSocketAdapter* getSocketAdapter() const;

    QHostAddress getClientAddress() const;
    quint16 getClientPort() const;

signals:
    void finished();
    void clientConnected(const QHostAddress& clientAddress, quint16 clientPort);
    void clientDisconnected(const QHostAddress& clientAddress, quint16 clientPort);
    void requestReceived(const QString& request);
    void responseSent(const QString& response);

public slots:
    void run();
    void stop();
    void socketDisconnected();

    void parseRequest(TcpSocketAdapter::REQUESTS requestId, QString data);

    void databaseUpdated();
    void studentsDeleted(int amount);
    void invalidStudentInserted();
    void duplicateStudentInserted();

private:
    qintptr socketDescriptor;
    TcpSocketAdapter* socket;

    StudentDatabase* database;
};
