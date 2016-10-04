﻿/*BaiDuUser hpp*/
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
#include <QtCore/qobject.h>

namespace baidu {

namespace zone_data{
class BaiDuUserData;
}
class BaiDuUser;

template<typename _TYPE_TAG_,unsigned int _N_>
auto getThisData(const BaiDuUser *)->_TYPE_TAG_ ;

class BAIDU_CORE_LIBRARYSHARED_EXPORT BaiDuUser 
    :public QObject
    ,public std::enable_shared_from_this<BaiDuUser>{
    Q_OBJECT

protected:
    using ThisDataType=std::shared_ptr<zone_data::BaiDuUserData>;
    ThisDataType thisData_{nullptr};
    BaiDuUser(ThisDataType && _arg_);
    template<typename _TYPE_TAG_,unsigned int _N_>
    friend auto getThisData(const BaiDuUser *)->_TYPE_TAG_ ;
    zone_data::BaiDuUserData * thisData();
    const zone_data::BaiDuUserData * thisData() const;
public:
    static QByteArray gid();
public:
    class StepNext {
    protected:
    public:
        StepNext()=default;
        virtual ~StepNext()=default;
        virtual void next()=0;
    };

    explicit BaiDuUser(decltype(nullptr)) {}
    BaiDuUser();
    
    static auto instance() {
        return std::shared_ptr<BaiDuUser>(
            new BaiDuUser,[](BaiDuUser*u) {delete u; },
            memory::Allocator<int>{});
    }
public:
    /*如果文件已经打,此函数无效*/
    void open(const QString&/*cache file name*/);
    void close();
    void setUserName(const QString&/*username*/);
    void setPassWord(const QString&/*password*/);
    bool isOpen()const;
    QString getUsername()const;
    QString getPassword()const;
    bool isLogin()const;
    void login()/**/;
public:
    Q_SIGNAL void loginFinished(bool,QString);

public:
    void openUserName(const QString&argUserName) {
        this->open(BaiDuUserCache::userNameToFilePath(argUserName));
        this->setUserName(argUserName);
    }
private:
    BaiDuUser(const BaiDuUser&)=delete;
    BaiDuUser(BaiDuUser&&)=delete;
    BaiDuUser&operator=(const BaiDuUser&)=delete;
    BaiDuUser&operator=(BaiDuUser&&)=delete;
protected:
    ~BaiDuUser();
private:
    MEMORY_CLASS_NEW_DELETE
};

}/*namespace baidu*/

Q_DECLARE_METATYPE(std::shared_ptr<baidu::BaiDuUser::StepNext>)

#endif


