#ifndef BAIUSERCACHE_HPP
#define BAIUSERCACHE_HPP

struct lua_State;
#include <memory>
#include <QtCore/qstring.h>
#include <QtCore/qbytearray.h>
#include <memory/MemoryLibrary.hpp>
#include "BaiduCoreLibrary.hpp"

namespace baidu {

class BAIDU_CORE_LIBRARYSHARED_EXPORT BaiDuUserCache {
    QString _m_FileName;
    std::shared_ptr<lua_State> _m_L;
    static std::shared_ptr<lua_State> _instance_lua();
public:
    BaiDuUserCache(const QString& argFileName=QString{}):_m_FileName(argFileName) {}
    ~BaiDuUserCache();

public:
    void read();
    void write();

    QString getUserName()const;
    QString getPassWord()const;

    void open();
    void setUserName(const QString&);
    void setPassWord(const QString&);

    bool isOpen() const { return bool(_m_L); }
    static QString userNameToFilePath(const QString&);
    static QString filePathToUserName(const QString&);
public:
    inline void setFileName(const QString& /*fileName*/arg);
    inline void setFileName(QString&& /*fileName*/arg){ _p_setFileName(std::move(arg)); }
    void setFileName(QString& /*fileName*/arg) { setFileName(static_cast<const QString&>(arg)); }
    void setFileName(const QString&& /*fileName*/arg) { setFileName(static_cast<const QString&>(arg)); }
    const QString & getFileName() const { return _m_FileName; }
    decltype(auto) fileName() const{ return getFileName();}
private: template<typename _t_FILENAME_t__>
    void _p_setFileName(_t_FILENAME_t__ && /*fileName*/);
private:
    MEMORY_CLASS_NEW_DELETE
};

template<typename _t_FILENAME_t__>
inline void BaiDuUserCache::_p_setFileName(_t_FILENAME_t__ &&_fileName_){
    _m_FileName=std::forward<_t_FILENAME_t__>(_fileName_);
}

inline void BaiDuUserCache::setFileName(const QString& arg) {
    _p_setFileName(arg);
}

}/*namespace baidu*/

#endif // BAIUSERCACHE_HPP
