
QT += core gui
QT += widgets
QT += network

CONFIG += console

TARGET = test_quicktest
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    TestStaticPointer.cpp \
    TestCompiler.cpp \
    TestNetWork.cpp \
    NetworkAccessManager.cpp \
    TestGzip.cpp \
    TestGumbo.cpp

HEADERS  += MainWindow.hpp \
    TestStaticPointer.hpp \
    TestCompiler.hpp \
    TestNetWork.hpp \
    NetworkAccessManager.hpp \
    TestGzip.hpp \
    TestGumbo.hpp

DEFINES*=THIS_PROJECT_SOURCE_DIR=\\\"$$PWD\\\"

include($$PWD/../../BaiduTieBaBase.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../../cplusplus_base_library/cplusplus_base_library.pri)
LIBS += -L$$THIS_PROJECT_DESTDIR -lcplusplus_base_library

include($$PWD/../../qt3rd_base_library/qt3rd_base_library.pri)
LIBS += -L$$THIS_PROJECT_DESTDIR -lqt3rd_base_library




