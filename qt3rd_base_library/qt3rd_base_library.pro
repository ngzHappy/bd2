QT += core
QT += gui

TARGET = qt3rd_base_library
TEMPLATE = lib

DEFINES*=__BUILD_QT3RD_BASE_LIBRARY=1

include($$PWD/text/text.pri)
include($$PWD/private_qt3rd_base_library/zlib.pri)
include($$PWD/quazip/quazip.pri)
include($$PWD/../BaiduTieBaBase.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

HEADERS += \
    qt3rd_base_library.hpp












