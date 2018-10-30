#-------------------------------------------------
#
# Project created by QtCreator 2016-10-16T20:22:27
#
#-------------------------------------------------

QT       += core gui network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rpiserver.cpp \
    crpi3serial.cpp

HEADERS  += mainwindow.h \
    rpiserver.h \
    crpi3serial.h

FORMS    += mainwindow.ui
