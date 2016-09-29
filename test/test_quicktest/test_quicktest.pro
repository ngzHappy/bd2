
QT += core gui
QT += widgets

TARGET = test_quicktest
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    TestStaticPointer.cpp

HEADERS  += MainWindow.hpp \
    TestStaticPointer.hpp


include($$PWD/../../BaiduTieBaBase.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../../cplusplus_base_library/cplusplus_base_library.pri)
LIBS += -L$$THIS_PROJECT_DESTDIR -lcplusplus_base_library

include($$PWD/../../qt3rd_base_library/qt3rd_base_library.pri)
LIBS += -L$$THIS_PROJECT_DESTDIR -lqt3rd_base_library




