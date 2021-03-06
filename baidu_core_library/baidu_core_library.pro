QT += gui
QT += core
QT += script
QT += network
QT += concurrent
CONFIG   += crypto # qca if you have it

TARGET = baidu_core_library
TEMPLATE = lib

DEFINES += BAIDU_CORE_LIBRARY_LIBRARY

HEADERS += BaiduCoreLibrary.hpp\
        baidu_core_library_global.hpp \
    DownLoadThread.hpp \
    private/PrivateDownLoadThread.hpp \
    RunInMainThread.hpp \
    NetworkAccessManager.hpp \
    NetworkCookieJar.hpp \
    BaiDuUser.hpp \
    BaiDuUserCache.hpp

include($$PWD/src/baidu_core_source.pri)

########################################

include($$PWD/../BaiduTieBaBase.pri)
DESTDIR=$$THIS_PROJECT_DESTDIR

include($$PWD/../cplusplus_base_library/cplusplus_base_library.pri)
LIBS += -L$$THIS_PROJECT_DESTDIR -lcplusplus_base_library

include($$PWD/../qt3rd_base_library/qt3rd_base_library.pri)
LIBS += -L$$THIS_PROJECT_DESTDIR -lqt3rd_base_library
