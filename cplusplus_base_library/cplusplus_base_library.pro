
QT -= core gui
QMAKE_CXXFLAGS += -ftemplate-depth=4100

TARGET = cplusplus_base_library
TEMPLATE = lib

DEFINES += CPLUSPLUS_BASE_LIBRARY_LIBRARY

include( $$PWD/cplusplus_base_library.pri )

include($$PWD/../BaiduTieBaBase.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

SOURCES += \
    $$PWD/source_cplusplus_base_library/source_cpp_global.cpp








