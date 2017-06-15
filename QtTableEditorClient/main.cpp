#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StudentDatabase *database = new StudentDatabase();
    DatabaseManager *manager = new DatabaseManager(database);

    MainWindow window(*database, manager);

    window.show();

    return a.exec();
}
