QT += core network serialport
QT -= gui

CONFIG += c++11

TARGET = qtConsoleServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    rpi3server.cpp \
    cstartserver.cpp

HEADERS += \
    rpi3server.h \
    globalcfg.h \
    cstartserver.h
