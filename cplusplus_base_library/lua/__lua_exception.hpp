
#ifndef _e_LUA_EXCEPTION_HPP____
#define _e_LUA_EXCEPTION_HPP____

#include "lua-5.3.3/src/luaconf.h"
#include <memory>

LUA_API int lua_exception_count();
//void lua_add_exception();
//void lua_remove_exception();
namespace lua {
inline int exception_count() noexcept(true) { return lua_exception_count(); }
}

class _e_lua_exception_type { 
public:
    _e_lua_exception_type(const _e_lua_exception_type&)=default;
    _e_lua_exception_type(_e_lua_exception_type&&)=default;
    _e_lua_exception_type&operator=(const _e_lua_exception_type&)=default;
    _e_lua_exception_type&operator=(_e_lua_exception_type&&)=default;
public:
    _e_lua_exception_type()=default;
    virtual ~_e_lua_exception_type()=default; 
};
typedef std::shared_ptr<_e_lua_exception_type> lua_exception_type;

#endif

