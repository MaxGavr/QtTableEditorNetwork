#include "window/serverwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWindow window;
    window.show();

    return a.exec();
}
