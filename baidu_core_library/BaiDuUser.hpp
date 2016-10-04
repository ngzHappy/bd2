/*BaiDuUser hpp*/
#if !defined(____PRAGMA_ONCE_HPP_BAIDUUSER_0___HPP_0x00_)
#define ____PRAGMA_ONCE_HPP_BAIDUUSER_0___HPP_0x00_() 1

#include <memory>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <type_traits>
#include <memory/MemoryLibrary.hpp>
#include "BaiduCoreLibrary.hpp"
#include "BaiDuUserCache.hpp"
#include <QtCore/qstring.h>
#include <QtCore/qbytearray.h>

namespace baidu {

namespace zone_data{
class BaiDuUserData;
}
class BaiDuUser;

template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const BaiDuUser *)->_TYPE_TAG_ ;

class BAIDU_CORE_LIBRARYSHARED_EXPORT BaiDuUser {
public:
    BaiDuUser(const BaiDuUser&)=default;
    BaiDuUser&operator=(const BaiDuUser&)=default;
    BaiDuUser(BaiDuUser&&)=default;
    BaiDuUser&operator=(BaiDuUser&&)=default;
protected:
    using ThisDataType=std::shared_ptr<zone_data::BaiDuUserData>;
    ThisDataType thisData_{nullptr};
    BaiDuUser(ThisDataType && _arg_);
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const BaiDuUser *)->_TYPE_TAG_ ;
    zone_data::BaiDuUserData * thisData();
    const zone_data::BaiDuUserData * thisData() const;
public:
    explicit BaiDuUser(decltype(nullptr)) {}
    BaiDuUser();
    ~BaiDuUser();
public:
    /*如果文件已经打,此函数无效*/
    void open(const QString&/*cache file name*/);
    void close();
    void setUserName(const QString&/*username*/);
    void setPassWord(const QString&/*password*/);
    bool isOpen()const;
    QString getUsername()const;
    QString getPassword()const;
    void login();
    bool isLogin()const;
public:
    void openUserName(const QString&argUserName) {
        this->open(BaiDuUserCache::userNameToFilePath(argUserName));
        this->setUserName(argUserName);
    }
private:
    MEMORY_CLASS_NEW_DELETE
};

}/*namespace baidu*/


#endif


