QT += core
QT += concurrent

QT -= gui

TARGET = boost_change_name
CONFIG += console

TEMPLATE = app

SOURCES += main.cpp

include($$PWD/../../../BaiduTieBaBase.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR


