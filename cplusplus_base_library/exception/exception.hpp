#ifndef _m_EXCEPTION__HPP_BASE__
#define _m_EXCEPTION__HPP_BASE__() 1

#include <memory>
#include <exception>
#include <stdexcept>
#include "../cplusplus_base_library.hpp"
#include "../lua/__lua_exception.hpp"

#ifndef HANDLE_EXCEPTION_EXPORT
#define HANDLE_EXCEPTION_EXPORT CPLUSPLUS_BASE_LIBRARYSHARED_EXPORT
#endif

namespace exception {

class ExceptionHandle {
    ExceptionHandle&operator=(const ExceptionHandle&)=delete;
    ExceptionHandle&operator=(ExceptionHandle&&)=delete;
    ExceptionHandle(const ExceptionHandle&)=delete;
    ExceptionHandle(ExceptionHandle&&)=delete;
public:
    virtual ~ExceptionHandle()=default;
    virtual void exception_handle() noexcept(true)=0;
    ExceptionHandle()=default;
};

typedef std::unique_ptr<ExceptionHandle>(*CreateExceptionHandleFunction)(int/*line*/,const char * /*func*/,const char * /*file*/);
HANDLE_EXCEPTION_EXPORT CreateExceptionHandleFunction getCreateExceptionHandleFunction();
HANDLE_EXCEPTION_EXPORT CreateExceptionHandleFunction setCreateExceptionHandleFunction(CreateExceptionHandleFunction);

/*
throw : lua_exception_type
*/
HANDLE_EXCEPTION_EXPORT void exception_handle(
    int line,
    const char * functionName,
    const char * fileName) noexcept(true);

}/*namspace:exception*/

#ifndef not_cplusplus_exception
#define not_cplusplus_exception() catch( const lua_exception_type & _lua_e_2376_ ) { throw _lua_e_2376_ ; }
#endif

#ifndef exception_catched
#define exception_catched() exception::exception_handle(__LINE__,__func__,__FILE__)
#endif

#ifndef cplusplus_catch
#define cplusplus_catch() /**/not_cplusplus_exception()catch (...) { /**/ \
exception_catched(); /**/ \
}/**/

#endif/*cplusplus_catch*/

#endif



