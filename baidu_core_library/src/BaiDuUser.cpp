﻿/*BaiDuUser cpp*/
#include "../BaiDuUser.hpp"
#include "../private/BaiDuUserData.hpp"
#include "../private/BaiDuUserPrivateFunction.hpp"
#include <QtCore>
#include <QtScript>
#include <QtCrypto>
#include <QtNetwork>
#include <string>

namespace baidu {

namespace {

using string=std::basic_string<char,std::char_traits<char>,memory::Allocator<char>>;

inline Q_DECL_CONSTEXPR QLatin1Literal operator""_qsl(const char *arg,std::size_t n) {
    return QLatin1Literal(arg,int(n));
}

inline QByteArray operator""_qb(const char *arg,std::size_t n) {
    return QByteArray(arg,int(n));
}

template<typename _T_>
class StringRef;

template<typename T,std::size_t N>
class StringRef<T[N]> {
    const T(&_m_Data)[N];
public:
    constexpr StringRef(const T(&argData)[N]):_m_Data(argData) {}
    const char * data() const { return _m_Data; }
    int size() const { return int(N-1); }
};

template<>
class StringRef<QByteArray> {
    const QByteArray & _m_Data;
public:
    constexpr StringRef(const QByteArray&arg):_m_Data(arg) {}
    const char *data() const { return _m_Data.data(); }
    int size() const { return _m_Data.size(); }
};

template<>
class StringRef<string> {
    const string & _m_Data;
public:
    constexpr StringRef(const string&arg):_m_Data(arg) {}
    const char *data() const { return _m_Data.data(); }
    int size() { return _m_Data.size(); }
};

template<typename _T_>
constexpr auto make_string_ref(const _T_&arg) {
    return StringRef<_T_>(arg);
}

template<std::size_t N>
constexpr auto make_string_ref(const char(&arg)[N]) {
    return StringRef<char[N]>(arg);
}

/******************************************************************/
namespace utility_cpp14 {/*此函数最好在c++17重写*/
template<
    typename _t_0_0,typename _t_0_1
>
string __cat_to_url(const _t_0_0&_v_0_0,const _t_0_1&_v_0_1) {
    constexpr int _n=1*(2/*&=*/)+4;
    const int _size=_n
        +_v_0_0.size()+_v_0_1.size();
    string _ans;
    _ans.reserve(_size);
    _ans.append("&",1);
    _ans.append(_v_0_0.data(),_v_0_0.size());
    _ans.append("=",1);
    _ans.append(_v_0_1.data(),_v_0_1.size());
    return std::move(_ans);
}
template<
    typename _t_0_0,typename _t_0_1,
    typename _t_1_0,typename _t_1_1
>
string __cat_to_url(const _t_0_0&_v_0_0,const _t_0_1&_v_0_1,
    const _t_1_0&_v_1_0,const _t_1_1&_v_1_1) {
    constexpr int _n=2*(2/*&=*/)+4;
    const int _size=_n
        +_v_0_0.size()+_v_0_1.size()
        +_v_1_0.size()+_v_1_1.size();
    string _ans;
    _ans.reserve(_size);
    _ans.append("&",1);
    _ans.append(_v_0_0.data(),_v_0_0.size());
    _ans.append("=",1);
    _ans.append(_v_0_1.data(),_v_0_1.size());
    _ans.append("&",1);
    _ans.append(_v_1_0.data(),_v_1_0.size());
    _ans.append("=",1);
    _ans.append(_v_1_1.data(),_v_1_1.size());
    return std::move(_ans);
}
template<
    typename _t_0_0,typename _t_0_1,
    typename _t_1_0,typename _t_1_1,
    typename _t_2_0,typename _t_2_1
>
string __cat_to_url(const _t_0_0&_v_0_0,const _t_0_1&_v_0_1,
    const _t_1_0&_v_1_0,const _t_1_1&_v_1_1,
    const _t_2_0&_v_2_0,const _t_2_1&_v_2_1) {
    constexpr int _n=3*(2/*&=*/)+4;
    const int _size=_n
        +_v_0_0.size()+_v_0_1.size()
        +_v_1_0.size()+_v_1_1.size()
        +_v_2_0.size()+_v_2_1.size();
    string _ans;
    _ans.reserve(_size);
    _ans.append("&",1);
    _ans.append(_v_0_0.data(),_v_0_0.size());
    _ans.append("=",1);
    _ans.append(_v_0_1.data(),_v_0_1.size());
    _ans.append("&",1);
    _ans.append(_v_1_0.data(),_v_1_0.size());
    _ans.append("=",1);
    _ans.append(_v_1_1.data(),_v_1_1.size());
    _ans.append("&",1);
    _ans.append(_v_2_0.data(),_v_2_0.size());
    _ans.append("=",1);
    _ans.append(_v_2_1.data(),_v_2_1.size());
    return std::move(_ans);
}
template<
    typename _t_0_0,typename _t_0_1,
    typename _t_1_0,typename _t_1_1,
    typename _t_2_0,typename _t_2_1,
    typename _t_3_0,typename _t_3_1
>
string __cat_to_url(const _t_0_0&_v_0_0,const _t_0_1&_v_0_1,
    const _t_1_0&_v_1_0,const _t_1_1&_v_1_1,
    const _t_2_0&_v_2_0,const _t_2_1&_v_2_1,
    const _t_3_0&_v_3_0,const _t_3_1&_v_3_1) {
    constexpr int _n=4*(2/*&=*/)+4;
    const int _size=_n
        +_v_0_0.size()+_v_0_1.size()
        +_v_1_0.size()+_v_1_1.size()
        +_v_2_0.size()+_v_2_1.size()
        +_v_3_0.size()+_v_3_1.size();
    string _ans;
    _ans.reserve(_size);
    _ans.append("&",1);
    _ans.append(_v_0_0.data(),_v_0_0.size());
    _ans.append("=",1);
    _ans.append(_v_0_1.data(),_v_0_1.size());
    _ans.append("&",1);
    _ans.append(_v_1_0.data(),_v_1_0.size());
    _ans.append("=",1);
    _ans.append(_v_1_1.data(),_v_1_1.size());
    _ans.append("&",1);
    _ans.append(_v_2_0.data(),_v_2_0.size());
    _ans.append("=",1);
    _ans.append(_v_2_1.data(),_v_2_1.size());
    _ans.append("&",1);
    _ans.append(_v_3_0.data(),_v_3_0.size());
    _ans.append("=",1);
    _ans.append(_v_3_1.data(),_v_3_1.size());
    return std::move(_ans);
}
template<
    typename _t_0_0,typename _t_0_1,
    typename _t_1_0,typename _t_1_1,
    typename _t_2_0,typename _t_2_1,
    typename _t_3_0,typename _t_3_1,
    typename _t_4_0,typename _t_4_1
>
string __cat_to_url(const _t_0_0&_v_0_0,const _t_0_1&_v_0_1,
    const _t_1_0&_v_1_0,const _t_1_1&_v_1_1,
    const _t_2_0&_v_2_0,const _t_2_1&_v_2_1,
    const _t_3_0&_v_3_0,const _t_3_1&_v_3_1,
    const _t_4_0&_v_4_0,const _t_4_1&_v_4_1) {
    constexpr int _n=5*(2/*&=*/)+4;
    const int _size=_n
        +_v_0_0.size()+_v_0_1.size()
        +_v_1_0.size()+_v_1_1.size()
        +_v_2_0.size()+_v_2_1.size()
        +_v_3_0.size()+_v_3_1.size()
        +_v_4_0.size()+_v_4_1.size();
    string _ans;
    _ans.reserve(_size);
    _ans.append("&",1);
    _ans.append(_v_0_0.data(),_v_0_0.size());
    _ans.append("=",1);
    _ans.append(_v_0_1.data(),_v_0_1.size());
    _ans.append("&",1);
    _ans.append(_v_1_0.data(),_v_1_0.size());
    _ans.append("=",1);
    _ans.append(_v_1_1.data(),_v_1_1.size());
    _ans.append("&",1);
    _ans.append(_v_2_0.data(),_v_2_0.size());
    _ans.append("=",1);
    _ans.append(_v_2_1.data(),_v_2_1.size());
    _ans.append("&",1);
    _ans.append(_v_3_0.data(),_v_3_0.size());
    _ans.append("=",1);
    _ans.append(_v_3_1.data(),_v_3_1.size());
    _ans.append("&",1);
    _ans.append(_v_4_0.data(),_v_4_0.size());
    _ans.append("=",1);
    _ans.append(_v_4_1.data(),_v_4_1.size());
    return std::move(_ans);
}
template<
    typename _t_0_0,typename _t_0_1,
    typename _t_1_0,typename _t_1_1,
    typename _t_2_0,typename _t_2_1,
    typename _t_3_0,typename _t_3_1,
    typename _t_4_0,typename _t_4_1,
    typename _t_5_0,typename _t_5_1
>
string __cat_to_url(const _t_0_0&_v_0_0,const _t_0_1&_v_0_1,
    const _t_1_0&_v_1_0,const _t_1_1&_v_1_1,
    const _t_2_0&_v_2_0,const _t_2_1&_v_2_1,
    const _t_3_0&_v_3_0,const _t_3_1&_v_3_1,
    const _t_4_0&_v_4_0,const _t_4_1&_v_4_1,
    const _t_5_0&_v_5_0,const _t_5_1&_v_5_1) {
    constexpr int _n=6*(2/*&=*/)+4;
    const int _size=_n
        +_v_0_0.size()+_v_0_1.size()
        +_v_1_0.size()+_v_1_1.size()
        +_v_2_0.size()+_v_2_1.size()
        +_v_3_0.size()+_v_3_1.size()
        +_v_4_0.size()+_v_4_1.size()
        +_v_5_0.size()+_v_5_1.size();
    string _ans;
    _ans.reserve(_size);
    _ans.append("&",1);
    _ans.append(_v_0_0.data(),_v_0_0.size());
    _ans.append("=",1);
    _ans.append(_v_0_1.data(),_v_0_1.size());
    _ans.append("&",1);
    _ans.append(_v_1_0.data(),_v_1_0.size());
    _ans.append("=",1);
    _ans.append(_v_1_1.data(),_v_1_1.size());
    _ans.append("&",1);
    _ans.append(_v_2_0.data(),_v_2_0.size());
    _ans.append("=",1);
    _ans.append(_v_2_1.data(),_v_2_1.size());
    _ans.append("&",1);
    _ans.append(_v_3_0.data(),_v_3_0.size());
    _ans.append("=",1);
    _ans.append(_v_3_1.data(),_v_3_1.size());
    _ans.append("&",1);
    _ans.append(_v_4_0.data(),_v_4_0.size());
    _ans.append("=",1);
    _ans.append(_v_4_1.data(),_v_4_1.size());
    _ans.append("&",1);
    _ans.append(_v_5_0.data(),_v_5_0.size());
    _ans.append("=",1);
    _ans.append(_v_5_1.data(),_v_5_1.size());
    return std::move(_ans);
}
template<
    typename _t_0_0,typename _t_0_1,
    typename _t_1_0,typename _t_1_1,
    typename _t_2_0,typename _t_2_1,
    typename _t_3_0,typename _t_3_1,
    typename _t_4_0,typename _t_4_1,
    typename _t_5_0,typename _t_5_1,
    typename _t_6_0,typename _t_6_1
>
string __cat_to_url(const _t_0_0&_v_0_0,const _t_0_1&_v_0_1,
    const _t_1_0&_v_1_0,const _t_1_1&_v_1_1,
    const _t_2_0&_v_2_0,const _t_2_1&_v_2_1,
    const _t_3_0&_v_3_0,const _t_3_1&_v_3_1,
    const _t_4_0&_v_4_0,const _t_4_1&_v_4_1,
    const _t_5_0&_v_5_0,const _t_5_1&_v_5_1,
    const _t_6_0&_v_6_0,const _t_6_1&_v_6_1) {
    constexpr int _n=7*(2/*&=*/)+4;
    const int _size=_n
        +_v_0_0.size()+_v_0_1.size()
        +_v_1_0.size()+_v_1_1.size()
        +_v_2_0.size()+_v_2_1.size()
        +_v_3_0.size()+_v_3_1.size()
        +_v_4_0.size()+_v_4_1.size()
        +_v_5_0.size()+_v_5_1.size()
        +_v_6_0.size()+_v_6_1.size();
    string _ans;
    _ans.reserve(_size);
    _ans.append("&",1);
    _ans.append(_v_0_0.data(),_v_0_0.size());
    _ans.append("=",1);
    _ans.append(_v_0_1.data(),_v_0_1.size());
    _ans.append("&",1);
    _ans.append(_v_1_0.data(),_v_1_0.size());
    _ans.append("=",1);
    _ans.append(_v_1_1.data(),_v_1_1.size());
    _ans.append("&",1);
    _ans.append(_v_2_0.data(),_v_2_0.size());
    _ans.append("=",1);
    _ans.append(_v_2_1.data(),_v_2_1.size());
    _ans.append("&",1);
    _ans.append(_v_3_0.data(),_v_3_0.size());
    _ans.append("=",1);
    _ans.append(_v_3_1.data(),_v_3_1.size());
    _ans.append("&",1);
    _ans.append(_v_4_0.data(),_v_4_0.size());
    _ans.append("=",1);
    _ans.append(_v_4_1.data(),_v_4_1.size());
    _ans.append("&",1);
    _ans.append(_v_5_0.data(),_v_5_0.size());
    _ans.append("=",1);
    _ans.append(_v_5_1.data(),_v_5_1.size());
    _ans.append("&",1);
    _ans.append(_v_6_0.data(),_v_6_0.size());
    _ans.append("=",1);
    _ans.append(_v_6_1.data(),_v_6_1.size());
    return std::move(_ans);
}
template<
    typename _t_0_0,typename _t_0_1,
    typename _t_1_0,typename _t_1_1,
    typename _t_2_0,typename _t_2_1,
    typename _t_3_0,typename _t_3_1,
    typename _t_4_0,typename _t_4_1,
    typename _t_5_0,typename _t_5_1,
    typename _t_6_0,typename _t_6_1,
    typename _t_7_0,typename _t_7_1
>
string __cat_to_url(const _t_0_0&_v_0_0,const _t_0_1&_v_0_1,
    const _t_1_0&_v_1_0,const _t_1_1&_v_1_1,
    const _t_2_0&_v_2_0,const _t_2_1&_v_2_1,
    const _t_3_0&_v_3_0,const _t_3_1&_v_3_1,
    const _t_4_0&_v_4_0,const _t_4_1&_v_4_1,
    const _t_5_0&_v_5_0,const _t_5_1&_v_5_1,
    const _t_6_0&_v_6_0,const _t_6_1&_v_6_1,
    const _t_7_0&_v_7_0,const _t_7_1&_v_7_1) {
    constexpr int _n=8*(2/*&=*/)+4;
    const int _size=_n
        +_v_0_0.size()+_v_0_1.size()
        +_v_1_0.size()+_v_1_1.size()
        +_v_2_0.size()+_v_2_1.size()
        +_v_3_0.size()+_v_3_1.size()
        +_v_4_0.size()+_v_4_1.size()
        +_v_5_0.size()+_v_5_1.size()
        +_v_6_0.size()+_v_6_1.size()
        +_v_7_0.size()+_v_7_1.size();
    string _ans;
    _ans.reserve(_size);
    _ans.append("&",1);
    _ans.append(_v_0_0.data(),_v_0_0.size());
    _ans.append("=",1);
    _ans.append(_v_0_1.data(),_v_0_1.size());
    _ans.append("&",1);
    _ans.append(_v_1_0.data(),_v_1_0.size());
    _ans.append("=",1);
    _ans.append(_v_1_1.data(),_v_1_1.size());
    _ans.append("&",1);
    _ans.append(_v_2_0.data(),_v_2_0.size());
    _ans.append("=",1);
    _ans.append(_v_2_1.data(),_v_2_1.size());
    _ans.append("&",1);
    _ans.append(_v_3_0.data(),_v_3_0.size());
    _ans.append("=",1);
    _ans.append(_v_3_1.data(),_v_3_1.size());
    _ans.append("&",1);
    _ans.append(_v_4_0.data(),_v_4_0.size());
    _ans.append("=",1);
    _ans.append(_v_4_1.data(),_v_4_1.size());
    _ans.append("&",1);
    _ans.append(_v_5_0.data(),_v_5_0.size());
    _ans.append("=",1);
    _ans.append(_v_5_1.data(),_v_5_1.size());
    _ans.append("&",1);
    _ans.append(_v_6_0.data(),_v_6_0.size());
    _ans.append("=",1);
    _ans.append(_v_6_1.data(),_v_6_1.size());
    _ans.append("&",1);
    _ans.append(_v_7_0.data(),_v_7_0.size());
    _ans.append("=",1);
    _ans.append(_v_7_1.data(),_v_7_1.size());
    return std::move(_ans);
}
template<
    typename _t_0_0,typename _t_0_1,
    typename _t_1_0,typename _t_1_1,
    typename _t_2_0,typename _t_2_1,
    typename _t_3_0,typename _t_3_1,
    typename _t_4_0,typename _t_4_1,
    typename _t_5_0,typename _t_5_1,
    typename _t_6_0,typename _t_6_1,
    typename _t_7_0,typename _t_7_1,
    typename _t_8_0,typename _t_8_1
>
string __cat_to_url(const _t_0_0&_v_0_0,const _t_0_1&_v_0_1,
    const _t_1_0&_v_1_0,const _t_1_1&_v_1_1,
    const _t_2_0&_v_2_0,const _t_2_1&_v_2_1,
    const _t_3_0&_v_3_0,const _t_3_1&_v_3_1,
    const _t_4_0&_v_4_0,const _t_4_1&_v_4_1,
    const _t_5_0&_v_5_0,const _t_5_1&_v_5_1,
    const _t_6_0&_v_6_0,const _t_6_1&_v_6_1,
    const _t_7_0&_v_7_0,const _t_7_1&_v_7_1,
    const _t_8_0&_v_8_0,const _t_8_1&_v_8_1) {
    constexpr int _n=9*(2/*&=*/)+4;
    const int _size=_n
        +_v_0_0.size()+_v_0_1.size()
        +_v_1_0.size()+_v_1_1.size()
        +_v_2_0.size()+_v_2_1.size()
        +_v_3_0.size()+_v_3_1.size()
        +_v_4_0.size()+_v_4_1.size()
        +_v_5_0.size()+_v_5_1.size()
        +_v_6_0.size()+_v_6_1.size()
        +_v_7_0.size()+_v_7_1.size()
        +_v_8_0.size()+_v_8_1.size();
    string _ans;
    _ans.reserve(_size);
    _ans.append("&",1);
    _ans.append(_v_0_0.data(),_v_0_0.size());
    _ans.append("=",1);
    _ans.append(_v_0_1.data(),_v_0_1.size());
    _ans.append("&",1);
    _ans.append(_v_1_0.data(),_v_1_0.size());
    _ans.append("=",1);
    _ans.append(_v_1_1.data(),_v_1_1.size());
    _ans.append("&",1);
    _ans.append(_v_2_0.data(),_v_2_0.size());
    _ans.append("=",1);
    _ans.append(_v_2_1.data(),_v_2_1.size());
    _ans.append("&",1);
    _ans.append(_v_3_0.data(),_v_3_0.size());
    _ans.append("=",1);
    _ans.append(_v_3_1.data(),_v_3_1.size());
    _ans.append("&",1);
    _ans.append(_v_4_0.data(),_v_4_0.size());
    _ans.append("=",1);
    _ans.append(_v_4_1.data(),_v_4_1.size());
    _ans.append("&",1);
    _ans.append(_v_5_0.data(),_v_5_0.size());
    _ans.append("=",1);
    _ans.append(_v_5_1.data(),_v_5_1.size());
    _ans.append("&",1);
    _ans.append(_v_6_0.data(),_v_6_0.size());
    _ans.append("=",1);
    _ans.append(_v_6_1.data(),_v_6_1.size());
    _ans.append("&",1);
    _ans.append(_v_7_0.data(),_v_7_0.size());
    _ans.append("=",1);
    _ans.append(_v_7_1.data(),_v_7_1.size());
    _ans.append("&",1);
    _ans.append(_v_8_0.data(),_v_8_0.size());
    _ans.append("=",1);
    _ans.append(_v_8_1.data(),_v_8_1.size());
    return std::move(_ans);
}
template<
    typename _t_0_0,typename _t_0_1,
    typename _t_1_0,typename _t_1_1,
    typename _t_2_0,typename _t_2_1,
    typename _t_3_0,typename _t_3_1,
    typename _t_4_0,typename _t_4_1,
    typename _t_5_0,typename _t_5_1,
    typename _t_6_0,typename _t_6_1,
    typename _t_7_0,typename _t_7_1,
    typename _t_8_0,typename _t_8_1,
    typename _t_9_0,typename _t_9_1
>
string __cat_to_url(const _t_0_0&_v_0_0,const _t_0_1&_v_0_1,
    const _t_1_0&_v_1_0,const _t_1_1&_v_1_1,
    const _t_2_0&_v_2_0,const _t_2_1&_v_2_1,
    const _t_3_0&_v_3_0,const _t_3_1&_v_3_1,
    const _t_4_0&_v_4_0,const _t_4_1&_v_4_1,
    const _t_5_0&_v_5_0,const _t_5_1&_v_5_1,
    const _t_6_0&_v_6_0,const _t_6_1&_v_6_1,
    const _t_7_0&_v_7_0,const _t_7_1&_v_7_1,
    const _t_8_0&_v_8_0,const _t_8_1&_v_8_1,
    const _t_9_0&_v_9_0,const _t_9_1&_v_9_1) {
    constexpr int _n=10*(2/*&=*/)+4;
    const int _size=_n
        +_v_0_0.size()+_v_0_1.size()
        +_v_1_0.size()+_v_1_1.size()
        +_v_2_0.size()+_v_2_1.size()
        +_v_3_0.size()+_v_3_1.size()
        +_v_4_0.size()+_v_4_1.size()
        +_v_5_0.size()+_v_5_1.size()
        +_v_6_0.size()+_v_6_1.size()
        +_v_7_0.size()+_v_7_1.size()
        +_v_8_0.size()+_v_8_1.size()
        +_v_9_0.size()+_v_9_1.size();
    string _ans;
    _ans.reserve(_size);
    _ans.append("&",1);
    _ans.append(_v_0_0.data(),_v_0_0.size());
    _ans.append("=",1);
    _ans.append(_v_0_1.data(),_v_0_1.size());
    _ans.append("&",1);
    _ans.append(_v_1_0.data(),_v_1_0.size());
    _ans.append("=",1);
    _ans.append(_v_1_1.data(),_v_1_1.size());
    _ans.append("&",1);
    _ans.append(_v_2_0.data(),_v_2_0.size());
    _ans.append("=",1);
    _ans.append(_v_2_1.data(),_v_2_1.size());
    _ans.append("&",1);
    _ans.append(_v_3_0.data(),_v_3_0.size());
    _ans.append("=",1);
    _ans.append(_v_3_1.data(),_v_3_1.size());
    _ans.append("&",1);
    _ans.append(_v_4_0.data(),_v_4_0.size());
    _ans.append("=",1);
    _ans.append(_v_4_1.data(),_v_4_1.size());
    _ans.append("&",1);
    _ans.append(_v_5_0.data(),_v_5_0.size());
    _ans.append("=",1);
    _ans.append(_v_5_1.data(),_v_5_1.size());
    _ans.append("&",1);
    _ans.append(_v_6_0.data(),_v_6_0.size());
    _ans.append("=",1);
    _ans.append(_v_6_1.data(),_v_6_1.size());
    _ans.append("&",1);
    _ans.append(_v_7_0.data(),_v_7_0.size());
    _ans.append("=",1);
    _ans.append(_v_7_1.data(),_v_7_1.size());
    _ans.append("&",1);
    _ans.append(_v_8_0.data(),_v_8_0.size());
    _ans.append("=",1);
    _ans.append(_v_8_1.data(),_v_8_1.size());
    _ans.append("&",1);
    _ans.append(_v_9_0.data(),_v_9_0.size());
    _ans.append("=",1);
    _ans.append(_v_9_1.data(),_v_9_1.size());
    return std::move(_ans);
}
template<
    typename _t_0_0,typename _t_0_1,
    typename _t_1_0,typename _t_1_1,
    typename _t_2_0,typename _t_2_1,
    typename _t_3_0,typename _t_3_1,
    typename _t_4_0,typename _t_4_1,
    typename _t_5_0,typename _t_5_1,
    typename _t_6_0,typename _t_6_1,
    typename _t_7_0,typename _t_7_1,
    typename _t_8_0,typename _t_8_1,
    typename _t_9_0,typename _t_9_1,
    typename _t_10_0,typename _t_10_1
>
string __cat_to_url(const _t_0_0&_v_0_0,const _t_0_1&_v_0_1,
    const _t_1_0&_v_1_0,const _t_1_1&_v_1_1,
    const _t_2_0&_v_2_0,const _t_2_1&_v_2_1,
    const _t_3_0&_v_3_0,const _t_3_1&_v_3_1,
    const _t_4_0&_v_4_0,const _t_4_1&_v_4_1,
    const _t_5_0&_v_5_0,const _t_5_1&_v_5_1,
    const _t_6_0&_v_6_0,const _t_6_1&_v_6_1,
    const _t_7_0&_v_7_0,const _t_7_1&_v_7_1,
    const _t_8_0&_v_8_0,const _t_8_1&_v_8_1,
    const _t_9_0&_v_9_0,const _t_9_1&_v_9_1,
    const _t_10_0&_v_10_0,const _t_10_1&_v_10_1) {
    constexpr int _n=11*(2/*&=*/)+4;
    const int _size=_n
        +_v_0_0.size()+_v_0_1.size()
        +_v_1_0.size()+_v_1_1.size()
        +_v_2_0.size()+_v_2_1.size()
        +_v_3_0.size()+_v_3_1.size()
        +_v_4_0.size()+_v_4_1.size()
        +_v_5_0.size()+_v_5_1.size()
        +_v_6_0.size()+_v_6_1.size()
        +_v_7_0.size()+_v_7_1.size()
        +_v_8_0.size()+_v_8_1.size()
        +_v_9_0.size()+_v_9_1.size()
        +_v_10_0.size()+_v_10_1.size();
    string _ans;
    _ans.reserve(_size);
    _ans.append("&",1);
    _ans.append(_v_0_0.data(),_v_0_0.size());
    _ans.append("=",1);
    _ans.append(_v_0_1.data(),_v_0_1.size());
    _ans.append("&",1);
    _ans.append(_v_1_0.data(),_v_1_0.size());
    _ans.append("=",1);
    _ans.append(_v_1_1.data(),_v_1_1.size());
    _ans.append("&",1);
    _ans.append(_v_2_0.data(),_v_2_0.size());
    _ans.append("=",1);
    _ans.append(_v_2_1.data(),_v_2_1.size());
    _ans.append("&",1);
    _ans.append(_v_3_0.data(),_v_3_0.size());
    _ans.append("=",1);
    _ans.append(_v_3_1.data(),_v_3_1.size());
    _ans.append("&",1);
    _ans.append(_v_4_0.data(),_v_4_0.size());
    _ans.append("=",1);
    _ans.append(_v_4_1.data(),_v_4_1.size());
    _ans.append("&",1);
    _ans.append(_v_5_0.data(),_v_5_0.size());
    _ans.append("=",1);
    _ans.append(_v_5_1.data(),_v_5_1.size());
    _ans.append("&",1);
    _ans.append(_v_6_0.data(),_v_6_0.size());
    _ans.append("=",1);
    _ans.append(_v_6_1.data(),_v_6_1.size());
    _ans.append("&",1);
    _ans.append(_v_7_0.data(),_v_7_0.size());
    _ans.append("=",1);
    _ans.append(_v_7_1.data(),_v_7_1.size());
    _ans.append("&",1);
    _ans.append(_v_8_0.data(),_v_8_0.size());
    _ans.append("=",1);
    _ans.append(_v_8_1.data(),_v_8_1.size());
    _ans.append("&",1);
    _ans.append(_v_9_0.data(),_v_9_0.size());
    _ans.append("=",1);
    _ans.append(_v_9_1.data(),_v_9_1.size());
    _ans.append("&",1);
    _ans.append(_v_10_0.data(),_v_10_0.size());
    _ans.append("=",1);
    _ans.append(_v_10_1.data(),_v_10_1.size());
    return std::move(_ans);
}
template<
    typename _t_0_0,typename _t_0_1,
    typename _t_1_0,typename _t_1_1,
    typename _t_2_0,typename _t_2_1,
    typename _t_3_0,typename _t_3_1,
    typename _t_4_0,typename _t_4_1,
    typename _t_5_0,typename _t_5_1,
    typename _t_6_0,typename _t_6_1,
    typename _t_7_0,typename _t_7_1,
    typename _t_8_0,typename _t_8_1,
    typename _t_9_0,typename _t_9_1,
    typename _t_10_0,typename _t_10_1,
    typename _t_11_0,typename _t_11_1
>
string __cat_to_url(const _t_0_0&_v_0_0,const _t_0_1&_v_0_1,
    const _t_1_0&_v_1_0,const _t_1_1&_v_1_1,
    const _t_2_0&_v_2_0,const _t_2_1&_v_2_1,
    const _t_3_0&_v_3_0,const _t_3_1&_v_3_1,
    const _t_4_0&_v_4_0,const _t_4_1&_v_4_1,
    const _t_5_0&_v_5_0,const _t_5_1&_v_5_1,
    const _t_6_0&_v_6_0,const _t_6_1&_v_6_1,
    const _t_7_0&_v_7_0,const _t_7_1&_v_7_1,
    const _t_8_0&_v_8_0,const _t_8_1&_v_8_1,
    const _t_9_0&_v_9_0,const _t_9_1&_v_9_1,
    const _t_10_0&_v_10_0,const _t_10_1&_v_10_1,
    const _t_11_0&_v_11_0,const _t_11_1&_v_11_1) {
    constexpr int _n=12*(2/*&=*/)+4;
    const int _size=_n
        +_v_0_0.size()+_v_0_1.size()
        +_v_1_0.size()+_v_1_1.size()
        +_v_2_0.size()+_v_2_1.size()
        +_v_3_0.size()+_v_3_1.size()
        +_v_4_0.size()+_v_4_1.size()
        +_v_5_0.size()+_v_5_1.size()
        +_v_6_0.size()+_v_6_1.size()
        +_v_7_0.size()+_v_7_1.size()
        +_v_8_0.size()+_v_8_1.size()
        +_v_9_0.size()+_v_9_1.size()
        +_v_10_0.size()+_v_10_1.size()
        +_v_11_0.size()+_v_11_1.size();
    string _ans;
    _ans.reserve(_size);
    _ans.append("&",1);
    _ans.append(_v_0_0.data(),_v_0_0.size());
    _ans.append("=",1);
    _ans.append(_v_0_1.data(),_v_0_1.size());
    _ans.append("&",1);
    _ans.append(_v_1_0.data(),_v_1_0.size());
    _ans.append("=",1);
    _ans.append(_v_1_1.data(),_v_1_1.size());
    _ans.append("&",1);
    _ans.append(_v_2_0.data(),_v_2_0.size());
    _ans.append("=",1);
    _ans.append(_v_2_1.data(),_v_2_1.size());
    _ans.append("&",1);
    _ans.append(_v_3_0.data(),_v_3_0.size());
    _ans.append("=",1);
    _ans.append(_v_3_1.data(),_v_3_1.size());
    _ans.append("&",1);
    _ans.append(_v_4_0.data(),_v_4_0.size());
    _ans.append("=",1);
    _ans.append(_v_4_1.data(),_v_4_1.size());
    _ans.append("&",1);
    _ans.append(_v_5_0.data(),_v_5_0.size());
    _ans.append("=",1);
    _ans.append(_v_5_1.data(),_v_5_1.size());
    _ans.append("&",1);
    _ans.append(_v_6_0.data(),_v_6_0.size());
    _ans.append("=",1);
    _ans.append(_v_6_1.data(),_v_6_1.size());
    _ans.append("&",1);
    _ans.append(_v_7_0.data(),_v_7_0.size());
    _ans.append("=",1);
    _ans.append(_v_7_1.data(),_v_7_1.size());
    _ans.append("&",1);
    _ans.append(_v_8_0.data(),_v_8_0.size());
    _ans.append("=",1);
    _ans.append(_v_8_1.data(),_v_8_1.size());
    _ans.append("&",1);
    _ans.append(_v_9_0.data(),_v_9_0.size());
    _ans.append("=",1);
    _ans.append(_v_9_1.data(),_v_9_1.size());
    _ans.append("&",1);
    _ans.append(_v_10_0.data(),_v_10_0.size());
    _ans.append("=",1);
    _ans.append(_v_10_1.data(),_v_10_1.size());
    _ans.append("&",1);
    _ans.append(_v_11_0.data(),_v_11_0.size());
    _ans.append("=",1);
    _ans.append(_v_11_1.data(),_v_11_1.size());
    return std::move(_ans);
}
template<
    typename _t_0_0,typename _t_0_1,
    typename _t_1_0,typename _t_1_1,
    typename _t_2_0,typename _t_2_1,
    typename _t_3_0,typename _t_3_1,
    typename _t_4_0,typename _t_4_1,
    typename _t_5_0,typename _t_5_1,
    typename _t_6_0,typename _t_6_1,
    typename _t_7_0,typename _t_7_1,
    typename _t_8_0,typename _t_8_1,
    typename _t_9_0,typename _t_9_1,
    typename _t_10_0,typename _t_10_1,
    typename _t_11_0,typename _t_11_1,
    typename _t_12_0,typename _t_12_1
>
string __cat_to_url(const _t_0_0&_v_0_0,const _t_0_1&_v_0_1,
    const _t_1_0&_v_1_0,const _t_1_1&_v_1_1,
    const _t_2_0&_v_2_0,const _t_2_1&_v_2_1,
    const _t_3_0&_v_3_0,const _t_3_1&_v_3_1,
    const _t_4_0&_v_4_0,const _t_4_1&_v_4_1,
    const _t_5_0&_v_5_0,const _t_5_1&_v_5_1,
    const _t_6_0&_v_6_0,const _t_6_1&_v_6_1,
    const _t_7_0&_v_7_0,const _t_7_1&_v_7_1,
    const _t_8_0&_v_8_0,const _t_8_1&_v_8_1,
    const _t_9_0&_v_9_0,const _t_9_1&_v_9_1,
    const _t_10_0&_v_10_0,const _t_10_1&_v_10_1,
    const _t_11_0&_v_11_0,const _t_11_1&_v_11_1,
    const _t_12_0&_v_12_0,const _t_12_1&_v_12_1) {
    constexpr int _n=13*(2/*&=*/)+4;
    const int _size=_n
        +_v_0_0.size()+_v_0_1.size()
        +_v_1_0.size()+_v_1_1.size()
        +_v_2_0.size()+_v_2_1.size()
        +_v_3_0.size()+_v_3_1.size()
        +_v_4_0.size()+_v_4_1.size()
        +_v_5_0.size()+_v_5_1.size()
        +_v_6_0.size()+_v_6_1.size()
        +_v_7_0.size()+_v_7_1.size()
        +_v_8_0.size()+_v_8_1.size()
        +_v_9_0.size()+_v_9_1.size()
        +_v_10_0.size()+_v_10_1.size()
        +_v_11_0.size()+_v_11_1.size()
        +_v_12_0.size()+_v_12_1.size();
    string _ans;
    _ans.reserve(_size);
    _ans.append("&",1);
    _ans.append(_v_0_0.data(),_v_0_0.size());
    _ans.append("=",1);
    _ans.append(_v_0_1.data(),_v_0_1.size());
    _ans.append("&",1);
    _ans.append(_v_1_0.data(),_v_1_0.size());
    _ans.append("=",1);
    _ans.append(_v_1_1.data(),_v_1_1.size());
    _ans.append("&",1);
    _ans.append(_v_2_0.data(),_v_2_0.size());
    _ans.append("=",1);
    _ans.append(_v_2_1.data(),_v_2_1.size());
    _ans.append("&",1);
    _ans.append(_v_3_0.data(),_v_3_0.size());
    _ans.append("=",1);
    _ans.append(_v_3_1.data(),_v_3_1.size());
    _ans.append("&",1);
    _ans.append(_v_4_0.data(),_v_4_0.size());
    _ans.append("=",1);
    _ans.append(_v_4_1.data(),_v_4_1.size());
    _ans.append("&",1);
    _ans.append(_v_5_0.data(),_v_5_0.size());
    _ans.append("=",1);
    _ans.append(_v_5_1.data(),_v_5_1.size());
    _ans.append("&",1);
    _ans.append(_v_6_0.data(),_v_6_0.size());
    _ans.append("=",1);
    _ans.append(_v_6_1.data(),_v_6_1.size());
    _ans.append("&",1);
    _ans.append(_v_7_0.data(),_v_7_0.size());
    _ans.append("=",1);
    _ans.append(_v_7_1.data(),_v_7_1.size());
    _ans.append("&",1);
    _ans.append(_v_8_0.data(),_v_8_0.size());
    _ans.append("=",1);
    _ans.append(_v_8_1.data(),_v_8_1.size());
    _ans.append("&",1);
    _ans.append(_v_9_0.data(),_v_9_0.size());
    _ans.append("=",1);
    _ans.append(_v_9_1.data(),_v_9_1.size());
    _ans.append("&",1);
    _ans.append(_v_10_0.data(),_v_10_0.size());
    _ans.append("=",1);
    _ans.append(_v_10_1.data(),_v_10_1.size());
    _ans.append("&",1);
    _ans.append(_v_11_0.data(),_v_11_0.size());
    _ans.append("=",1);
    _ans.append(_v_11_1.data(),_v_11_1.size());
    _ans.append("&",1);
    _ans.append(_v_12_0.data(),_v_12_0.size());
    _ans.append("=",1);
    _ans.append(_v_12_1.data(),_v_12_1.size());
    return std::move(_ans);
}
template<
    typename _t_0_0,typename _t_0_1,
    typename _t_1_0,typename _t_1_1,
    typename _t_2_0,typename _t_2_1,
    typename _t_3_0,typename _t_3_1,
    typename _t_4_0,typename _t_4_1,
    typename _t_5_0,typename _t_5_1,
    typename _t_6_0,typename _t_6_1,
    typename _t_7_0,typename _t_7_1,
    typename _t_8_0,typename _t_8_1,
    typename _t_9_0,typename _t_9_1,
    typename _t_10_0,typename _t_10_1,
    typename _t_11_0,typename _t_11_1,
    typename _t_12_0,typename _t_12_1,
    typename _t_13_0,typename _t_13_1
>
string __cat_to_url(const _t_0_0&_v_0_0,const _t_0_1&_v_0_1,
    const _t_1_0&_v_1_0,const _t_1_1&_v_1_1,
    const _t_2_0&_v_2_0,const _t_2_1&_v_2_1,
    const _t_3_0&_v_3_0,const _t_3_1&_v_3_1,
    const _t_4_0&_v_4_0,const _t_4_1&_v_4_1,
    const _t_5_0&_v_5_0,const _t_5_1&_v_5_1,
    const _t_6_0&_v_6_0,const _t_6_1&_v_6_1,
    const _t_7_0&_v_7_0,const _t_7_1&_v_7_1,
    const _t_8_0&_v_8_0,const _t_8_1&_v_8_1,
    const _t_9_0&_v_9_0,const _t_9_1&_v_9_1,
    const _t_10_0&_v_10_0,const _t_10_1&_v_10_1,
    const _t_11_0&_v_11_0,const _t_11_1&_v_11_1,
    const _t_12_0&_v_12_0,const _t_12_1&_v_12_1,
    const _t_13_0&_v_13_0,const _t_13_1&_v_13_1) {
    constexpr int _n=14*(2/*&=*/)+4;
    const int _size=_n
        +_v_0_0.size()+_v_0_1.size()
        +_v_1_0.size()+_v_1_1.size()
        +_v_2_0.size()+_v_2_1.size()
        +_v_3_0.size()+_v_3_1.size()
        +_v_4_0.size()+_v_4_1.size()
        +_v_5_0.size()+_v_5_1.size()
        +_v_6_0.size()+_v_6_1.size()
        +_v_7_0.size()+_v_7_1.size()
        +_v_8_0.size()+_v_8_1.size()
        +_v_9_0.size()+_v_9_1.size()
        +_v_10_0.size()+_v_10_1.size()
        +_v_11_0.size()+_v_11_1.size()
        +_v_12_0.size()+_v_12_1.size()
        +_v_13_0.size()+_v_13_1.size();
    string _ans;
    _ans.reserve(_size);
    _ans.append("&",1);
    _ans.append(_v_0_0.data(),_v_0_0.size());
    _ans.append("=",1);
    _ans.append(_v_0_1.data(),_v_0_1.size());
    _ans.append("&",1);
    _ans.append(_v_1_0.data(),_v_1_0.size());
    _ans.append("=",1);
    _ans.append(_v_1_1.data(),_v_1_1.size());
    _ans.append("&",1);
    _ans.append(_v_2_0.data(),_v_2_0.size());
    _ans.append("=",1);
    _ans.append(_v_2_1.data(),_v_2_1.size());
    _ans.append("&",1);
    _ans.append(_v_3_0.data(),_v_3_0.size());
    _ans.append("=",1);
    _ans.append(_v_3_1.data(),_v_3_1.size());
    _ans.append("&",1);
    _ans.append(_v_4_0.data(),_v_4_0.size());
    _ans.append("=",1);
    _ans.append(_v_4_1.data(),_v_4_1.size());
    _ans.append("&",1);
    _ans.append(_v_5_0.data(),_v_5_0.size());
    _ans.append("=",1);
    _ans.append(_v_5_1.data(),_v_5_1.size());
    _ans.append("&",1);
    _ans.append(_v_6_0.data(),_v_6_0.size());
    _ans.append("=",1);
    _ans.append(_v_6_1.data(),_v_6_1.size());
    _ans.append("&",1);
    _ans.append(_v_7_0.data(),_v_7_0.size());
    _ans.append("=",1);
    _ans.append(_v_7_1.data(),_v_7_1.size());
    _ans.append("&",1);
    _ans.append(_v_8_0.data(),_v_8_0.size());
    _ans.append("=",1);
    _ans.append(_v_8_1.data(),_v_8_1.size());
    _ans.append("&",1);
    _ans.append(_v_9_0.data(),_v_9_0.size());
    _ans.append("=",1);
    _ans.append(_v_9_1.data(),_v_9_1.size());
    _ans.append("&",1);
    _ans.append(_v_10_0.data(),_v_10_0.size());
    _ans.append("=",1);
    _ans.append(_v_10_1.data(),_v_10_1.size());
    _ans.append("&",1);
    _ans.append(_v_11_0.data(),_v_11_0.size());
    _ans.append("=",1);
    _ans.append(_v_11_1.data(),_v_11_1.size());
    _ans.append("&",1);
    _ans.append(_v_12_0.data(),_v_12_0.size());
    _ans.append("=",1);
    _ans.append(_v_12_1.data(),_v_12_1.size());
    _ans.append("&",1);
    _ans.append(_v_13_0.data(),_v_13_0.size());
    _ans.append("=",1);
    _ans.append(_v_13_1.data(),_v_13_1.size());
    return std::move(_ans);
}
template<
    typename _t_0_0,typename _t_0_1,
    typename _t_1_0,typename _t_1_1,
    typename _t_2_0,typename _t_2_1,
    typename _t_3_0,typename _t_3_1,
    typename _t_4_0,typename _t_4_1,
    typename _t_5_0,typename _t_5_1,
    typename _t_6_0,typename _t_6_1,
    typename _t_7_0,typename _t_7_1,
    typename _t_8_0,typename _t_8_1,
    typename _t_9_0,typename _t_9_1,
    typename _t_10_0,typename _t_10_1,
    typename _t_11_0,typename _t_11_1,
    typename _t_12_0,typename _t_12_1,
    typename _t_13_0,typename _t_13_1,
    typename _t_14_0,typename _t_14_1
>
string __cat_to_url(const _t_0_0&_v_0_0,const _t_0_1&_v_0_1,
    const _t_1_0&_v_1_0,const _t_1_1&_v_1_1,
    const _t_2_0&_v_2_0,const _t_2_1&_v_2_1,
    const _t_3_0&_v_3_0,const _t_3_1&_v_3_1,
    const _t_4_0&_v_4_0,const _t_4_1&_v_4_1,
    const _t_5_0&_v_5_0,const _t_5_1&_v_5_1,
    const _t_6_0&_v_6_0,const _t_6_1&_v_6_1,
    const _t_7_0&_v_7_0,const _t_7_1&_v_7_1,
    const _t_8_0&_v_8_0,const _t_8_1&_v_8_1,
    const _t_9_0&_v_9_0,const _t_9_1&_v_9_1,
    const _t_10_0&_v_10_0,const _t_10_1&_v_10_1,
    const _t_11_0&_v_11_0,const _t_11_1&_v_11_1,
    const _t_12_0&_v_12_0,const _t_12_1&_v_12_1,
    const _t_13_0&_v_13_0,const _t_13_1&_v_13_1,
    const _t_14_0&_v_14_0,const _t_14_1&_v_14_1) {
    constexpr int _n=15*(2/*&=*/)+4;
    const int _size=_n
        +_v_0_0.size()+_v_0_1.size()
        +_v_1_0.size()+_v_1_1.size()
        +_v_2_0.size()+_v_2_1.size()
        +_v_3_0.size()+_v_3_1.size()
        +_v_4_0.size()+_v_4_1.size()
        +_v_5_0.size()+_v_5_1.size()
        +_v_6_0.size()+_v_6_1.size()
        +_v_7_0.size()+_v_7_1.size()
        +_v_8_0.size()+_v_8_1.size()
        +_v_9_0.size()+_v_9_1.size()
        +_v_10_0.size()+_v_10_1.size()
        +_v_11_0.size()+_v_11_1.size()
        +_v_12_0.size()+_v_12_1.size()
        +_v_13_0.size()+_v_13_1.size()
        +_v_14_0.size()+_v_14_1.size();
    string _ans;
    _ans.reserve(_size);
    _ans.append("&",1);
    _ans.append(_v_0_0.data(),_v_0_0.size());
    _ans.append("=",1);
    _ans.append(_v_0_1.data(),_v_0_1.size());
    _ans.append("&",1);
    _ans.append(_v_1_0.data(),_v_1_0.size());
    _ans.append("=",1);
    _ans.append(_v_1_1.data(),_v_1_1.size());
    _ans.append("&",1);
    _ans.append(_v_2_0.data(),_v_2_0.size());
    _ans.append("=",1);
    _ans.append(_v_2_1.data(),_v_2_1.size());
    _ans.append("&",1);
    _ans.append(_v_3_0.data(),_v_3_0.size());
    _ans.append("=",1);
    _ans.append(_v_3_1.data(),_v_3_1.size());
    _ans.append("&",1);
    _ans.append(_v_4_0.data(),_v_4_0.size());
    _ans.append("=",1);
    _ans.append(_v_4_1.data(),_v_4_1.size());
    _ans.append("&",1);
    _ans.append(_v_5_0.data(),_v_5_0.size());
    _ans.append("=",1);
    _ans.append(_v_5_1.data(),_v_5_1.size());
    _ans.append("&",1);
    _ans.append(_v_6_0.data(),_v_6_0.size());
    _ans.append("=",1);
    _ans.append(_v_6_1.data(),_v_6_1.size());
    _ans.append("&",1);
    _ans.append(_v_7_0.data(),_v_7_0.size());
    _ans.append("=",1);
    _ans.append(_v_7_1.data(),_v_7_1.size());
    _ans.append("&",1);
    _ans.append(_v_8_0.data(),_v_8_0.size());
    _ans.append("=",1);
    _ans.append(_v_8_1.data(),_v_8_1.size());
    _ans.append("&",1);
    _ans.append(_v_9_0.data(),_v_9_0.size());
    _ans.append("=",1);
    _ans.append(_v_9_1.data(),_v_9_1.size());
    _ans.append("&",1);
    _ans.append(_v_10_0.data(),_v_10_0.size());
    _ans.append("=",1);
    _ans.append(_v_10_1.data(),_v_10_1.size());
    _ans.append("&",1);
    _ans.append(_v_11_0.data(),_v_11_0.size());
    _ans.append("=",1);
    _ans.append(_v_11_1.data(),_v_11_1.size());
    _ans.append("&",1);
    _ans.append(_v_12_0.data(),_v_12_0.size());
    _ans.append("=",1);
    _ans.append(_v_12_1.data(),_v_12_1.size());
    _ans.append("&",1);
    _ans.append(_v_13_0.data(),_v_13_0.size());
    _ans.append("=",1);
    _ans.append(_v_13_1.data(),_v_13_1.size());
    _ans.append("&",1);
    _ans.append(_v_14_0.data(),_v_14_0.size());
    _ans.append("=",1);
    _ans.append(_v_14_1.data(),_v_14_1.size());
    return std::move(_ans);
}
template<
    typename _t_0_0,typename _t_0_1,
    typename _t_1_0,typename _t_1_1,
    typename _t_2_0,typename _t_2_1,
    typename _t_3_0,typename _t_3_1,
    typename _t_4_0,typename _t_4_1,
    typename _t_5_0,typename _t_5_1,
    typename _t_6_0,typename _t_6_1,
    typename _t_7_0,typename _t_7_1,
    typename _t_8_0,typename _t_8_1,
    typename _t_9_0,typename _t_9_1,
    typename _t_10_0,typename _t_10_1,
    typename _t_11_0,typename _t_11_1,
    typename _t_12_0,typename _t_12_1,
    typename _t_13_0,typename _t_13_1,
    typename _t_14_0,typename _t_14_1,
    typename _t_15_0,typename _t_15_1
>
string __cat_to_url(const _t_0_0&_v_0_0,const _t_0_1&_v_0_1,
    const _t_1_0&_v_1_0,const _t_1_1&_v_1_1,
    const _t_2_0&_v_2_0,const _t_2_1&_v_2_1,
    const _t_3_0&_v_3_0,const _t_3_1&_v_3_1,
    const _t_4_0&_v_4_0,const _t_4_1&_v_4_1,
    const _t_5_0&_v_5_0,const _t_5_1&_v_5_1,
    const _t_6_0&_v_6_0,const _t_6_1&_v_6_1,
    const _t_7_0&_v_7_0,const _t_7_1&_v_7_1,
    const _t_8_0&_v_8_0,const _t_8_1&_v_8_1,
    const _t_9_0&_v_9_0,const _t_9_1&_v_9_1,
    const _t_10_0&_v_10_0,const _t_10_1&_v_10_1,
    const _t_11_0&_v_11_0,const _t_11_1&_v_11_1,
    const _t_12_0&_v_12_0,const _t_12_1&_v_12_1,
    const _t_13_0&_v_13_0,const _t_13_1&_v_13_1,
    const _t_14_0&_v_14_0,const _t_14_1&_v_14_1,
    const _t_15_0&_v_15_0,const _t_15_1&_v_15_1) {
    constexpr int _n=16*(2/*&=*/)+4;
    const int _size=_n
        +_v_0_0.size()+_v_0_1.size()
        +_v_1_0.size()+_v_1_1.size()
        +_v_2_0.size()+_v_2_1.size()
        +_v_3_0.size()+_v_3_1.size()
        +_v_4_0.size()+_v_4_1.size()
        +_v_5_0.size()+_v_5_1.size()
        +_v_6_0.size()+_v_6_1.size()
        +_v_7_0.size()+_v_7_1.size()
        +_v_8_0.size()+_v_8_1.size()
        +_v_9_0.size()+_v_9_1.size()
        +_v_10_0.size()+_v_10_1.size()
        +_v_11_0.size()+_v_11_1.size()
        +_v_12_0.size()+_v_12_1.size()
        +_v_13_0.size()+_v_13_1.size()
        +_v_14_0.size()+_v_14_1.size()
        +_v_15_0.size()+_v_15_1.size();
    string _ans;
    _ans.reserve(_size);
    _ans.append("&",1);
    _ans.append(_v_0_0.data(),_v_0_0.size());
    _ans.append("=",1);
    _ans.append(_v_0_1.data(),_v_0_1.size());
    _ans.append("&",1);
    _ans.append(_v_1_0.data(),_v_1_0.size());
    _ans.append("=",1);
    _ans.append(_v_1_1.data(),_v_1_1.size());
    _ans.append("&",1);
    _ans.append(_v_2_0.data(),_v_2_0.size());
    _ans.append("=",1);
    _ans.append(_v_2_1.data(),_v_2_1.size());
    _ans.append("&",1);
    _ans.append(_v_3_0.data(),_v_3_0.size());
    _ans.append("=",1);
    _ans.append(_v_3_1.data(),_v_3_1.size());
    _ans.append("&",1);
    _ans.append(_v_4_0.data(),_v_4_0.size());
    _ans.append("=",1);
    _ans.append(_v_4_1.data(),_v_4_1.size());
    _ans.append("&",1);
    _ans.append(_v_5_0.data(),_v_5_0.size());
    _ans.append("=",1);
    _ans.append(_v_5_1.data(),_v_5_1.size());
    _ans.append("&",1);
    _ans.append(_v_6_0.data(),_v_6_0.size());
    _ans.append("=",1);
    _ans.append(_v_6_1.data(),_v_6_1.size());
    _ans.append("&",1);
    _ans.append(_v_7_0.data(),_v_7_0.size());
    _ans.append("=",1);
    _ans.append(_v_7_1.data(),_v_7_1.size());
    _ans.append("&",1);
    _ans.append(_v_8_0.data(),_v_8_0.size());
    _ans.append("=",1);
    _ans.append(_v_8_1.data(),_v_8_1.size());
    _ans.append("&",1);
    _ans.append(_v_9_0.data(),_v_9_0.size());
    _ans.append("=",1);
    _ans.append(_v_9_1.data(),_v_9_1.size());
    _ans.append("&",1);
    _ans.append(_v_10_0.data(),_v_10_0.size());
    _ans.append("=",1);
    _ans.append(_v_10_1.data(),_v_10_1.size());
    _ans.append("&",1);
    _ans.append(_v_11_0.data(),_v_11_0.size());
    _ans.append("=",1);
    _ans.append(_v_11_1.data(),_v_11_1.size());
    _ans.append("&",1);
    _ans.append(_v_12_0.data(),_v_12_0.size());
    _ans.append("=",1);
    _ans.append(_v_12_1.data(),_v_12_1.size());
    _ans.append("&",1);
    _ans.append(_v_13_0.data(),_v_13_0.size());
    _ans.append("=",1);
    _ans.append(_v_13_1.data(),_v_13_1.size());
    _ans.append("&",1);
    _ans.append(_v_14_0.data(),_v_14_0.size());
    _ans.append("=",1);
    _ans.append(_v_14_1.data(),_v_14_1.size());
    _ans.append("&",1);
    _ans.append(_v_15_0.data(),_v_15_0.size());
    _ans.append("=",1);
    _ans.append(_v_15_1.data(),_v_15_1.size());
    return std::move(_ans);
}
}/*namespace utility_cpp14*/
/******************************************************************/

/* &a=b */
template<typename ..._T_>
string cat_to_url(const _T_&...arg) {
    return utility_cpp14::__cat_to_url(make_string_ref(arg)...);
}

}/*namespace*/

template<>
inline auto getThisData<zone_data::BaiDuUserData *,0>(const BaiDuUser * arg) ->zone_data::BaiDuUserData * {
    return const_cast<BaiDuUser *>(arg)->thisData();
}

template<>
inline auto getThisData<const zone_data::BaiDuUserData *,1>(const BaiDuUser * arg) ->const zone_data::BaiDuUserData *{
    return arg->thisData();
}

#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * varThisData=getThisData<zone_data::BaiDuUserData *,0>(_v_)
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * varThisData=getThisData<const zone_data::BaiDuUserData *,1>(_v_)
#endif

namespace zone_data {
/********************************zone_data********************************/
BaiDuUserData::BaiDuUserData() {
    static_assert(
        std::has_virtual_destructor<BaiDuUserData>::value,
        "the class must has virtual destructor");

    _m_NetworkCookieJar=new NetworkCookieJar(&_m_NetworkAccessManager);
    _m_NetworkAccessManager.setCookieJar(_m_NetworkCookieJar);
}


BaiDuUserData::~BaiDuUserData() {
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

/********************************zone_function********************************/
}

BaiDuUser::~BaiDuUser() {
    close();
}

BaiDuUser::BaiDuUser():BaiDuUser(ThisDataType(
    new zone_data::BaiDuUserData,
    [](auto *arg) {delete arg; },memory::Allocator<int>{})) {
}

BaiDuUser::BaiDuUser(ThisDataType && _arg_):
    thisData_(std::move(_arg_)) {
}

auto BaiDuUser::thisData()->zone_data::BaiDuUserData * {
    return static_cast<zone_data::BaiDuUserData *>(thisData_.get());
}

auto BaiDuUser::thisData() const->const zone_data::BaiDuUserData *{
    return static_cast<const zone_data::BaiDuUserData *>(thisData_.get());
}

void BaiDuUser::open(const QString&arg) {
    zone_this_data(this);
    if (isOpen()) { return; }
    varThisData->_m_BaiDuUserCache.setFileName(arg);
    varThisData->_m_BaiDuUserCache.open();
}

void BaiDuUser::close() {
    zone_this_data(this);
    varThisData->_m_BaiDuUserCache.write();
    varThisData->_m_BaiDuUserCache={};
}

void BaiDuUser::setUserName(const QString&arg) {
    zone_this_data(this);
    varThisData->_m_BaiDuUserCache.setUserName(arg);
}

void BaiDuUser::setPassWord(const QString&arg) {
    zone_this_data(this);
    varThisData->_m_BaiDuUserCache.setPassWord(arg);
}

QString BaiDuUser::getUsername()const {
    zone_const_this_data(this);
    return varThisData->_m_BaiDuUserCache.getUserName();
}

QString BaiDuUser::getPassword()const {
    zone_const_this_data(this);
    return varThisData->_m_BaiDuUserCache.getPassWord();
}

bool BaiDuUser::isOpen() const {
    zone_const_this_data(this);
    return varThisData->_m_BaiDuUserCache.isOpen();
}

namespace __login {
namespace {

class Login final :
    public BaiDuUser::StepNext,
    public std::enable_shared_from_this<Login> {
    Login(const Login&)=delete;
    Login(Login&&)=delete;
    Login&operator=(const Login&)=delete;
    Login&operator=(Login&&)=delete;
public:
    Login() {}
    std::weak_ptr<BaiDuUser> baiDuUser;

    enum LogInSteps :int {
        s_error,
        s_start,s_getbaidu_cookie=s_start,
        s_get_baidu_token,
        s_finished
    };

    static QString step_to_string(LogInSteps arg) {
        switch (arg) {
            case s_error:return "error"_qsl; break;
            case s_start:return "get baidu cookie"_qsl; break;
            case s_get_baidu_token:return "getBaiduToken"_qsl; break;
            case s_finished:return "finished"_qsl; break;
            default:break;
        }
        return "unknow step"_qsl;
    }

    LogInSteps loginStep=s_start;
    LogInSteps loginStepNext=s_start;
    QString errorString{ "unknow error"_qsl };
    bool logInFinishedCalled=false;

    class StaticData_getBaiduToken {
    public:
        const QByteArray url;
        const QByteArray userAgent;
        const QString zero;
        StaticData_getBaiduToken() 
            :url(u8R"(https://passport.baidu.com/v2/api/?getapi)"_qb)
            ,userAgent("User-Agent"_qb)
            ,zero("0"_qsl){}
    };
    static char _psd_getBaiduToken[sizeof(StaticData_getBaiduToken)];
    void getBaiduToken() {

        loginStep=s_get_baidu_token;

        /*静态数据*/
        static memory::StaticPoionter<StaticData_getBaiduToken> 
            _psd_(_psd_getBaiduToken);

        auto varBaiDuUser=baiDuUser.lock();
        if (false==varBaiDuUser) { return; }

        zone_this_data(varBaiDuUser.get());
        
        QUrl varUrl;
        {/*set url*/
            const auto url_=cat_to_url(
                "tpl","mn",
                "apiver","v3",
                "tt",BaiDuUser::currentTime(),
                "class","login",
                "gid",varBaiDuUser->gid(),
                "logintype","dialogLogin",
                "callback","bd__cbs__89tioq"
            );
            QByteArray varTmpUrl;
            varTmpUrl.reserve(4
                +_psd_->url.size()
                +static_cast<int>(url_.size()));
            varTmpUrl.append(_psd_->url);
            varTmpUrl.append(url_.c_str(),static_cast<int>(url_.size()));
            varUrl.setUrl(varTmpUrl);
        }

        QNetworkRequest varRequest(varUrl);
        varRequest.setRawHeader(_psd_->userAgent,BaiDuUser::userAgent());
        
        auto varReply=varThisData->_m_NetworkAccessManager.get(varRequest);
        varReply->connect(varReply,&QNetworkReply::finished,
            [varLockThis=this->shared_from_this(),varReply,this]() {

                {
                    varReply->deleteLater();
                    auto varBaiDuUser=baiDuUser.lock();
                    if (false==varBaiDuUser) { return; }

                    auto json=varReply->readAll();
                    varReply->close();

                    /*remove ()*/
                    json=json.mid(json.indexOf("("_qsl)+1);
                    json.resize(json.size()-1);

                    /*读取error 和 token*/
                    QScriptEngine eng;
                    eng.evaluate("var bd__cbs__89tioq = "_qsl+json);
                    auto error=eng.evaluate(u8R"(bd__cbs__89tioq["errInfo"]["no"])"_qsl).toString();
                    auto token=eng.evaluate(u8R"(bd__cbs__89tioq["data"]["token"])"_qsl).toString();

                    if (error==_psd_->zero) {

                    }
                    else {
                        loginStepNext=s_error;
                        errorString="can not find token"_qsl;
                    }

                }
                
                this->next_step();

        });
    }

    void next_step() {
        switch (loginStepNext) {
            case s_error:login_error(); break;
            case s_start:getBaiDuCookie(); break;
            case s_get_baidu_token:getBaiduToken(); break;
            case s_finished:login_finished(); break;
        }
    }

    void next() override {
        next_step();
    }

    void login_error() {
        logInFinishedCalled=true;
        auto var_step_name=step_to_string(loginStep);
        auto varBaiDuUser=baiDuUser.lock();
        if (false==varBaiDuUser) { return; }
        varBaiDuUser->loginFinished(false,
            "login error@"_qsl
            +std::move(var_step_name)
            +" : "_qsl
            +std::move(errorString)
        );
    }

    void login_finished() {
        logInFinishedCalled=true;
        loginStep=s_finished;
        loginStepNext=s_finished;
        auto varBaiDuUser=baiDuUser.lock();
        if (false==varBaiDuUser) { return; }
        varBaiDuUser->loginFinished(true,{});
    }

    class StaticData_getBaiDuCookie {
    public:
        QUrl baidu_url;
        QByteArray key_user_agent;
        StaticData_getBaiDuCookie():
            baidu_url(QString("http://www.baidu.com")),
            key_user_agent("User-Agent"_qb) {
        }
    };
    static char _psd_getBaiDuCookie[sizeof(StaticData_getBaiDuCookie)];
    void getBaiDuCookie() {
        static memory::StaticPoionter<StaticData_getBaiDuCookie> varStaticData{
            _psd_getBaiDuCookie };

        loginStep=s_start;

        /*初始化请求*/
        QNetworkRequest varRequest;
        varRequest.setUrl(varStaticData->baidu_url);
        varRequest.setRawHeader(varStaticData->key_user_agent,BaiDuUser::userAgent());

        /*获得baidu user*/
        auto varBaiDuUser=baiDuUser.lock();
        if (false==varBaiDuUser) { return; }

        /*获得networkaccessmanager*/
        auto varNAM=varBaiDuUser->getNetworkAccessManager();

        /*获得reply*/
        auto varReply=varNAM->get(varRequest);

        /*cookie 已经写入 cookiejar*/
        varReply->connect(varReply,&QNetworkReply::finished,
            [varLockThis=this->shared_from_this(),varReply,this]() {

                {
                    /*这些数据无用*/
                    varReply->close();
                    varReply->deleteLater();

                    auto varBaiDuUser=baiDuUser.lock();
                    if (false==varBaiDuUser) { return; }

                    if (varReply->error()!=QNetworkReply::NoError) {
                        loginStepNext=s_error;
                        errorString=varReply->errorString();
                    }
                    else {
                        loginStepNext=s_get_baidu_token;
                    }
                }

                next_step();

        });

    }

    ~Login() {
        if (false==logInFinishedCalled) {
            logInFinishedCalled=true;
            login_error();
        }
    }
private:
    CPLUSPLUS_CLASS_META
};

char Login::_psd_getBaiDuCookie[sizeof(StaticData_getBaiDuCookie)];
char Login::_psd_getBaiduToken[sizeof(StaticData_getBaiduToken)];

}/*namespace*/
}/*namespace __login*/

void BaiDuUser::login() {
    auto varLogin=memory::make_shared<__login::Login>();
    {/*init login data*/
        varLogin->baiDuUser=this->shared_from_this();
        zone_this_data(this);
        varThisData->_m_GID=gid();
    }
    varLogin->next_step();
}

NetworkAccessManager * BaiDuUser::getNetworkAccessManager() const {
    zone_const_this_data(this);
    return const_cast<NetworkAccessManager *>(
        &(varThisData->_m_NetworkAccessManager));
}

QString BaiDuUser::getLocalCacheFilePath()const {
    zone_const_this_data(this);
    return varThisData->_m_BaiDuUserCache.fileName();
}

bool BaiDuUser::isLogin() const {
    zone_const_this_data(this);
    return varThisData->_m_IsLogin;
}

QByteArray BaiDuUser::currentTime() {
    return QByteArray::number(QDateTime::currentMSecsSinceEpoch());
}

static char _p_userAgent_[sizeof(QByteArray)];
QByteArray BaiDuUser::userAgent() {
    static memory::StaticPoionter<QByteArray> varAns{ _p_userAgent_,
            "Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko"_qb
    };
    return *varAns;
}

QByteArray BaiDuUser::gid() {

    QByteArray ans{ 35,Qt::Uninitialized };

    constexpr const static char toHex0[]={
        '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    };

    constexpr const static char toHex1[]={
        '8','9','A','B','C','D','E','F','8','9','A','B','C','D','E','F',
    };

    class Array {
        char data[35];
    public:
        Array():data{
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15], '-',toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            '-','4',toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15], '-',
            toHex1[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15],'-',toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15]
        } {
        }
    };

    ::new(ans.data()) Array;

    return std::move(ans);
}

}/*namespace baidu*/

#undef zone_this_data

