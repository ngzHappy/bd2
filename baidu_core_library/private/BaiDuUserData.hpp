/*BaiDuUser hpp*/
#if !defined(____PRAGMA_ONCE_HPP_DATA_BAIDUUSER_0__0x00)
#define ____PRAGMA_ONCE_HPP_DATA_BAIDUUSER_0__0x00() 1

#include <memory>
#include <type_traits>
#include <memory/MemoryLibrary.hpp>
#include "BaiDuUserCache.hpp"

namespace baidu {

namespace zone_data{

class BaiDuUserData  {
public:
    BaiDuUserData();
    virtual ~BaiDuUserData();
public:
    BaiDuUserCache _m_BaiDuUserCache;
private:
    MEMORY_CLASS_NEW_DELETE
};

}

}/*namespace baidu*/

#endif

