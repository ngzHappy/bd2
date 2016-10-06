/*BaiDuUser hpp*/
#if !defined(____PRAGMA_ONCE_HPP_DATA_BAIDUUSER_0__0x00)
#define ____PRAGMA_ONCE_HPP_DATA_BAIDUUSER_0__0x00() 1

#include <memory>
#include <type_traits>
#include <class/class.hpp>
#include "../BaiDuUserCache.hpp"
#include "../NetworkAccessManager.hpp"
#include "../NetworkCookieJar.hpp"

namespace baidu {

namespace zone_data{

class BaiDuUserData  {
public:
    BaiDuUserData();
    virtual ~BaiDuUserData();
public:
    BaiDuUserCache _m_BaiDuUserCache;
    NetworkAccessManager _m_NetworkAccessManager;
    NetworkCookieJar * _m_NetworkCookieJar=nullptr;
    bool _m_IsLogin=false;
    QByteArray _m_GID;
    std::shared_ptr<BaiDuUser::LoginWithVertifyCode> _m_LoginWithVertifyCode;
private:
    CPLUSPLUS_CLASS_META
};

}

}/*namespace baidu*/

#endif

