#ifndef __57235__FUNCTION__HPP__
#define __57235__FUNCTION__HPP__

#include <type_traits>
#include "module.hpp"
#include "../exception/exception.hpp"

namespace function {

template<typename ___T___>
class BasicFunctionState {
    BasicFunctionState&operator=(const BasicFunctionState&)=delete;
    BasicFunctionState&operator=(BasicFunctionState&&)=delete;
    BasicFunctionState(const BasicFunctionState&)=delete;
    BasicFunctionState(BasicFunctionState&&)=delete;
public:
    typedef std::remove_reference_t<___T___> ans_type;
    constexpr ans_type returnNormal() const  noexcept(true) { return{}; }
    constexpr const ans_type & returnNormal(const ans_type &arg) const  noexcept(true) { return arg; }
    constexpr ans_type && returnNormal(ans_type &&arg) const  noexcept(true) { return static_cast<ans_type&&>(arg); }
    constexpr const ans_type && returnNormal(const ans_type &&arg) const  noexcept(true) { return static_cast<const ans_type&&>(arg); }
    constexpr ans_type & returnNormal(ans_type&arg) const  noexcept(true) { return static_cast<ans_type&>(arg); }
    ~BasicFunctionState()=default;
    constexpr BasicFunctionState()=default;
};

template<>
class BasicFunctionState<void> {
    BasicFunctionState&operator=(const BasicFunctionState&)=delete;
    BasicFunctionState&operator=(BasicFunctionState&&)=delete;
    BasicFunctionState(const BasicFunctionState&)=delete;
    BasicFunctionState(BasicFunctionState&&)=delete;
public:
    ~BasicFunctionState()=default;
    constexpr BasicFunctionState()=default;
    typedef void ans_type;
    template<typename...___U___>
    constexpr void returnNormal(___U___&&...) const  noexcept(true) {}
};

}/*namespace function*/

#define FUNCTION_WITHOUT_EXCEPTION(_2_module__,...) { static_assert(_2_module__,"all module must without exceptions");/**/__VA_ARGS__/**/ }
#define FUNCTION_WITH_EXCEPTION(_1_module__,...) try/**/FUNCTION_WITHOUT_EXCEPTION(((_1_module__)||true),__VA_ARGS__)/**/cplusplus_catch()

#endif

/**
class _FunctionState final {
        _FunctionState(const _FunctionState&)=delete;
        _FunctionState(_FunctionState&&)=delete;
        _FunctionState&operator=(const _FunctionState&)=delete;
        _FunctionState&operator=(_FunctionState&&)=delete;
    public:
        typedef int ans_type;
    public://state 0
        constexpr ans_type returnNormal() const  noexcept(true) { return 0; }
        constexpr decltype(auto) returnNormal(const ans_type &arg) const  noexcept(true) { return arg; }
        constexpr decltype(auto) returnNormal(ans_type &&arg) const  noexcept(true) { return static_cast<ans_type&&>(arg); }
        constexpr decltype(auto) returnNormal(const ans_type &&arg) const  noexcept(true) { return static_cast<const ans_type&&>(arg); }
        constexpr decltype(auto) returnNormal(ans_type&arg) const  noexcept(true) { return static_cast<ans_type&>(arg); }
        ~_FunctionState()=default;
        constexpr _FunctionState()=default;
    private://state 1
        //void on_return() noexcept(true) {}
    public:
        //ans_type returnNormal()  noexcept(true) { on_return(); return 0; }
        //decltype(auto) returnNormal(const ans_type &arg)  noexcept(true) { on_return(); return arg; }
        //decltype(auto) returnNormal(ans_type &&arg)  noexcept(true) { on_return(); return static_cast<ans_type&&>(arg); }
        //decltype(auto) returnNormal(const ans_type &&arg)  noexcept(true) { on_return(); return static_cast<const ans_type&&>(arg); }
        //decltype(auto) returnNormal(ans_type&arg)  noexcept(true) { on_return(); return static_cast<ans_type&>(arg); }
        //_FunctionState() {}
        //~_FunctionState() {}
    };
**/

