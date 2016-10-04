QT += concurrent
QT += core gui
QT += widgets
QT += network

TARGET = test_baidu_login
TEMPLATE = app

DEFINES += THIS_PROJECT_SOURCE_DIR=u8R\\\"_($$PWD)_\\\"

SOURCES += main.cpp\
        MainWindow.cpp \
    BaiDuUserCache.cpp

HEADERS  += MainWindow.hpp \
    BaiDuUserCache.hpp

DEFINES+= THIS_TEST_DIR=$$PWD/login_info

include($$PWD/../../BaiduTieBaBase.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../../cplusplus_base_library/cplusplus_base_library.pri)
LIBS += -L$$THIS_PROJECT_DESTDIR -lcplusplus_base_library

include($$PWD/../../qt3rd_base_library/qt3rd_base_library.pri)
LIBS += -L$$THIS_PROJECT_DESTDIR -lqt3rd_base_library

include($$PWD/../../baidu_core_library/baidu_core_library.pri)
LIBS += -L$$THIS_PROJECT_DESTDIR -lbaidu_core_library

FORMS += \
    MainWindow.ui

DISTFILES += \
    $$PWD/login_info/login_info.lua







