QT -= core
QT -= gui

TARGET = test_memory_new_
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    source_memory_basic.cpp

include($$PWD/../../BaiduTieBaBase.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

INCLUDEPATH+=$$PWD/../../cplusplus_base_library






