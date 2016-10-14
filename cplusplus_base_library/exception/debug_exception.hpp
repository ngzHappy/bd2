#ifndef _m_DEBUG_EXCEPTION__HPP_BASE_0x79327_
#define _m_DEBUG_EXCEPTION__HPP_BASE_0x79327_() 1

#include <cassert>

#ifndef NDEBUG /* 用于追踪函数异常 */

#include <mutex>
#include <iostream>
#include "exception.hpp"

#ifndef DEBUG_TRY
#define DEBUG_TRY /**/try/**/
#endif

namespace exception {
HANDLE_EXCEPTION_EXPORT std::ostream & debug_exception_out();
HANDLE_EXCEPTION_EXPORT std::recursive_mutex & debug_exception_out_mutex();
}

#ifndef DEBUG_CATCH
#define DEBUG_CATCH(...) /* DEBUG_CATCH */catch(...){ const std::unique_lock<std::recursive_mutex> __lock__(exception::debug_exception_out_mutex()); \
    exception::debug_exception_out()<<"exception@ "<<__LINE__<<" ::.:: "<<__FILE__<<" ::.:: "<<__func__<<std::endl; \
    __VA_ARGS__ }/* DEBUG_CATCH */
#endif

#else /*NDEBUG*/

#ifndef DEBUG_TRY
#define DEBUG_TRY /*do nothing*/
#endif

#ifndef DEBUG_CATCH
#define DEBUG_CATCH(...) /*do nothing*/
#endif

#endif /*NDEBUG*/

#endif






