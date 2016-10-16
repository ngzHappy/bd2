#ifndef _m_EXCEPTION__HPP_BASE__
#define _m_EXCEPTION__HPP_BASE__() 1

#include <string>
#include <memory>
#include <exception>
#include <stdexcept>
using namespace std::string_literals;
#include "../cplusplus_base_library.hpp"
#include "../lua/__lua_exception.hpp"

#ifndef HANDLE_EXCEPTION_EXPORT
#define HANDLE_EXCEPTION_EXPORT CPLUSPLUS_BASE_LIBRARYSHARED_EXPORT
#endif

namespace exception {

class UnexpectedException :public std::logic_error {
public:
    UnexpectedException(
        const char *argFileName,int argLFileName,
        const char *argFunctionName,int argLFunctionName,
        int argLine
    ):std::logic_error(u8R"(UnexpectedException @ )"s
        +u8R"(filename : )"s
        +std::string(argFileName,argLFileName)
        +u8R"(functionname : )"s
        +std::string(argFunctionName,argLFunctionName)
        +u8R"(line : )"s
        +std::to_string(argLine)
        +"\n"s
    ) {/*the application should be exit here*/
    }

    template<int _N_0,int _N_1>
    UnexpectedException(
        const char(&_0_)[_N_0],
        const char(&_1_)[_N_1],
        int _2_
    ):UnexpectedException(_0_,(_N_0-1),_1_,(_N_1-1),_2_) {
    }

};

#ifndef unexpected_exception
#define unexpected_exception() throw( UnexpectedException(__FILE__,__func__,__LINE__) )
#endif

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
}static_assert(true,"")/**/

#endif/*cplusplus_catch*/

#endif



