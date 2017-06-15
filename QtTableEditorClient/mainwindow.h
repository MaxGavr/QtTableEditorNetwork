#pragma once

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QApplication>

#include "manager/manager.h"
#include "table/table.h"
#include "dialogs/adddialog.h"
#include "dialogs/searchdialog.h"
#include "dialogs/deletedialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const StudentDatabase &db, DatabaseManager *mng, QWidget *parent = 0);
    ~MainWindow();

    DatabaseManager *getManager() const;
    void setManager(DatabaseManager *value);

    void createActions();
    void createMenus();
    void createToolBars();

public slots:
    void openFile();
    bool saveFile();
    bool saveFileAs();
    void showAddDialog();
    void showSearchDialog();
    void showDeleteDialog();

private:
    bool saveConfirmation();

    MultipageTable *table;

    DatabaseManager *manager;
    const StudentDatabase &database;

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
    QAction *aboutQtAction;
};
