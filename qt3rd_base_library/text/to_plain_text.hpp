#ifndef __TOPLAINTEXT_hpp_0x00
#define __TOPLAINTEXT_hpp_0x00

#include <memory>
#include "../qt3rd_base_library.hpp"

namespace text {

class ToPlainTextAns{
    bool _m_is_old_data;
    union __Data{
        QByteArray new_data;
        const char * old_data_begin;
        const char * old_data_end;
        __Data(){}
        ~__Data(){}
    };
    __Data _m_Data;
public:
    ToPlainTextAns();
    ToPlainTextAns(const char*,const char*);
    ToPlainTextAns(const QByteArray&);
    ToPlainTextAns(QByteArray&&);
    const char * data()const;
    int size()const;
    bool isQByteArray()const{return !_m_is_old_data;}
    QByteArray toQByteArray()const;
    operator bool()const;
public:
    ToPlainTextAns(const ToPlainTextAns&);
    ToPlainTextAns(ToPlainTextAns&&);
    ToPlainTextAns&operator=(const ToPlainTextAns&);
    ToPlainTextAns&operator=(ToPlainTextAns&&);
    ~ToPlainTextAns();
};

/*
 * if text begin with bom remove it and convert text to utf8
 * if text is gzip ungzip and remove bom and convert text to utf8
*/
EXPORT_QT3RD_BASE_LIBRARY QByteArray to_plain_text(const char *,const char *);

ToPlainTextAns::ToPlainTextAns():_m_is_old_data(true){
    _m_Data.old_data_begin=nullptr;
    _m_Data.old_data_end=nullptr;
}

ToPlainTextAns::ToPlainTextAns(const char*argB,const char*argE):_m_is_old_data(true){
    _m_Data.old_data_begin=argB;
    _m_Data.old_data_end=argE;
}

ToPlainTextAns::ToPlainTextAns(const QByteArray&arg):_m_is_old_data(false){
    ::new (&_m_Data.new_data) QByteArray(arg);
}

ToPlainTextAns::ToPlainTextAns(QByteArray&&arg):_m_is_old_data(false){
    ::new (&_m_Data.new_data) QByteArray(std::move(arg));
}

ToPlainTextAns::~ToPlainTextAns(){
    if(_m_is_old_data){return;}
    _m_Data.new_data.~QByteArray();
}

ToPlainTextAns::ToPlainTextAns(const ToPlainTextAns&arg):_m_is_old_data(arg._m_is_old_data){
    if(_m_is_old_data==false){
        ::new (&_m_Data.new_data) QByteArray(arg._m_Data.new_data);
    }else{
        _m_Data.old_data_begin=arg._m_Data.old_data_begin;
        _m_Data.old_data_end=arg._m_Data.old_data_end;
    }
}

ToPlainTextAns::ToPlainTextAns(ToPlainTextAns&&arg):_m_is_old_data(arg._m_is_old_data){
    if(_m_is_old_data==false){
        ::new (&_m_Data.new_data) QByteArray(std::move(arg._m_Data.new_data));
    }else{
        _m_Data.old_data_begin=arg._m_Data.old_data_begin;
        _m_Data.old_data_end=arg._m_Data.old_data_end;
    }
}

ToPlainTextAns&ToPlainTextAns::operator=(const ToPlainTextAns&arg){
    if(this==&arg){return *this;}
    if(arg._m_is_old_data){
        if(this->_m_is_old_data){
            _m_Data.old_data_begin=arg._m_Data.old_data_begin;
            _m_Data.old_data_end=arg._m_Data.old_data_end;
        }else{
            this->_m_is_old_data=true;
            this->_m_Data.new_data.~QByteArray();
            _m_Data.old_data_begin=arg._m_Data.old_data_begin;
            _m_Data.old_data_end=arg._m_Data.old_data_end;
        }
    }else{
        if(this->_m_is_old_data){
            this->_m_is_old_data=false;
            ::new (&_m_Data.new_data) QByteArray(arg._m_Data.new_data);
        }else{
            this->_m_Data.new_data=arg._m_Data.new_data;
        }
    }
    return *this;
}

ToPlainTextAns&ToPlainTextAns::operator=(ToPlainTextAns&&arg){
    if(this==&arg){return *this;}
    if(arg._m_is_old_data){
        if(this->_m_is_old_data){
            _m_Data.old_data_begin=arg._m_Data.old_data_begin;
            _m_Data.old_data_end=arg._m_Data.old_data_end;
        }else{
            this->_m_is_old_data=true;
            this->_m_Data.new_data.~QByteArray();
            _m_Data.old_data_begin=arg._m_Data.old_data_begin;
            _m_Data.old_data_end=arg._m_Data.old_data_end;
        }
    }else{
        if(this->_m_is_old_data){
            this->_m_is_old_data=false;
            ::new (&_m_Data.new_data) QByteArray(std::move(arg._m_Data.new_data));
        }else{
            this->_m_Data.new_data=std::move(arg._m_Data.new_data);
        }
    }
    return *this;
}

const char * ToPlainTextAns::data()const{
    if(this->_m_is_old_data){return this->_m_Data.old_data_begin;}
    else{
        return static_cast<const QByteArray&>(_m_Data.new_data).data();
    }
}

int ToPlainTextAns::size()const{
    if(this->_m_is_old_data){
        return static_cast<int>(_m_Data.old_data_end-_m_Data.old_data_begin);
    }
    else{
        return static_cast<const QByteArray&>(_m_Data.new_data).size();
    }
}

QByteArray ToPlainTextAns::toQByteArray()const{
    if(isQByteArray()){return _m_Data.new_data;}
    return QByteArray(data(),size());
}

ToPlainTextAns::operator bool()const{
    if(_m_is_old_data){
        return _m_Data.old_data_end>_m_Data.old_data_begin;
    }else{
        return !(_m_Data.new_data.isEmpty());
    }
}

}/*text*/

#endif

