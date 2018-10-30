#-------------------------------------------------
#
# Project created by QtCreator 2016-11-13T18:43:27
#
#-------------------------------------------------

QT       += core gui network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtMainServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rpi3server.cpp

HEADERS  += mainwindow.h \
    globalcfg.h \
    rpi3server.h

FORMS    += mainwindow.ui
