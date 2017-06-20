#include "serverwindow.h"
#include "../server/server.h"

#include <QLabel>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTime>

ServerWindow::ServerWindow(QWidget *parent)
    : QWidget(parent)
{
    runServerButton = new QPushButton(tr("Запустить"));
    runServerButton->setDefault(true);
    stopServerButton = new QPushButton(tr("Остановить"));
    clearLogButton = new QPushButton(tr("Очистить лог"));

    log = new QPlainTextEdit();
    log->setReadOnly(true);

    serverStatusLabel = new QLabel(tr("не запущен"));

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    QVBoxLayout* mainLayout = new QVBoxLayout();

    buttonsLayout->addWidget(runServerButton);
    buttonsLayout->addWidget(stopServerButton);

    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(serverStatusLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(log);
    mainLayout->addWidget(clearLogButton);

    setLayout(mainLayout);

    server = new Server();
    connect(runServerButton, SIGNAL(clicked(bool)), this, SLOT(runServer()));
    connect(stopServerButton, SIGNAL(clicked(bool)), this, SLOT(stopServer()));
    connect(server, SIGNAL(serverMessage(QString)), this, SLOT(showMessage(QString)));
    connect(clearLogButton, SIGNAL(clicked(bool)), log, SLOT(clear()));

    showMessage(tr("Добро пожаловать!"));
}

void ServerWindow::runServer()
{
    server->runServer();
    displayServerStatus(QString("запущен: %1:%2")
                        .arg(server->serverAddress().toString())
                        .arg(QString::number(server->serverPort())));
}

void ServerWindow::stopServer()
{
    server->stopServer();
    displayServerStatus("не запущен");
}

void ServerWindow::showMessage(QString message)
{
    log->appendPlainText(QTime::currentTime().toString() + ": " + message);
}

void ServerWindow::displayServerStatus(QString status)
{
    serverStatusLabel->setText(status);
}
