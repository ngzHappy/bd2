
#ifndef _e_LUA_EXCEPTION_HPP____
#define _e_LUA_EXCEPTION_HPP____

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
typedef _e_lua_exception_type lua_exception_type;

#endif

