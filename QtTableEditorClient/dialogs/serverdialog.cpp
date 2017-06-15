#include "serverdialog.h"
#include "../manager/manager.h"
#include "../socket/socketadapter.h"

#include <QLineEdit>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIntValidator>
#include <QPushButton>
#include <QLabel>
#include <QHostAddress>
#include <QTcpSocket>

ConnectToServerDialog::ConnectToServerDialog(DatabaseManager *mng, QWidget *parent)
    : QDialog(parent)
{
    setManager(mng);

    manageInputFields();
    manageButtons();
    manageLayouts();
}

DatabaseManager *ConnectToServerDialog::getManager() const
{
    return m_manager;
}

void ConnectToServerDialog::setManager(DatabaseManager *value)
{
    m_manager = value;
    if (m_manager)
    {
        connect(m_manager->getSocket()->getSocket(), SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(connectionError(QAbstractSocket::SocketError)));
    }
}

void ConnectToServerDialog::connectToServer()
{
    QString addressString = m_addressInput->text();
    QString portString = m_portInput->text();

    QHostAddress address(addressString);
    int port = portString.toInt();

    if (!address.toIPv4Address())
    {
        showMessage(tr("Введен некорректный адрес"));
        return;
    }
    if (port < 0)
    {
        showMessage(tr("Введен некорректный порт"));
        return;
    }
    getManager()->connectToServer(address, port);
}

void ConnectToServerDialog::showMessage(const QString &message)
{
    m_log->appendPlainText(message);
}

void ConnectToServerDialog::connectionError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        showMessage(tr("Сервер не найден. Проверьте правильность IP-адреса и порта."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        showMessage(tr("В соединении отказано"));
        break;
    default:
        showMessage(tr("Произошла ошибка: %1").arg(getManager()->getSocket()->getSocket()->errorString()));
    }
}

void ConnectToServerDialog::manageInputFields()
{
    m_addressLabel = new QLabel(tr("IP-адрес:"));

    m_addressInput = new QLineEdit();
    // TODO: ip-address validator
    m_addressInput->setInputMask("000.000.000.000;_");
    //m_addressInput->setPlaceholderText(tr("Введите IP-адрес сервера..."));

    m_portLabel = new QLabel(tr("Порт:"));

    m_portInput = new QLineEdit();
    m_portInput->setValidator(new QIntValidator());
    //m_addressInput->setPlaceholderText(tr("Введите порт сервера..."));

    m_log = new QPlainTextEdit();
    m_log->setReadOnly(true);
}

void ConnectToServerDialog::manageButtons()
{
    m_connectButton = new QPushButton(tr("Подключиться"));
    connect(m_connectButton, SIGNAL(clicked(bool)), this, SLOT(connectToServer()));
    m_connectButton->setDefault(true);

    m_cancelButton = new QPushButton(tr("Отмена"));
    connect(m_cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void ConnectToServerDialog::manageLayouts()
{
    QHBoxLayout* inputLayout = new QHBoxLayout();
    inputLayout->addWidget(m_addressLabel);
    inputLayout->addWidget(m_addressInput);
    inputLayout->addWidget(m_portLabel);
    inputLayout->addWidget(m_portInput);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(m_connectButton);
    buttonsLayout->addWidget(m_cancelButton);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(m_log);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
}
