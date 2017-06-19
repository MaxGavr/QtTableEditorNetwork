#pragma once

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QApplication>

#include "manager/manager.h"

class MultipageTable;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DatabaseManager *mng, QWidget *parent = 0);
    ~MainWindow();

    DatabaseManager *getManager() const;
    void setManager(DatabaseManager *value);

    void createActions();
    void createMenus();
    void createToolBars();

public slots:
    void openFile();
    void saveFile();
    void saveFileAs();
    void showAddDialog();
    void showSearchDialog();
    void showDeleteDialog();
    void showServerDialog();

private slots:
    void lostConnection();
    void connectionEstablished();

private:
    bool saveConfirmation();

    MultipageTable *table;

    DatabaseManager *manager;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;

    QString currentFile;
    QAction *openFileAction;
    QAction *saveFileAction;
    QAction *saveAsAction;

    QAction *addStudentAction;
    QAction *findStudentAction;
    QAction *deleteStudentAction;
    QAction *connectToServerAction;
    QAction *aboutQtAction;
};
