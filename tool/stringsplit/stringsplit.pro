
QT       += core gui
QT += widgets

TARGET = stringsplit
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.hpp

FORMS    += MainWindow.ui

include($$PWD/../../BaiduTieBaBase.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

