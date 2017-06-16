#include "serverwindow.h"
#include "../server/server.h"

#include <QPushButton>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

ServerWindow::ServerWindow(QWidget *parent)
    : QWidget(parent)
{
    runServerButton = new QPushButton(tr("Запустить"));
    runServerButton->setDefault(true);
    stopServerButton = new QPushButton(tr("Остановить"));
    clearLogButton = new QPushButton(tr("Очистить лог"));

    log = new QPlainTextEdit();
    log->setReadOnly(true);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    QVBoxLayout* mainLayout = new QVBoxLayout();

    buttonsLayout->addWidget(runServerButton);
    buttonsLayout->addWidget(stopServerButton);

    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(log);
    mainLayout->addWidget(clearLogButton);

    setLayout(mainLayout);

    server = new Server();
    connect(runServerButton, SIGNAL(clicked(bool)), server, SLOT(runServer()));
    connect(stopServerButton, SIGNAL(clicked(bool)), server, SLOT(stopServer()));
    connect(server, SIGNAL(serverMessage(QString)), this, SLOT(showMessage(QString)));
    connect(clearLogButton, SIGNAL(clicked(bool)), log, SLOT(clear()));

    showMessage(tr("Добро пожаловать!"));
}

void ServerWindow::showMessage(QString message)
{
    log->appendPlainText(message);
}
