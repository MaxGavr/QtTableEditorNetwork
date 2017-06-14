#include "serverwindow.h"
#include "../server/server.h"

#include <QPushButton>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

ServerWindow::ServerWindow(QWidget *parent)
    : QWidget(parent)
{
    runServerButton = new QPushButton(tr("Run server"));
    runServerButton->setDefault(true);
    stopServerButton = new QPushButton(tr("Stop server"));

    log = new QPlainTextEdit();
    log->setReadOnly(true);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    QVBoxLayout* mainLayout = new QVBoxLayout();

    buttonsLayout->addWidget(runServerButton);
    buttonsLayout->addWidget(stopServerButton);

    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(log);

    setLayout(mainLayout);

    server = new Server();
    connect(runServerButton, SIGNAL(clicked(bool)), server, SLOT(runServer()));
    connect(stopServerButton, SIGNAL(clicked(bool)), server, SLOT(stopServer()));
    connect(server, SIGNAL(messageString(QString)), this, SLOT(showMessage(QString)));

    showMessage(tr("Welcome!"));
}

void ServerWindow::showMessage(QString message)
{
    log->appendPlainText(message);
}



