#pragma once

#include <QAbstractSocket>
#include <QDialog>

class QLineEdit;
class QPlainTextEdit;
class QLabel;

class DatabaseManager;

class ConnectToServerDialog : public QDialog
{
    Q_OBJECT
public:
    ConnectToServerDialog(DatabaseManager* mng, QWidget* parent = 0);

    DatabaseManager *getManager() const;
    void setManager(DatabaseManager *value);

private slots:
    void connectToServer();
    void showMessage(const QString& message);
    void connectionError(QAbstractSocket::SocketError socketError);

private:
    void manageInputFields();
    void manageButtons();
    void manageLayouts();

    DatabaseManager* m_manager;

    QLabel* m_addressLabel;
    QLabel* m_portLabel;

    QLineEdit* m_addressInput;
    QLineEdit* m_portInput;

    QPushButton* m_connectButton;
    QPushButton* m_cancelButton;

    QPlainTextEdit* m_log;
};

