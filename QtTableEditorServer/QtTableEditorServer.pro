#-------------------------------------------------
#
# Project created by QtCreator 2017-06-14T00:05:59
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtTableEditorServer
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
    model/database.cpp \
    model/searchpattern.cpp \
    model/student.cpp \
    model/xmlhandler.cpp \
    server/server.cpp \
    window/serverwindow.cpp

HEADERS  += \
    model/database.h \
    model/searchpattern.h \
    model/student.h \
    model/xmlhandler.h \
    server/server.h \
    window/serverwindow.h
