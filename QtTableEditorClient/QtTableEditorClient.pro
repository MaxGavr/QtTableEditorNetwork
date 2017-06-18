#-------------------------------------------------
#
# Project created by QtCreator 2017-04-26T15:59:06
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtTableEditorClient
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    mainwindow.cpp \
    model/student.cpp \
    manager/manager.cpp \
    table/table.cpp \
    dialogs/adddialog.cpp \
    dialogs/searchdialog.cpp \
    dialogs/searchwidget.cpp \
    dialogs/deletedialog.cpp \
    socket/socketadapter.cpp \
    model/searchpattern.cpp \
    dialogs/serverdialog.cpp

HEADERS  += mainwindow.h \
    model/student.h \
    manager/manager.h \
    table/table.h \
    dialogs/adddialog.h \
    dialogs/searchdialog.h \
    model/searchpattern.h \
    dialogs/searchwidget.h \
    dialogs/deletedialog.h \
    socket/socketadapter.h \
    dialogs/serverdialog.h

RESOURCES += \
    icons.qrc
