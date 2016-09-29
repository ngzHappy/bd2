#ifndef _m_MEMORY_STATIC_HPP_CPP_
#define _m_MEMORY_STATIC_HPP_CPP_() 1

#include "Memory.hpp"
#include "Allocator.hpp"
#include "MemoryApplication.hpp"
#include <type_traits>

namespace memory {

/*
the function just call once
the function must be called before any static/thread_local data not pod
*/
inline void constructStatic() {
    if (__memory__construct_static::__is_construct_static()) { return; }
    __memory__construct_static::__run_once([]() {
        /*set your code here***********************/
        /******************************************/
        __memory__construct_static::__set_construct_static();
    });
    return;
}

namespace _ns_static_pointer_private_memory_ {
template<typename _T_>
class StaticPointerPOD {
private:
    _T_ * const _m_Data;

    template<typename _U_,bool _I_>
    class __Construct {
    public:
        template<typename ... _A_>
        static void construct(void *arg,_A_&&...args) {
            ::new(arg) _T_(std::forward<_A_>(args)...);
        }
    };

    template<typename _U_>
    class __Construct<_U_,false> {
    public:
        template<typename ... _A_>
        static void construct(void *arg,_A_&&...args) {
            ::new(arg) _T_{ std::forward<_A_>(args)... };
        }
    };

public:
    auto pointer() { return _m_Data; }
    const auto pointer() const { return _m_Data; }
    auto operator->() { return pointer(); }
    const auto operator->() const { return pointer(); }
    auto & operator*() { return *pointer(); }
    const auto & operator*() const { return *pointer(); }
public:
    ~StaticPointerPOD()=default;
    StaticPointerPOD()=delete;
    StaticPointerPOD(const StaticPointerPOD&)=delete;
    StaticPointerPOD(StaticPointerPOD&&)=delete;
    StaticPointerPOD&operator=(const StaticPointerPOD&)=delete;
    StaticPointerPOD&operator=(StaticPointerPOD&&)=delete;
public:
    template<typename ..._Args_>
    StaticPointerPOD(const void * argData,_Args_&&...args)
        :_m_Data(reinterpret_cast<_T_ *>(const_cast<void*>(argData))) {
        __Construct<_T_,std::is_constructible<
            _T_,_Args_...>::value>::construct(
                const_cast<void*>(argData),
                std::forward<_Args_>(args)...);
    }
    StaticPointerPOD(const void * argData)
        :_m_Data(reinterpret_cast<_T_ *>(const_cast<void*>(argData))) {
        ::new(const_cast<void*>(argData)) _T_{};
    }
};

class NoPODConstruct {
public:
    NoPODConstruct() { memory::constructStatic(); }
    ~NoPODConstruct()=default;
};

}

template<
    typename _T_,
    bool _need_close_=false,
    bool _is_plugin_=IS_PLUGIN_FIRE,
    bool _is_pod_=std::is_pod<_T_>::value/*false*/
>
class StaticPoionter :
    private _ns_static_pointer_private_memory_::NoPODConstruct,
    public _ns_static_pointer_private_memory_::StaticPointerPOD<_T_> {
    using _N_=_ns_static_pointer_private_memory_::NoPODConstruct;
    using _S_=_ns_static_pointer_private_memory_::StaticPointerPOD<_T_>;
    template<typename ...>using _void_t=void;
    template<typename _U_,typename _C_=void>
    class __Close:public std::false_type {};
    template<typename _U_>
    class __Close<_U_,_void_t<decltype(std::declval<_T_*>()->close())>>
        :public std::true_type{};
public:
    template<typename ..._Args_>
    StaticPoionter(const void *argData,_Args_&&...args)
        :_N_(),_S_(argData,std::forward<_Args_>(args)...) {}

    ~StaticPoionter() {
        /*c++17将if改为if constexpr*/
        constexpr bool _has_close=__Close<void>::value;

        /*关闭非内存资源*/
        if(_need_close_&&_has_close) {
            _S_::pointer()->close();
        }

        /*执行析构释放内存资源*/
        if (std::is_trivially_destructible<_T_>::value) {
            return/*平凡的析构函数*/;
        }else if(_is_plugin_) {
            if (memory::Application::isMainQuit()) {
                return/*主函数已经退出不必释放内存*/;
            }
            _S_::pointer()->~_T_()/*用析构释放内存*/;
            return/*插件需要析构*/;
        }else {
            return/*非插件不必析构释放内存*/;
        }

    }
};

template<
    typename _T_,
    bool _need_close_
    bool _is_plugin_
>class StaticPoionter<_T_,_need_close_,_is_plugin_,true> :
    public _ns_static_pointer_private_memory_::StaticPointerPOD<_T_> {
    using _S_=_ns_static_pointer_private_memory_::StaticPointerPOD<_T_>;
public:
    using _S_::_S_;
};

}/*~memory*/

#endif



