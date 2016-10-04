#ifndef BAIUSERCACHE_HPP
#define BAIUSERCACHE_HPP

struct lua_State;
#include <memory>
#include <QtCore/qstring.h>
#include <QtCore/qbytearray.h>

namespace baidu {

class BaiDuUserCache {
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

public:
    void setFileName(const QString& /*fileName*/);
    void setFileName(QString&& /*fileName*/);
    void setFileName(QString& /*fileName*/arg) { setFileName(static_cast<const QString&>(arg)); }
    void setFileName(const QString&& /*fileName*/arg) { setFileName(static_cast<const QString&>(arg)); }
    const QString & getFileName() const { return _m_FileName; }
    decltype(auto) fileName() const{ return getFileName();}
private: template<typename _t_FILENAME_t__>
    void _p_setFileName(_t_FILENAME_t__ && /*fileName*/);
};

template<typename _t_FILENAME_t__>
void BaiDuUserCache::_p_setFileName(_t_FILENAME_t__ &&_fileName_){
    _m_FileName=std::forward<_t_FILENAME_t__>(_fileName_);
}

inline void BaiDuUserCache::setFileName(const QString&_fileName_){
    _p_setFileName(_fileName_);
}

inline void BaiDuUserCache::setFileName(QString&&_fileName_){
    _p_setFileName(std::move(_fileName_));
}

}/*namespace baidu*/

#endif // BAIUSERCACHE_HPP
