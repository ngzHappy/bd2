#ifndef __RunInMainThread_HPP_
#define __RunInMainThread_HPP_

#include <functional>
#include "BaiduCoreLibrary.hpp"

namespace baidu {

namespace __private {

typedef void(*PlainFunctionType)();

BAIDU_CORE_LIBRARYSHARED_EXPORT void _plain_runInMainThread(const PlainFunctionType);
BAIDU_CORE_LIBRARYSHARED_EXPORT void _function_runInMainThread(std::function<void(void)>);

template<typename _T_>
class IsPlainFunction :public std::conditional_t<
    std::is_convertible<_T_/*from*/,const PlainFunctionType/*to*/>::value,
    std::true_type,std::false_type> {
};

class RunSelectPlain {
public:
    static void run(const PlainFunctionType arg) { _plain_runInMainThread(arg); }
};

class RunSelectMulti {
public:
    static void run(const std::function<void(void)>&arg) { _function_runInMainThread(arg); }
    static void run(std::function<void(void)>&&arg) { _function_runInMainThread(std::move(arg)); }
};

}/*__private*/

template<typename _T_>
void runInMainThread(_T_&&arg) {
    using _run_type=std::conditional_t<
        __private::IsPlainFunction<_T_>::value,
        __private::RunSelectPlain,
        __private::RunSelectMulti
    >;
    return _run_type::run(std::forward<_T_>(arg));
}

}/*baidu*/

#endif
