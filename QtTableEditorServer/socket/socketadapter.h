#pragma once

#include <QObject>

class QTcpSocket;

class TcpSocketAdapter : public QObject
{
    Q_OBJECT
public:
    TcpSocketAdapter(QTcpSocket* socket, QObject *parent = 0);

    enum REQUESTS {RESPOND = 0,
                   ADD_STUDENT, SEARCH_STUDENTS, REMOVE_STUDENTS,
                   GET_PAGE, COUNT_PAGES, VALIDATE_PAGE,
                   DATABASE_UPDATED,
                   SAVE_DATABASE, LOAD_DATABASE,
                   INVALID_INSERTION, DUPLICATE_INSERTION};

    void sendRequest(TcpSocketAdapter::REQUESTS requestId, QString data);

    QTcpSocket* getSocket();

signals:
    void requestReceived(TcpSocketAdapter::REQUESTS requestId, QString data) const;

public slots:
    void onReadyRead();

private:
    QTcpSocket* m_socket;
    quint16 m_nextBlockSize;
};