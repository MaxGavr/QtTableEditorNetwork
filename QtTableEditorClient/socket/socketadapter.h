#pragma once

#include <QObject>
#include <QTcpSocket>

class TcpSocketAdapter : public QObject
{
    Q_OBJECT
public:
    TcpSocketAdapter(QTcpSocket* socket, QObject *parent = 0);

    enum REQUESTS {ADD_STUDENT, SEARCH_STUDENTS, REMOVE_STUDENTS,
                   GET_PAGE, COUNT_PAGES, VALIDATE_PAGE,
                   DATABASE_UPDATED, STUDENTS_DELETED,
                   SAVE_DATABASE, LOAD_DATABASE, LOAD_FILES,
                   INVALID_INSERTION, DUPLICATE_INSERTION};

    void sendRequest(TcpSocketAdapter::REQUESTS requestId, QString data = QString());

    QTcpSocket* getSocket();

signals:
    void requestReceived(TcpSocketAdapter::REQUESTS requestId, QString data) const;

public slots:
    void onReadyRead();

private:
    QTcpSocket* m_socket;
    quint16 m_nextBlockSize;
};
