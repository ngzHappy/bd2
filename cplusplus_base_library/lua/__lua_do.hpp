
#include "__lua_exception.hpp"
#include <atomic>
#include "../memory/MakeShared.hpp"

static thread_local std::atomic<int> __lua_exception_count={0};

int lua_exception_count() { return __lua_exception_count.load(); }
inline void lua_add_exception() { ++__lua_exception_count; }
inline void lua_remove_exception() { --__lua_exception_count; }

namespace {

class __LUA_Exception :
    public _e_lua_exception_type {
    __LUA_Exception(const __LUA_Exception&);
    __LUA_Exception(__LUA_Exception&&);
public:
    __LUA_Exception() { lua_add_exception(); }
    ~__LUA_Exception() { lua_remove_exception(); }
};

}/*namespace*/

#if !defined(LUAI_THROW)				/* { */

/* C++ exceptions */
#define LUAI_THROW(L,c) lua_exception_type _1_exception_lock_=memory::make_shared<__LUA_Exception>(); throw( _1_exception_lock_ )
#define LUAI_TRY(L,c,a) \
	try { a } catch(...) { if ((c)->status == 0) (c)->status = -1; }
#define luai_jmpbuf		int  /* dummy variable */

#endif							/* } */



