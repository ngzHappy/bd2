TEMPLATE = subdirs

#.subdir
#Use the specified subdirectory instead of SUBDIRS value.
#.file
#Specify the subproject pro file explicitly. Cannot be used in conjunction with .subdir modifier.
#.depends
#This subproject depends on specified subproject.
#.makefile
#The makefile of subproject. Available only on platforms that use makefiles.
#.target
#Base string used for makefile targets related to this subproject. Available only on platforms that use makefiles.

#baidu_core_library
library_baidu_core_library.file=$$PWD/baidu_core_library/baidu_core_library.pro

#test_baidu_core
test_baidu_core.file=$$PWD/test/test_baidu_core/test_baidu_core.pro
test_baidu_core.depends+=library_baidu_core_library

SUBDIRS += \
    library_baidu_core_library \
    test_baidu_core




