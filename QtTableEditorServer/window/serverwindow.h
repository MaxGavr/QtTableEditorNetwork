#pragma once

#include <QWidget>

class QPushButton;
class QPlainTextEdit;
class QLabel;

class Server;

class ServerWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ServerWindow(QWidget *parent = 0);

public slots:
    void runServer();
    void stopServer();

    void showMessage(QString message);
    void displayServerStatus(QString status);

private:
    QPushButton* runServerButton;
    QPushButton* stopServerButton;
    QPushButton* clearLogButton;
    QLabel* serverStatusLabel;
    QPlainTextEdit* log;

    Server* server;
};
