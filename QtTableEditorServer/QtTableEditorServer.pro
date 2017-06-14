#-------------------------------------------------
#
# Project created by QtCreator 2017-06-14T00:05:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtTableEditorServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    model/database.cpp \
    model/searchpattern.cpp \
    model/student.cpp \
    model/xmlhandler.cpp

HEADERS  += mainwindow.h \
    model/database.h \
    model/searchpattern.h \
    model/student.h \
    model/xmlhandler.h
