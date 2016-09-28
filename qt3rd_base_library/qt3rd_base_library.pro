QT += core
QT += gui

TARGET = qt3rd_base_library
TEMPLATE = lib

include($$PWD/private_qt3rd_base_library/zlib.pri)
include($$PWD/quazip/quazip.pri)
include($$PWD/../BaiduTieBaBase.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR












