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

#tool:boost_change_name
tool_boost_change_name.file=$$PWD/cplusplus_base_library/boost_tool/tool_boost_change_name/boost_change_name.pro

SUBDIRS += \
    tool_boost_change_name













