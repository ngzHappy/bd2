
QT -= core gui
QMAKE_CXXFLAGS += -ftemplate-depth=4100

TARGET = cplusplus_base_library
TEMPLATE = lib

DEFINES += CPLUSPLUS_BASE_LIBRARY_LIBRARY

include($$PWD/lua/lua_build.pri)
include($$PWD/exception/exception.pri)
include($$PWD/cplusplus_base_library.pri )
include($$PWD/gumbo/gumbo.pri)
include($$PWD/../BaiduTieBaBase.pri)
include($$PWD/memory/source/memory.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

SOURCES += \
    $$PWD/source_cplusplus_base_library/source_cpp_global.cpp

HEADERS += \
    $$PWD/cplusplus_base_library.hpp \
    $$PWD/argument/argument.hpp \
    $$PWD/class/class.hpp \
    $$PWD/function/function.hpp








