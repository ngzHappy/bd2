#ifndef __HPP_35765_RUNTIME_BASICSHAREDDATA_
#define __HPP_35765_RUNTIME_BASICSHAREDDATA_() 1

#include <memory>
#include <cstddef>
#include <typeinfo>
#include <typeindex>
#include <cinttypes>
#include <type_traits>

namespace runtime {

class string_view {
public:
    const char *data;
    int length;
};

union BasicData {
    /*pointer data*/
    void * _m_void_pointer;
    /*shared pointer data*/
    std::shared_ptr<void> _m_shared_pointer;
    /*pod data*/
    string_view /**/ _m_string_view;
    int /**/ _m_int;
    char /**/ _m_char;
    bool /**/ _m_bool;
    long /**/ _m_long;
    short /**/ _m_short;
    float /**/ _m_float;
    double /**/ _m_double;
    wchar_t /**/ _m_wchar_t;
    char16_t /**/ _m_char16_t;
    char32_t /**/ _m_char32_t;
    long long /**/ _m_long_long;
    long double /**/ _m_long_double;
    signed char /**/ _m_signed_char;
    unsigned int /**/ _m_unsigned_int;
    unsigned char /**/ _m_unsigned_char;
    unsigned long /**/ _m_unsigned_long;
    unsigned short /**/ _m_unsigned_short;
    unsigned long long /**/ _m_unsigned_long_long;
    /*construct*/
    BasicData(const string_view/**/& arg):_m_string_view(arg) {}
    BasicData(const int/**/& arg):_m_int(arg) {}
    BasicData(const char/**/& arg):_m_char(arg) {}
    BasicData(const bool/**/& arg):_m_bool(arg) {}
    BasicData(const long/**/& arg):_m_long(arg) {}
    BasicData(const short/**/& arg):_m_short(arg) {}
    BasicData(const float/**/& arg):_m_float(arg) {}
    BasicData(const double/**/& arg):_m_double(arg) {}
    BasicData(const wchar_t/**/& arg):_m_wchar_t(arg) {}
    BasicData(const char16_t/**/& arg):_m_char16_t(arg) {}
    BasicData(const char32_t/**/& arg):_m_char32_t(arg) {}
    BasicData(const long long/**/& arg):_m_long_long(arg) {}
    BasicData(const long double/**/& arg):_m_long_double(arg) {}
    BasicData(const signed char/**/& arg):_m_signed_char(arg) {}
    BasicData(const unsigned int/**/& arg):_m_unsigned_int(arg) {}
    BasicData(const unsigned char/**/& arg):_m_unsigned_char(arg) {}
    BasicData(const unsigned long/**/& arg):_m_unsigned_long(arg) {}
    BasicData(const unsigned short/**/& arg):_m_unsigned_short(arg) {}
    BasicData(const unsigned long long/**/& arg):_m_unsigned_long_long(arg) {}
    /*void * construct*/
    BasicData(const void * const &arg):_m_void_pointer(const_cast<void*>(arg)) {}
    BasicData(void * const & arg):_m_void_pointer(arg) {}
    BasicData(const decltype(nullptr)&arg):_m_void_pointer(arg) {}
    /*construct and destruct*/
    BasicData() {}
    ~BasicData() {}
    /*shared void*/
    BasicData(std::shared_ptr<void>&&arg) { ::new(&_m_shared_pointer) std::shared_ptr<void>{std::move(arg)}; }
    BasicData(std::shared_ptr<const void>&&arg) {
        ::new(&_m_shared_pointer) std::shared_ptr<void>{
            std::const_pointer_cast<void>(std::move(arg))};
    }
};

class BasicSharedData {
public:
    enum BasicDataType :std::uint8_t {
        basictype_void_pointer,
        basictype_shared_pointer,
        basictype_string_view,
        basictype_int,
        basictype_char,
        basictype_bool,
        basictype_long,
        basictype_short,
        basictype_float,
        basictype_double,
        basictype_wchar_t,
        basictype_char16_t,
        basictype_char32_t,
        basictype_long_long,
        basictype_long_double,
        basictype_signed_char,
        basictype_unsigned_int,
        basictype_unsigned_char,
        basictype_unsigned_long,
        basictype_unsigned_short,
        basictype_unsigned_long_long,
    };
    inline void * _p_get_data() const;
public:
    inline BasicDataType getType() const noexcept(true);
    inline bool isSharedPointer() const noexcept(true);
    inline const std::type_index&getTypeIndex() const noexcept(true);
    inline bool isConst() const noexcept(true);
    inline void * getData() const { return _p_get_data(); }

protected:
    using _T_=std::shared_ptr<void>;
    BasicData _m_data;
    std::type_index _m_type_index;
    BasicDataType _m_type:8;
    bool _m_is_const:1;
    inline void _p_free() { _m_data._m_shared_pointer.~shared_ptr(); }
    inline void _p_try_free() { if (isSharedPointer()) { _p_free(); } }
    inline void _p_clean();
    inline void _p_create(const std::shared_ptr<void>&);
    inline void _p_create(std::shared_ptr<void>&&);
    inline void _p_create(const std::shared_ptr<const void>&);
    inline void _p_create(std::shared_ptr<const void>&&);
    inline void _p_copy_pod(BasicDataType,const BasicData&);
public:
    inline ~BasicSharedData() { _p_try_free(); }
    inline BasicSharedData();
    inline BasicSharedData(const void*&,const std::type_index&);
    inline BasicSharedData(void*&,const std::type_index&);
    inline BasicSharedData(const decltype(nullptr)&);
public:
    inline BasicSharedData(const string_view/**/&);
    inline BasicSharedData(const int/**/&);
    inline BasicSharedData(const char/**/&);
    inline BasicSharedData(const bool/**/&);
    inline BasicSharedData(const long/**/&);
    inline BasicSharedData(const short/**/&);
    inline BasicSharedData(const float/**/&);
    inline BasicSharedData(const double/**/&);
    inline BasicSharedData(const wchar_t/**/&);
    inline BasicSharedData(const char16_t/**/&);
    inline BasicSharedData(const char32_t/**/&);
    inline BasicSharedData(const long long/**/&);
    inline BasicSharedData(const long double/**/&);
    inline BasicSharedData(const signed char/**/&);
    inline BasicSharedData(const unsigned int/**/&);
    inline BasicSharedData(const unsigned char/**/&);
    inline BasicSharedData(const unsigned long/**/&);
    inline BasicSharedData(const unsigned short/**/&);
    inline BasicSharedData(const unsigned long long/**/&);

    inline BasicSharedData(string_view/**/&);
    inline BasicSharedData(int/**/&);
    inline BasicSharedData(char/**/&);
    inline BasicSharedData(bool/**/&);
    inline BasicSharedData(long/**/&);
    inline BasicSharedData(short/**/&);
    inline BasicSharedData(float/**/&);
    inline BasicSharedData(double/**/&);
    inline BasicSharedData(wchar_t/**/&);
    inline BasicSharedData(char16_t/**/&);
    inline BasicSharedData(char32_t/**/&);
    inline BasicSharedData(long long/**/&);
    inline BasicSharedData(long double/**/&);
    inline BasicSharedData(signed char/**/&);
    inline BasicSharedData(unsigned int/**/&);
    inline BasicSharedData(unsigned char/**/&);
    inline BasicSharedData(unsigned long/**/&);
    inline BasicSharedData(unsigned short/**/&);
    inline BasicSharedData(unsigned long long/**/&);
public:
    inline void set(const decltype(nullptr)&) { _p_clean(); }
    inline void setVoid(const void *&,const std::type_index&);
    inline void setVoid(void *&,const std::type_index&);
    inline void set(void *&arg,const std::type_index&argI) { setVoid(arg,argI); }
    inline void set(const void *&arg,const std::type_index&argI) { setVoid(arg,argI); }
    inline void set(const string_view &);
    inline void set(const int &);
    inline void set(const char &);
    inline void set(const bool &);
    inline void set(const long &);
    inline void set(const short &);
    inline void set(const float &);
    inline void set(const double &);
    inline void set(const wchar_t &);
    inline void set(const char16_t &);
    inline void set(const char32_t &);
    inline void set(const long long &);
    inline void set(const long double &);
    inline void set(const signed char &);
    inline void set(const unsigned int &);
    inline void set(const unsigned char &);
    inline void set(const unsigned long &);
    inline void set(const unsigned short &);
    inline void set(const unsigned long long &);
    inline void set(string_view &);
    inline void set(int &);
    inline void set(char &);
    inline void set(bool &);
    inline void set(long &);
    inline void set(short &);
    inline void set(float &);
    inline void set(double &);
    inline void set(wchar_t &);
    inline void set(char16_t &);
    inline void set(char32_t &);
    inline void set(long long &);
    inline void set(long double &);
    inline void set(signed char &);
    inline void set(unsigned int &);
    inline void set(unsigned char &);
    inline void set(unsigned long &);
    inline void set(unsigned short &);
    inline void set(unsigned long long &);
public:
    inline BasicSharedData(std::shared_ptr<void> &&,const std::type_index&);
    inline BasicSharedData(const std::shared_ptr<void> &,const std::type_index&);
    inline BasicSharedData(std::shared_ptr<const void>&&,const std::type_index&);
    inline BasicSharedData(const std::shared_ptr<const void>&,const std::type_index&);
    inline void setShared(std::shared_ptr<void> &&,const std::type_index&);
    inline void setShared(const std::shared_ptr<void> &,const std::type_index&);
    inline void setShared(std::shared_ptr<const void>&&,const std::type_index&);
    inline void setShared(const std::shared_ptr<const void>&,const std::type_index&);
    inline void set(std::shared_ptr<void> &&arg,const std::type_index&argI) { setShared(std::move(arg),argI); }
    inline void set(const std::shared_ptr<void> &arg,const std::type_index&argI) { setShared(arg,argI); }
    inline void set(std::shared_ptr<const void>&&arg,const std::type_index&argI) { setShared(std::move(arg),argI); }
    inline void set(const std::shared_ptr<const void>&arg,const std::type_index&argI) { setShared(arg,argI); }
public:
    inline BasicSharedData(const BasicSharedData&);
    inline BasicSharedData(BasicSharedData&&);
    inline BasicSharedData&operator=(const BasicSharedData&);
    inline BasicSharedData&operator=(BasicSharedData&&);

};
/****************************************************/
inline const std::type_index&
BasicSharedData::getTypeIndex() const noexcept(true) {
    return _m_type_index;
}

inline bool BasicSharedData::isSharedPointer() const noexcept(true) {
    return _m_type==basictype_shared_pointer;
}

inline auto BasicSharedData::getType() const noexcept(true)
->BasicSharedData::BasicDataType {
    return static_cast<BasicDataType>(_m_type);
}

inline BasicSharedData::BasicSharedData():
    _m_data(nullptr),
    _m_type_index(typeid(void*)),
    _m_type(basictype_void_pointer),
    _m_is_const(false) {
}

inline BasicSharedData::BasicSharedData(const void *&arg,const std::type_index&argI):
    _m_data(arg),
    _m_type_index(argI),
    _m_type(basictype_void_pointer),
    _m_is_const(true) {
}

inline BasicSharedData::BasicSharedData(const decltype(nullptr)&arg):
    _m_data(arg),
    _m_type_index(typeid(void*)),
    _m_type(basictype_void_pointer),
    _m_is_const(true) {
}

inline BasicSharedData::BasicSharedData(void *&arg,const std::type_index&argI):
    _m_data(arg),
    _m_type_index(argI),
    _m_type(basictype_void_pointer),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(const string_view & arg):
    _m_data(arg),
    _m_type_index(typeid(string_view)),
    _m_type(basictype_string_view),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const int & arg):
    _m_data(arg),
    _m_type_index(typeid(int)),
    _m_type(basictype_int),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const char & arg):
    _m_data(arg),
    _m_type_index(typeid(char)),
    _m_type(basictype_char),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const bool & arg):
    _m_data(arg),
    _m_type_index(typeid(bool)),
    _m_type(basictype_bool),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const long & arg):
    _m_data(arg),
    _m_type_index(typeid(long)),
    _m_type(basictype_long),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const short & arg):
    _m_data(arg),
    _m_type_index(typeid(short)),
    _m_type(basictype_short),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const float & arg):
    _m_data(arg),
    _m_type_index(typeid(float)),
    _m_type(basictype_float),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const double & arg):
    _m_data(arg),
    _m_type_index(typeid(double)),
    _m_type(basictype_double),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const wchar_t & arg):
    _m_data(arg),
    _m_type_index(typeid(wchar_t)),
    _m_type(basictype_wchar_t),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const char16_t & arg):
    _m_data(arg),
    _m_type_index(typeid(char16_t)),
    _m_type(basictype_char16_t),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const char32_t & arg):
    _m_data(arg),
    _m_type_index(typeid(char32_t)),
    _m_type(basictype_char32_t),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const long long & arg):
    _m_data(arg),
    _m_type_index(typeid(long long)),
    _m_type(basictype_long_long),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const long double & arg):
    _m_data(arg),
    _m_type_index(typeid(long double)),
    _m_type(basictype_long_double),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const signed char & arg):
    _m_data(arg),
    _m_type_index(typeid(signed char)),
    _m_type(basictype_signed_char),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const unsigned int & arg):
    _m_data(arg),
    _m_type_index(typeid(unsigned int)),
    _m_type(basictype_unsigned_int),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const unsigned char & arg):
    _m_data(arg),
    _m_type_index(typeid(unsigned char)),
    _m_type(basictype_unsigned_char),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const unsigned long & arg):
    _m_data(arg),
    _m_type_index(typeid(unsigned long)),
    _m_type(basictype_unsigned_long),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const unsigned short & arg):
    _m_data(arg),
    _m_type_index(typeid(unsigned short)),
    _m_type(basictype_unsigned_short),
    _m_is_const(false/*pod is false*/) {
}
inline BasicSharedData::BasicSharedData(const unsigned long long & arg):
    _m_data(arg),
    _m_type_index(typeid(unsigned long long)),
    _m_type(basictype_unsigned_long_long),
    _m_is_const(false/*pod is false*/) {
}

inline BasicSharedData::BasicSharedData(string_view & arg):
    _m_data(arg),
    _m_type_index(typeid(string_view)),
    _m_type(basictype_string_view),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(int & arg):
    _m_data(arg),
    _m_type_index(typeid(int)),
    _m_type(basictype_int),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(char & arg):
    _m_data(arg),
    _m_type_index(typeid(char)),
    _m_type(basictype_char),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(bool & arg):
    _m_data(arg),
    _m_type_index(typeid(bool)),
    _m_type(basictype_bool),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(long & arg):
    _m_data(arg),
    _m_type_index(typeid(long)),
    _m_type(basictype_long),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(short & arg):
    _m_data(arg),
    _m_type_index(typeid(short)),
    _m_type(basictype_short),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(float & arg):
    _m_data(arg),
    _m_type_index(typeid(float)),
    _m_type(basictype_float),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(double & arg):
    _m_data(arg),
    _m_type_index(typeid(double)),
    _m_type(basictype_double),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(wchar_t & arg):
    _m_data(arg),
    _m_type_index(typeid(wchar_t)),
    _m_type(basictype_wchar_t),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(char16_t & arg):
    _m_data(arg),
    _m_type_index(typeid(char16_t)),
    _m_type(basictype_char16_t),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(char32_t & arg):
    _m_data(arg),
    _m_type_index(typeid(char32_t)),
    _m_type(basictype_char32_t),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(long long & arg):
    _m_data(arg),
    _m_type_index(typeid(long long)),
    _m_type(basictype_long_long),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(long double & arg):
    _m_data(arg),
    _m_type_index(typeid(long double)),
    _m_type(basictype_long_double),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(signed char & arg):
    _m_data(arg),
    _m_type_index(typeid(signed char)),
    _m_type(basictype_signed_char),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(unsigned int & arg):
    _m_data(arg),
    _m_type_index(typeid(unsigned int)),
    _m_type(basictype_unsigned_int),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(unsigned char & arg):
    _m_data(arg),
    _m_type_index(typeid(unsigned char)),
    _m_type(basictype_unsigned_char),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(unsigned long & arg):
    _m_data(arg),
    _m_type_index(typeid(unsigned long)),
    _m_type(basictype_unsigned_long),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(unsigned short & arg):
    _m_data(arg),
    _m_type_index(typeid(unsigned short)),
    _m_type(basictype_unsigned_short),
    _m_is_const(false) {
}
inline BasicSharedData::BasicSharedData(unsigned long long & arg):
    _m_data(arg),
    _m_type_index(typeid(unsigned long long)),
    _m_type(basictype_unsigned_long_long),
    _m_is_const(false) {
}
inline void * BasicSharedData::_p_get_data() const {
    switch (this->_m_type) {
        case basictype_void_pointer:return _m_data._m_void_pointer;
        case basictype_shared_pointer:return _m_data._m_shared_pointer.get();
        case basictype_string_view: return const_cast<string_view*>(&(_m_data._m_string_view));
        case basictype_int: return const_cast<int*>(&(_m_data._m_int));
        case basictype_char: return const_cast<char*>(&(_m_data._m_char));
        case basictype_bool: return const_cast<bool*>(&(_m_data._m_bool));
        case basictype_long: return const_cast<long*>(&(_m_data._m_long));
        case basictype_short: return const_cast<short*>(&(_m_data._m_short));
        case basictype_float: return const_cast<float*>(&(_m_data._m_float));
        case basictype_double: return const_cast<double*>(&(_m_data._m_double));
        case basictype_wchar_t: return const_cast<wchar_t*>(&(_m_data._m_wchar_t));
        case basictype_char16_t: return const_cast<char16_t*>(&(_m_data._m_char16_t));
        case basictype_char32_t: return const_cast<char32_t*>(&(_m_data._m_char32_t));
        case basictype_long_long: return const_cast<long long*>(&(_m_data._m_long_long));
        case basictype_long_double: return const_cast<long double*>(&(_m_data._m_long_double));
        case basictype_signed_char: return const_cast<signed char*>(&(_m_data._m_signed_char));
        case basictype_unsigned_int: return const_cast<unsigned int*>(&(_m_data._m_unsigned_int));
        case basictype_unsigned_char: return const_cast<unsigned char*>(&(_m_data._m_unsigned_char));
        case basictype_unsigned_long: return const_cast<unsigned long*>(&(_m_data._m_unsigned_long));
        case basictype_unsigned_short: return const_cast<unsigned short*>(&(_m_data._m_unsigned_short));
        case basictype_unsigned_long_long: return const_cast<unsigned long long*>(&(_m_data._m_unsigned_long_long));
    }
    return nullptr;
}
inline bool BasicSharedData::isConst() const noexcept(true) {
    return _m_is_const;
}
inline void BasicSharedData::_p_clean() {
    _p_try_free();
    _m_data._m_void_pointer=nullptr;
    _m_type=basictype_void_pointer;
    _m_type_index=typeid(void*);
    _m_is_const=false;
}

inline void BasicSharedData::setVoid(const void *&arg,const std::type_index&argI) {
    if (_m_type==basictype_void_pointer) {
        _m_data._m_void_pointer=const_cast<void*>(arg);
        _m_type_index=argI;
        _m_is_const=true;
        return;
    }
    _p_try_free();
    _m_data._m_void_pointer=const_cast<void*>(arg);
    _m_type_index=argI;
    _m_type=basictype_void_pointer;
    _m_is_const=true;
}
inline void BasicSharedData::setVoid(void *&arg,const std::type_index&argI) {
    if (_m_type==basictype_void_pointer) {
        _m_data._m_void_pointer=arg;
        _m_type_index=argI;
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_void_pointer=arg;
    _m_type_index=argI;
    _m_type=basictype_void_pointer;
    _m_is_const=false;
}
inline void BasicSharedData::set(const string_view & arg) {
    if (_m_type==basictype_string_view) {
        _m_data._m_string_view=arg;
        _m_type_index=typeid(string_view);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_string_view=arg;
    _m_type_index=typeid(string_view);
    _m_type=basictype_string_view;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const int & arg) {
    if (_m_type==basictype_int) {
        _m_data._m_int=arg;
        _m_type_index=typeid(int);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_int=arg;
    _m_type_index=typeid(int);
    _m_type=basictype_int;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const char & arg) {
    if (_m_type==basictype_char) {
        _m_data._m_char=arg;
        _m_type_index=typeid(char);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_char=arg;
    _m_type_index=typeid(char);
    _m_type=basictype_char;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const bool & arg) {
    if (_m_type==basictype_bool) {
        _m_data._m_bool=arg;
        _m_type_index=typeid(bool);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_bool=arg;
    _m_type_index=typeid(bool);
    _m_type=basictype_bool;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const long & arg) {
    if (_m_type==basictype_long) {
        _m_data._m_long=arg;
        _m_type_index=typeid(long);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_long=arg;
    _m_type_index=typeid(long);
    _m_type=basictype_long;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const short & arg) {
    if (_m_type==basictype_short) {
        _m_data._m_short=arg;
        _m_type_index=typeid(short);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_short=arg;
    _m_type_index=typeid(short);
    _m_type=basictype_short;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const float & arg) {
    if (_m_type==basictype_float) {
        _m_data._m_float=arg;
        _m_type_index=typeid(float);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_float=arg;
    _m_type_index=typeid(float);
    _m_type=basictype_float;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const double & arg) {
    if (_m_type==basictype_double) {
        _m_data._m_double=arg;
        _m_type_index=typeid(double);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_double=arg;
    _m_type_index=typeid(double);
    _m_type=basictype_double;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const wchar_t & arg) {
    if (_m_type==basictype_wchar_t) {
        _m_data._m_wchar_t=arg;
        _m_type_index=typeid(wchar_t);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_wchar_t=arg;
    _m_type_index=typeid(wchar_t);
    _m_type=basictype_wchar_t;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const char16_t & arg) {
    if (_m_type==basictype_char16_t) {
        _m_data._m_char16_t=arg;
        _m_type_index=typeid(char16_t);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_char16_t=arg;
    _m_type_index=typeid(char16_t);
    _m_type=basictype_char16_t;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const char32_t & arg) {
    if (_m_type==basictype_char32_t) {
        _m_data._m_char32_t=arg;
        _m_type_index=typeid(char32_t);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_char32_t=arg;
    _m_type_index=typeid(char32_t);
    _m_type=basictype_char32_t;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const long long & arg) {
    if (_m_type==basictype_long_long) {
        _m_data._m_long_long=arg;
        _m_type_index=typeid(long long);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_long_long=arg;
    _m_type_index=typeid(long long);
    _m_type=basictype_long_long;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const long double & arg) {
    if (_m_type==basictype_long_double) {
        _m_data._m_long_double=arg;
        _m_type_index=typeid(long double);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_long_double=arg;
    _m_type_index=typeid(long double);
    _m_type=basictype_long_double;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const signed char & arg) {
    if (_m_type==basictype_signed_char) {
        _m_data._m_signed_char=arg;
        _m_type_index=typeid(signed char);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_signed_char=arg;
    _m_type_index=typeid(signed char);
    _m_type=basictype_signed_char;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const unsigned int & arg) {
    if (_m_type==basictype_unsigned_int) {
        _m_data._m_unsigned_int=arg;
        _m_type_index=typeid(unsigned int);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_unsigned_int=arg;
    _m_type_index=typeid(unsigned int);
    _m_type=basictype_unsigned_int;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const unsigned char & arg) {
    if (_m_type==basictype_unsigned_char) {
        _m_data._m_unsigned_char=arg;
        _m_type_index=typeid(unsigned char);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_unsigned_char=arg;
    _m_type_index=typeid(unsigned char);
    _m_type=basictype_unsigned_char;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const unsigned long & arg) {
    if (_m_type==basictype_unsigned_long) {
        _m_data._m_unsigned_long=arg;
        _m_type_index=typeid(unsigned long);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_unsigned_long=arg;
    _m_type_index=typeid(unsigned long);
    _m_type=basictype_unsigned_long;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const unsigned short & arg) {
    if (_m_type==basictype_unsigned_short) {
        _m_data._m_unsigned_short=arg;
        _m_type_index=typeid(unsigned short);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_unsigned_short=arg;
    _m_type_index=typeid(unsigned short);
    _m_type=basictype_unsigned_short;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(const unsigned long long & arg) {
    if (_m_type==basictype_unsigned_long_long) {
        _m_data._m_unsigned_long_long=arg;
        _m_type_index=typeid(unsigned long long);
        _m_is_const=false/*pod is false*/;
        return;
    }
    _p_try_free();
    _m_data._m_unsigned_long_long=arg;
    _m_type_index=typeid(unsigned long long);
    _m_type=basictype_unsigned_long_long;
    _m_is_const=false/*pod is false*/;
}
inline void BasicSharedData::set(string_view & arg) {
    if (_m_type==basictype_string_view) {
        _m_data._m_string_view=arg;
        _m_type_index=typeid(string_view);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_string_view=arg;
    _m_type_index=typeid(string_view);
    _m_type=basictype_string_view;
    _m_is_const=false;
}
inline void BasicSharedData::set(int & arg) {
    if (_m_type==basictype_int) {
        _m_data._m_int=arg;
        _m_type_index=typeid(int);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_int=arg;
    _m_type_index=typeid(int);
    _m_type=basictype_int;
    _m_is_const=false;
}
inline void BasicSharedData::set(char & arg) {
    if (_m_type==basictype_char) {
        _m_data._m_char=arg;
        _m_type_index=typeid(char);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_char=arg;
    _m_type_index=typeid(char);
    _m_type=basictype_char;
    _m_is_const=false;
}
inline void BasicSharedData::set(bool & arg) {
    if (_m_type==basictype_bool) {
        _m_data._m_bool=arg;
        _m_type_index=typeid(bool);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_bool=arg;
    _m_type_index=typeid(bool);
    _m_type=basictype_bool;
    _m_is_const=false;
}
inline void BasicSharedData::set(long & arg) {
    if (_m_type==basictype_long) {
        _m_data._m_long=arg;
        _m_type_index=typeid(long);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_long=arg;
    _m_type_index=typeid(long);
    _m_type=basictype_long;
    _m_is_const=false;
}
inline void BasicSharedData::set(short & arg) {
    if (_m_type==basictype_short) {
        _m_data._m_short=arg;
        _m_type_index=typeid(short);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_short=arg;
    _m_type_index=typeid(short);
    _m_type=basictype_short;
    _m_is_const=false;
}
inline void BasicSharedData::set(float & arg) {
    if (_m_type==basictype_float) {
        _m_data._m_float=arg;
        _m_type_index=typeid(float);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_float=arg;
    _m_type_index=typeid(float);
    _m_type=basictype_float;
    _m_is_const=false;
}
inline void BasicSharedData::set(double & arg) {
    if (_m_type==basictype_double) {
        _m_data._m_double=arg;
        _m_type_index=typeid(double);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_double=arg;
    _m_type_index=typeid(double);
    _m_type=basictype_double;
    _m_is_const=false;
}
inline void BasicSharedData::set(wchar_t & arg) {
    if (_m_type==basictype_wchar_t) {
        _m_data._m_wchar_t=arg;
        _m_type_index=typeid(wchar_t);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_wchar_t=arg;
    _m_type_index=typeid(wchar_t);
    _m_type=basictype_wchar_t;
    _m_is_const=false;
}
inline void BasicSharedData::set(char16_t & arg) {
    if (_m_type==basictype_char16_t) {
        _m_data._m_char16_t=arg;
        _m_type_index=typeid(char16_t);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_char16_t=arg;
    _m_type_index=typeid(char16_t);
    _m_type=basictype_char16_t;
    _m_is_const=false;
}
inline void BasicSharedData::set(char32_t & arg) {
    if (_m_type==basictype_char32_t) {
        _m_data._m_char32_t=arg;
        _m_type_index=typeid(char32_t);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_char32_t=arg;
    _m_type_index=typeid(char32_t);
    _m_type=basictype_char32_t;
    _m_is_const=false;
}
inline void BasicSharedData::set(long long & arg) {
    if (_m_type==basictype_long_long) {
        _m_data._m_long_long=arg;
        _m_type_index=typeid(long long);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_long_long=arg;
    _m_type_index=typeid(long long);
    _m_type=basictype_long_long;
    _m_is_const=false;
}
inline void BasicSharedData::set(long double & arg) {
    if (_m_type==basictype_long_double) {
        _m_data._m_long_double=arg;
        _m_type_index=typeid(long double);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_long_double=arg;
    _m_type_index=typeid(long double);
    _m_type=basictype_long_double;
    _m_is_const=false;
}
inline void BasicSharedData::set(signed char & arg) {
    if (_m_type==basictype_signed_char) {
        _m_data._m_signed_char=arg;
        _m_type_index=typeid(signed char);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_signed_char=arg;
    _m_type_index=typeid(signed char);
    _m_type=basictype_signed_char;
    _m_is_const=false;
}
inline void BasicSharedData::set(unsigned int & arg) {
    if (_m_type==basictype_unsigned_int) {
        _m_data._m_unsigned_int=arg;
        _m_type_index=typeid(unsigned int);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_unsigned_int=arg;
    _m_type_index=typeid(unsigned int);
    _m_type=basictype_unsigned_int;
    _m_is_const=false;
}
inline void BasicSharedData::set(unsigned char & arg) {
    if (_m_type==basictype_unsigned_char) {
        _m_data._m_unsigned_char=arg;
        _m_type_index=typeid(unsigned char);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_unsigned_char=arg;
    _m_type_index=typeid(unsigned char);
    _m_type=basictype_unsigned_char;
    _m_is_const=false;
}
inline void BasicSharedData::set(unsigned long & arg) {
    if (_m_type==basictype_unsigned_long) {
        _m_data._m_unsigned_long=arg;
        _m_type_index=typeid(unsigned long);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_unsigned_long=arg;
    _m_type_index=typeid(unsigned long);
    _m_type=basictype_unsigned_long;
    _m_is_const=false;
}
inline void BasicSharedData::set(unsigned short & arg) {
    if (_m_type==basictype_unsigned_short) {
        _m_data._m_unsigned_short=arg;
        _m_type_index=typeid(unsigned short);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_unsigned_short=arg;
    _m_type_index=typeid(unsigned short);
    _m_type=basictype_unsigned_short;
    _m_is_const=false;
}
inline void BasicSharedData::set(unsigned long long & arg) {
    if (_m_type==basictype_unsigned_long_long) {
        _m_data._m_unsigned_long_long=arg;
        _m_type_index=typeid(unsigned long long);
        _m_is_const=false;
        return;
    }
    _p_try_free();
    _m_data._m_unsigned_long_long=arg;
    _m_type_index=typeid(unsigned long long);
    _m_type=basictype_unsigned_long_long;
    _m_is_const=false;
}

inline BasicSharedData::BasicSharedData(std::shared_ptr<void> &&arg,const std::type_index&argI)
    :_m_data(std::move(arg))
    ,_m_type_index(argI)
    ,_m_type(basictype_shared_pointer)
    ,_m_is_const(false) {
}

inline BasicSharedData::BasicSharedData(const std::shared_ptr<void> &arg,const std::type_index&argI)
    :_m_data(_T_{ arg })
    ,_m_type_index(argI)
    ,_m_type(basictype_shared_pointer)
    ,_m_is_const(false) {
}

inline BasicSharedData::BasicSharedData(std::shared_ptr<const void>&&arg,const std::type_index&argI)
    :_m_data(std::move(arg))
    ,_m_type_index(argI)
    ,_m_type(basictype_shared_pointer)
    ,_m_is_const(true) {
}

inline BasicSharedData::BasicSharedData(const std::shared_ptr<const void>&arg,const std::type_index&argI)
    :_m_data(std::shared_ptr<const void>{ arg })
    ,_m_type_index(argI)
    ,_m_type(basictype_shared_pointer)
    ,_m_is_const(true) {
}

inline void BasicSharedData::_p_create(const std::shared_ptr<void>&arg) {
    ::new (&_m_data._m_shared_pointer) _T_{ arg };
}

inline void BasicSharedData::_p_create(std::shared_ptr<void>&&arg) {
    ::new (&_m_data._m_shared_pointer) _T_{ std::move(arg) };
}

inline void BasicSharedData::_p_create(const std::shared_ptr<const void>&arg) {
    _p_create(std::const_pointer_cast<void>(arg));
}

inline void BasicSharedData::_p_create(std::shared_ptr<const void>&&arg) {
    _p_create(std::const_pointer_cast<void>(std::move(arg)));
}

inline void BasicSharedData::setShared(std::shared_ptr<void> &&arg,const std::type_index&argI) {
    if (bool(arg)==false) { return _p_clean(); }
    if (_m_type==basictype_shared_pointer) {
        _m_data._m_shared_pointer=std::move(arg);
        _m_type_index=argI;
        _m_is_const=false;
        return;
    }
    _p_create(std::move(arg));
    _m_type=basictype_shared_pointer;
    _m_type_index=argI;
    _m_is_const=false;
}

inline void BasicSharedData::setShared(const std::shared_ptr<void> &arg,const std::type_index&argI) {
    if (bool(arg)==false) { return _p_clean(); }
    if (_m_type==basictype_shared_pointer) {
        _m_data._m_shared_pointer=arg;
        _m_type_index=argI;
        _m_is_const=false;
        return;
    }
    _p_create(arg);
    _m_type=basictype_shared_pointer;
    _m_type_index=argI;
    _m_is_const=false;
}

inline void BasicSharedData::setShared(std::shared_ptr<const void>&&arg,const std::type_index&argI) {
    if (bool(arg)==false) { return _p_clean(); }
    if (_m_type==basictype_shared_pointer) {
        _m_data._m_shared_pointer=std::const_pointer_cast<void>(std::move(arg));
        _m_type_index=argI;
        _m_is_const=true;
        return;
    }
    _p_create(std::move(arg));
    _m_type=basictype_shared_pointer;
    _m_type_index=argI;
    _m_is_const=true;
}

inline void BasicSharedData::setShared(const std::shared_ptr<const void>&arg,const std::type_index&argI) {
    if (bool(arg)==false) { return _p_clean(); }
    if (_m_type==basictype_shared_pointer) {
        _m_data._m_shared_pointer=std::const_pointer_cast<void>(arg);
        _m_type_index=argI;
        _m_is_const=true;
        return;
    }
    _p_create(arg);
    _m_type=basictype_shared_pointer;
    _m_type_index=argI;
    _m_is_const=true;
}

inline BasicSharedData::BasicSharedData(const BasicSharedData&arg)
    :_m_type_index(arg._m_type_index)
    ,_m_type(arg._m_type)
    ,_m_is_const(arg._m_is_const) {
    if (arg.isSharedPointer()) {
        _p_create(arg._m_data._m_shared_pointer);
        return;
    }
    _p_copy_pod(arg._m_type,arg._m_data);
}

inline BasicSharedData::BasicSharedData(BasicSharedData&&arg)
    :_m_type_index(arg._m_type_index)
    ,_m_type(arg._m_type)
    ,_m_is_const(arg._m_is_const) {
    if (arg.isSharedPointer()) {
        _p_create(std::move(arg._m_data._m_shared_pointer));
        return;
    }
    _p_copy_pod(arg._m_type,arg._m_data);
}


inline void BasicSharedData::_p_copy_pod(BasicDataType arg,const BasicData&var) {
    switch (arg) {
        case basictype_void_pointer:_m_data._m_void_pointer=var._m_void_pointer; return;
        case basictype_shared_pointer:return;
        case basictype_string_view:_m_data._m_string_view=var._m_string_view; return;
        case basictype_int:_m_data._m_int=var._m_int; return;
        case basictype_char:_m_data._m_char=var._m_char; return;
        case basictype_bool:_m_data._m_bool=var._m_bool; return;
        case basictype_long:_m_data._m_long=var._m_long; return;
        case basictype_short:_m_data._m_short=var._m_short; return;
        case basictype_float:_m_data._m_float=var._m_float; return;
        case basictype_double:_m_data._m_double=var._m_double; return;
        case basictype_wchar_t:_m_data._m_wchar_t=var._m_wchar_t; return;
        case basictype_char16_t:_m_data._m_char16_t=var._m_char16_t; return;
        case basictype_char32_t:_m_data._m_char32_t=var._m_char32_t; return;
        case basictype_long_long:_m_data._m_long_long=var._m_long_long; return;
        case basictype_long_double:_m_data._m_long_double=var._m_long_double; return;
        case basictype_signed_char:_m_data._m_signed_char=var._m_signed_char; return;
        case basictype_unsigned_int:_m_data._m_unsigned_int=var._m_unsigned_int; return;
        case basictype_unsigned_char:_m_data._m_unsigned_char=var._m_unsigned_char; return;
        case basictype_unsigned_long:_m_data._m_unsigned_long=var._m_unsigned_long; return;
        case basictype_unsigned_short:_m_data._m_unsigned_short=var._m_unsigned_short; return;
        case basictype_unsigned_long_long:_m_data._m_unsigned_long_long=var._m_unsigned_long_long; return;

    }
}

inline BasicSharedData&BasicSharedData::operator=(const BasicSharedData&arg) {
    if (this==&arg) { return *this; }
    if (arg.isSharedPointer()) {
        if (isSharedPointer()) {
            _m_data._m_shared_pointer=arg._m_data._m_shared_pointer;
            _m_is_const=arg._m_is_const;
            _m_type_index=arg._m_type_index;
        }
        else {
            _p_create(arg._m_data._m_shared_pointer);
            _m_type=basictype_shared_pointer;
            _m_is_const=arg._m_is_const;
            _m_type_index=arg._m_type_index;
        }
    }
    else {
        _p_try_free();
        _m_is_const=arg._m_is_const;
        _m_type_index=arg._m_type_index;
        _m_type=arg._m_type;
        _p_copy_pod(_m_type,arg._m_data);
    }
    return *this;
}
inline BasicSharedData&BasicSharedData::operator=(BasicSharedData&&arg) {
    if (this==&arg) { return *this; }
    if (arg.isSharedPointer()) {
        if (isSharedPointer()) {
            _m_data._m_shared_pointer=std::move(arg._m_data._m_shared_pointer);
            _m_is_const=arg._m_is_const;
            _m_type_index=arg._m_type_index;
        }
        else {
            _p_create(std::move(arg._m_data._m_shared_pointer));
            _m_type=basictype_shared_pointer;
            _m_is_const=arg._m_is_const;
            _m_type_index=arg._m_type_index;
        }
    }
    else {
        _p_try_free();
        _m_is_const=arg._m_is_const;
        _m_type_index=arg._m_type_index;
        _m_type=arg._m_type;
        _p_copy_pod(_m_type,arg._m_data);
    }
    return *this;
}

}/*namespace runtime*/

#endif/*__HPP_35765_RUNTIME_BASICSHAREDDATA_*/

