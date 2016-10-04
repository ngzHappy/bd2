TEMPLATE = app
CONFIG += console

QT += core
QT -= gui

SOURCES += main.cpp
SOURCES += _cpp.cpp
SOURCES += _data.cpp
SOURCES += _function.cpp
SOURCES += _hpp.cpp
SOURCES += run.cpp

include($$PWD/../../BaiduTieBaBase.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

