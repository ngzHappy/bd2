#ifndef __ARGUMENT_hpp_file_0x3051
#define __ARGUMENT_hpp_file_0x3051

#include <tuple>
#include <utility>
#include <type_traits>

template<typename,typename> class Value;
template<typename,int> class Type;

namespace _pcios/*private constexpr int or string*/ {
template<int,int/*-1:string 1:integer*/,char...>class _cT_;
}

namespace constexpr_string {
template<char...__C>
using string=_pcios::_cT_<-1,-1,__C...>;
}

namespace constexpr_integer{
template<int _N_>
using integer=_pcios::_cT_<_N_,1>;
}

namespace argument {

namespace _a0_/*version 0.0*/ {
namespace _p0_ {

template<int,typename,typename...>class _PositionIn;

template<typename _T_>
using _simple=std::remove_cv_t<std::remove_reference_t<_T_>>;

template<typename A,typename B>
using _is_same=std::is_same<_simple<A>,_simple<B>>;

template<int I,typename A>
class _PositionIn<I,A> {
public:
    constexpr static int value=-1;
};

template<int I,typename A,typename B>
class _PositionIn<I,A,B> {
public:
    constexpr static int value=_is_same<A,B>::value?I:-1;
};

template<int I,typename A,typename B,typename C,typename ... D>
class _PositionIn<I,A,B,C,D...> {
public:
    constexpr static int value=_is_same<A,B>::value?I:
        _PositionIn<1+I,A,C,D...>::value;
};

template<int I,bool=(I<0)>class _Get;

template<int I>
class _Get<I,true> {
public:
    template<typename _U_>
    constexpr static decltype(nullptr) value(const _U_&) { return nullptr; }
};

template<int I>
class _Get<I,false> {
public:
    template<typename _TKV_>
    static decltype(auto) value(const _TKV_&arg) {
        using _this_element_=_simple<std::tuple_element_t<I,_TKV_>>;
        typedef typename _this_element_::value_type _value_type_;
        return std::forward<_value_type_>(std::get<I>(arg).value);
    }
};

}/*_p0_*/

template<typename _K_,typename _V_>
class KeyValue {
    static_assert(std::is_reference<_V_>::value,"value must be reference");
public:
    typedef _V_ value_type;
    typedef _K_ key_type;
    _V_ value;
};

template<typename _K_,typename _V_>
inline auto akv(_V_&&arg) {
    return KeyValue<_K_,_V_&&>{ std::forward<_V_>(arg) };
}/*_p0_*/

template<typename ... _A_>
auto atie(_A_&&...args) {
    typedef std::tuple<const _A_&...> _Tuple_;
    return _Tuple_(static_cast<const _A_&>(args)...);
}

template<
    typename _this_key_,
    typename ..._K_,
    typename ..._V_
>
inline decltype(auto) aget(
    const std::tuple<const KeyValue<_K_,_V_>&...>&arg) {
    constexpr int _index_=
        _p0_::_PositionIn<0,_this_key_,_K_...>::value;
    return _p0_::_Get<_index_>::value(arg);
}/*aget*/

}/*_a0_*/


template<typename _A_,typename _B_>
using key_same=_a0_::_p0_::_is_same<_A_,_B_>/*type*/;
template<typename _A_>
using is_key_nullptr=key_same<_A_,decltype(nullptr)>/*type*/;
using _a0_::KeyValue/*type*/;
using _a0_::atie/*function*/;
using _a0_::aget/*function*/;
using _a0_::akv/*function*/;
template<typename...>class cat_tuple;
template<typename ...A>
class cat_tuple<std::tuple<A...>> {
public:
    typedef std::tuple<A...> type;
};
template<typename ...A,typename ...B>
class cat_tuple<std::tuple<A...>,std::tuple<B...>> {
public:
    typedef std::tuple<A...,B...> type;
};

template<typename ...A,typename ...B,typename ...C,typename ...D>
class cat_tuple<std::tuple<A...>,std::tuple<B...>,std::tuple<C...>,D...> {
    typedef typename cat_tuple<std::tuple<A...>,std::tuple<B...>>::type __type1;
    typedef typename cat_tuple<std::tuple<C...>,D...>::type __type2;
public:
    typedef typename cat_tuple<__type1,__type2>::type type;
};

template<typename ...T>
using cat_tuple_t=typename cat_tuple<T...>::type;
/*
template<typename ..._K_,typename ..._V_>
(const std::tuple<const argument::KeyValue<_K_,_V_>&...>&arg)
*/

}/*argument*/

#endif/*argument.hpp*/



