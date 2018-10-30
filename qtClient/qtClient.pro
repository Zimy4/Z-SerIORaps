#-------------------------------------------------
#
# Project created by QtCreator 2016-10-21T18:37:10
#
#-------------------------------------------------

QT       += core gui network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    ../qtMainServer/qtMainServer/globalcfg.h

FORMS    += mainwindow.ui
