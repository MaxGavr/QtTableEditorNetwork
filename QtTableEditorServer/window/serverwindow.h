#pragma once

#include <QWidget>

class QPushButton;
class QPlainTextEdit;

class Server;

class ServerWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ServerWindow(QWidget *parent = 0);

public slots:
    void showMessage(QString message);

private:
    QPushButton* runServerButton;
    QPushButton* stopServerButton;
    QPushButton* clearLogButton;
    QPlainTextEdit* log;

    Server* server;
};
