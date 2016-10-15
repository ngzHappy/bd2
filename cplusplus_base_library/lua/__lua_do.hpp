
#include "__lua_exception.hpp"

namespace {

class __LUA_Exception :
    public lua_exception_type {
    lua_State*_m_L;
public:
    __LUA_Exception(lua_State*arg):_m_L(arg) {}
    ~__LUA_Exception() {}
};

}/*namespace*/

#if !defined(LUAI_THROW)				/* { */

/* C++ exceptions */
#define LUAI_THROW(L,c) const __LUA_Exception _1_exception_lock_(L); throw( _1_exception_lock_ )
#define LUAI_TRY(L,c,a) \
	try { a } catch(...) { if ((c)->status == 0) (c)->status = -1; }
#define luai_jmpbuf		int  /* dummy variable */

#endif							/* } */



