#include "mainwindow.h"
#include "table/table.h"
#include "dialogs/adddialog.h"
#include "dialogs/searchdialog.h"
#include "dialogs/deletedialog.h"
#include "dialogs/serverdialog.h"

#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(DatabaseManager *mng, QWidget *parent)
    : QMainWindow(parent)
{
    setManager(mng);

    createActions();
    createMenus();
    createToolBars();

    table = new MultipageTable(this);
    setCentralWidget(table);
    showMaximized();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    openFileAction = new QAction(QIcon(":/icons/icon_open_file.png"), tr("Открыть файл"), this);
    openFileAction->setShortcut(QKeySequence::Open);
    openFileAction->setStatusTip(tr("Открыть файл с таблицей студентов"));
    connect(openFileAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));

    saveFileAction = new QAction(QIcon(":/icons/icon_save_file.png"), tr("Сохранить файл"), this);
    saveFileAction->setShortcut(QKeySequence::Save);
    saveFileAction->setStatusTip(tr("Сохранить текущую таблицу студентов"));
    connect(saveFileAction, SIGNAL(triggered(bool)), this, SLOT(saveFile()));

    saveAsAction = new QAction(QIcon(":/icons/icon_save_as_file.png"), tr("Сохранить как ..."), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Сохранить текущую таблицу студентов в новый файл"));
    connect(saveAsAction, SIGNAL(triggered(bool)), this, SLOT(saveFileAs()));

    addStudentAction = new QAction(QIcon(":/icons/icon_add.png"), tr("Добавить запись"), this);
    addStudentAction->setShortcut(Qt::Key_1);
    addStudentAction->setStatusTip(tr("Добавить в таблицу новую запись с информацией о студенте"));
    connect(addStudentAction, SIGNAL(triggered(bool)), this, SLOT(showAddDialog()));

    findStudentAction = new QAction(QIcon(":/icons/icon_find.png"), tr("Найти записи"), this);
    findStudentAction->setShortcut(Qt::Key_2);
    findStudentAction->setStatusTip(tr("Найти записи о студентах по заданным критериям"));
    connect(findStudentAction, SIGNAL(triggered(bool)), this, SLOT(showSearchDialog()));

    deleteStudentAction = new QAction(QIcon(":/icons/icon_delete.png"), tr("Удалить записи"), this);
    deleteStudentAction->setShortcut(Qt::Key_3);
    deleteStudentAction->setStatusTip(tr("Найти и удалить записи о студентах по заданным критериям"));
    connect(deleteStudentAction, SIGNAL(triggered(bool)), this, SLOT(showDeleteDialog()));

    connectToServerAction = new QAction(tr("Подключиться к серверу"), this);
    //connectToServerAction->setShortcut();
    connectToServerAction->setStatusTip(tr("Подключиться к удаленному серверу"));
    connect(connectToServerAction, SIGNAL(triggered(bool)), this, SLOT(showServerDialog()));

    aboutQtAction = new QAction(tr("О Qt"), this);
    aboutQtAction->setStatusTip(tr("Показать справочную информацию о библиотеке Qt"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("Файл"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(saveAsAction);

    editMenu = menuBar()->addMenu(tr("Редактировать"));
    editMenu->addAction(addStudentAction);
    editMenu->addAction(findStudentAction);
    editMenu->addAction(deleteStudentAction);
    editMenu->addAction(connectToServerAction);

    helpMenu = menuBar()->addMenu(tr("Справка"));
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBars()
{
    fileToolBar = new QToolBar(tr("Работа с файлом"));
    fileToolBar->setIconSize(QSize(40, 40));
    fileToolBar->addAction(openFileAction);
    fileToolBar->addAction(saveFileAction);
    fileToolBar->addAction(saveAsAction);
    addToolBar(fileToolBar);

    editToolBar = new QToolBar(tr("Редактировать"));
    editToolBar->setIconSize(QSize(40, 40));
    editToolBar->addAction(addStudentAction);
    editToolBar->addAction(findStudentAction);
    editToolBar->addAction(deleteStudentAction);
    editToolBar->addAction(connectToServerAction);
    addToolBar(Qt::LeftToolBarArea, editToolBar);
}

bool MainWindow::saveConfirmation()
{
//    int respond = QMessageBox::warning(this, tr("Сохранить файл"),
//                                       tr("Вы хотите сохранить изменения?"),
//                                       QMessageBox::Yes | QMessageBox::No |
//                                       QMessageBox::Cancel);
//    if (respond == QMessageBox::Yes)
//        return saveFile();
//    else if (respond == QMessageBox::Cancel)
//        return false;
//    return true;
}

void MainWindow::openFile()
{
//    if (saveConfirmation())
//    {
//        QString openFile = QFileDialog::getOpenFileName(this, tr("Открыть файл"),
//                                                        QString(),
//                                                        "Student table (*.xml)");
//        getManager()->loadDatabaseFromFile(openFile);
//        currentFile = openFile;
//    }
}

bool MainWindow::saveFile()
{
//    if (currentFile.isEmpty())
//        return saveFileAs();
//    else
//        return getManager()->saveDatabaseToFile(currentFile);
}

bool MainWindow::saveFileAs()
{
//    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл"),
//                                                    "new_table.xml", "Student table (*.xml)");
//    if (!fileName.isEmpty())
//    {
//        currentFile = fileName;
//        return getManager()->saveDatabaseToFile(currentFile);
//    }
//    else
//        return false;
}

DatabaseManager *MainWindow::getManager() const
{
    return manager;
}

void MainWindow::setManager(DatabaseManager *value)
{
    manager = value;
}

void MainWindow::showAddDialog()
{
    AddStudentDialog dialog(getManager(), this);
    dialog.exec();
}

void MainWindow::showSearchDialog()
{
    SearchStudentDialog dialog(getManager(), this);
    dialog.exec();
}

void MainWindow::showDeleteDialog()
{
    DeleteStudentDialog dialog(getManager(), this);
    dialog.exec();
}

void MainWindow::showServerDialog()
{
    ConnectToServerDialog dialog(getManager(), this);
    dialog.exec();
}
