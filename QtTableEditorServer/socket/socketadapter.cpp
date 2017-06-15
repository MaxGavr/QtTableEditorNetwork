#include "socketadapter.h"

#include <QDataStream>
#include <QTcpSocket>

TcpSocketAdapter::TcpSocketAdapter(QTcpSocket* socket, QObject *parent)
    : QObject(parent), m_socket(socket), m_nextBlockSize(0)
{
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}


void TcpSocketAdapter::sendRequest(TcpSocketAdapter::REQUESTS requestId, QString data)
{
    QByteArray dataBlock;
    QDataStream stream(&dataBlock, QIODevice::ReadWrite);

    stream << quint16(0);
    stream << requestId << data;
    stream.device()->seek(0);
    stream << (quint16)(dataBlock.size() - sizeof(quint16));

    m_socket->write(dataBlock);
}

QTcpSocket *TcpSocketAdapter::getSocket()
{
    return m_socket;
}

void TcpSocketAdapter::onReadyRead()
{
    QDataStream stream(m_socket);
    TcpSocketAdapter::REQUESTS requestId;
    QString data;

    while (true)
    {
        if (0 == m_nextBlockSize)
        {
            if (m_socket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            stream >> m_nextBlockSize;
        }
        else
        {
            if (m_socket->bytesAvailable() < m_nextBlockSize)
            {
                break;
            }
            else
            {
                // probably foolish casting
                int i;
                stream >> i;
                requestId = static_cast<TcpSocketAdapter::REQUESTS>(i);
                stream >> data;

                emit requestReceived(requestId, data);

                m_nextBlockSize = 0;
            }
        }
    }
}
