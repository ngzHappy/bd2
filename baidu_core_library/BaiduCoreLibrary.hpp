#ifndef BAIDU_CORE_LIBRARY_HPP
#define BAIDU_CORE_LIBRARY_HPP

#include "baidu_core_library_global.hpp"
#include <memory/MemoryLibrary.hpp>

class BAIDU_CORE_LIBRARYSHARED_EXPORT BaiduCoreLibrary{
public:
    BaiduCoreLibrary();
    virtual ~BaiduCoreLibrary();
private:
    MEMORY_CLASS_NEW_DELETE
};

#endif // BAIDU_CORE_LIBRARY_HPP









