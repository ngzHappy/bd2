﻿#ifndef _m_EXCEPTION__HPP_BASE__
#define _m_EXCEPTION__HPP_BASE__() 1

#include <memory>
#include <exception>
#include <stdexcept>
#include "../cplusplus_base_library.hpp"

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

#ifndef exception_catched
#define exception_catched() exception::exception_handle(__LINE__,__func__,__FILE__)
#endif

#endif


