#include "exception.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <mutex>
#include <shared_mutex>
#include "../lua/lua.hpp"
#include "../memory/MemoryLibrary.hpp"
#include "debug_exception.hpp"

#ifndef __DEBUG_TRY_CATCH

#else
namespace exception {

std::ostream & debug_exception_out() {
    /* do not need delete */
    static auto * ans=new std::ofstream("debug_exception.txt");
    return *ans;
}

std::recursive_mutex & debug_exception_out_mutex() {
    /* no not need delete */
    static auto * ans=new std::recursive_mutex;
    return *ans;
}

}/**/
#endif

/****************************************************************/
namespace {
namespace __private {

template<typename _Stream,typename _Data,std::size_t _N=0,typename _U=void>
inline void _write(_Stream && arg,const _Data&argD) {
    arg<<argD;
}

template<typename _Stream,typename _Data,std::size_t _N>
inline void _write(_Stream && arg,_Data(&argD)[_N]) {
    arg.write(argD,_N-1);
}

class TestInt {};

inline std::ostream& log_stream() {
    return std::cout;
}

class stringstream final :public std::basic_stringstream<
    char,std::char_traits<char>,
    memory::Allocator<char>
> {
    static inline std::recursive_mutex & getMutex();
    std::unique_lock<std::recursive_mutex> _m_Lock;
public:
    stringstream():_m_Lock(getMutex()) {}
    ~stringstream() {}
};

static char static_stringstream_getMutex[sizeof(std::recursive_mutex)];
inline std::recursive_mutex & stringstream::getMutex() {
    static memory::StaticPoionter<std::recursive_mutex>
        ans(static_stringstream_getMutex);
    return *ans;
}

class Handle :public exception::ExceptionHandle {
    int memLine;
    const char * memFunctionName;
    const char * memFileName;
    int memExceptionDepth=0;

    void bad_exception_handle() {
        try {
            stringstream out;
            _write(out,"get a really bad exception @\n");
            _write(out,"from : ");
            _write(out,"\nline : ");
            _write(out,memLine);
            _write(out,"\nfileName : ");
            _write(out,memFileName);
            _write(out,"\nfunctionName : ");
            _write(out,memFunctionName);
            _write(out,"\n(");
            _write(out,__LINE__);
            _write(out," , ");
            _write(out,__FILE__);
            _write(out," , ");
            _write(out,__func__);
            _write(out,")\n");
            log_stream()<<out.rdbuf();
        }
        catch (...) {}
        std::exit(-1);
    }

    /*add your own exception functions here*/
    void int_exception_handle(const TestInt &e) {

        try {
            stringstream out;
            _write(out,"get a TestInt exception @\n");
            _write(out,"from : ");
            _write(out,"\nline : ");
            _write(out,memLine);
            _write(out,"\nfileName : ");
            _write(out,memFileName);
            _write(out,"\nfunctionName : ");
            _write(out,memFunctionName);
            _write(out,"\n(");
            _write(out,__LINE__);
            _write(out," , ");
            _write(out,__FILE__);
            _write(out," , ");
            _write(out,__func__);
            _write(out,")\n");
            log_stream()<<out.rdbuf();
        }
        catch (...) {
            bad_exception_handle();
        }

        try {
            std::rethrow_if_nested(e);
        }
        catch (...) {
            exception_handle();
        }

    }

    void std_exception_handle(const std::exception &e) {

        try {
            stringstream out;
            _write(out,"get a std::exception exception @\n");
            _write(out,"from : ");
            _write(out,"\nline : ");
            _write(out,memLine);
            _write(out,"\nfileName : ");
            _write(out,memFileName);
            _write(out,"\nfunctionName : ");
            _write(out,memFunctionName);
            _write(out,"\n(");
            _write(out,__LINE__);
            _write(out," , ");
            _write(out,__FILE__);
            _write(out," , ");
            _write(out,__func__);
            _write(out,")");
            _write(out,e.what());
            _write(out,"\n");
            log_stream()<<out.rdbuf();
        }
        catch (...) {
            bad_exception_handle();
        }

        try {
            std::rethrow_if_nested(e);
        }
        catch (...) {
            exception_handle();
        }

    }

    void std_logic_error_exception_handle(const std::logic_error &e) {

        try {
            {
                stringstream out;
                _write(out,"get a std::logic_error exception @\n");
                _write(out,"from : ");
                _write(out,"\nline : ");
                _write(out,memLine);
                _write(out,"\nfileName : ");
                _write(out,memFileName);
                _write(out,"\nfunctionName : ");
                _write(out,memFunctionName);
                _write(out,"\n(");
                _write(out,__LINE__);
                _write(out," , ");
                _write(out,__FILE__);
                _write(out," , ");
                _write(out,__func__);
                _write(out,")");
                _write(out,e.what());
                _write(out,"\n");
                log_stream()<<out.rdbuf();
            }
            std::exit(-1);
        }
        catch (...) {
            bad_exception_handle();
        }

        try {
            std::rethrow_if_nested(e);
        }
        catch (...) {
            exception_handle();
        }

    }

    void std_bad_cast_exception_handle(const std::bad_cast &e) {

        try {
            {
                stringstream out;
                _write(out,"get a std::bad_cast exception @\n");
                _write(out,"from : ");
                _write(out,"\nline : ");
                _write(out,memLine);
                _write(out,"\nfileName : ");
                _write(out,memFileName);
                _write(out,"\nfunctionName : ");
                _write(out,memFunctionName);
                _write(out,"\n(");
                _write(out,__LINE__);
                _write(out," , ");
                _write(out,__FILE__);
                _write(out," , ");
                _write(out,__func__);
                _write(out,")");
                _write(out,e.what());
                _write(out,"\n");
                log_stream()<<out.rdbuf();
            }
        }
        catch (...) {
            bad_exception_handle();
        }

        try {
            std::rethrow_if_nested(e);
        }
        catch (...) {
            exception_handle();
        }

    }

public:

    Handle(
        int argLine=0,
        const char * argFunctionName=nullptr,
        const char * argFileName=nullptr):memLine(argLine),
        memFunctionName(argFunctionName),
        memFileName(argFileName) {
    }

    void exception_handle() noexcept(true) override {

        ++memExceptionDepth;
        try {
            std::rethrow_exception(std::current_exception());
        }/*add your own exception functions here*/
        catch (const TestInt &e) {
            int_exception_handle(e);
        }
        catch (const std::logic_error & e) {
            std_logic_error_exception_handle(e);
        }
        catch (const std::bad_cast & e) {
            std_bad_cast_exception_handle(e);
        }
        catch (const std::exception & e) {
            std_exception_handle(e);
        }
        catch (...) {
            /*unknow exception handle*/
            {
                stringstream out;
                _write(out,"get a unknow exception @\n");
                _write(out,"from : ");
                _write(out,"\nline : ");
                _write(out,memLine);
                _write(out,"\nfileName : ");
                _write(out,memFileName);
                _write(out,"\nfunctionName : ");
                _write(out,memFunctionName);
                _write(out,"\n(");
                _write(out,__LINE__);
                _write(out," , ");
                _write(out,__FILE__);
                _write(out," , ");
                _write(out,__func__);
                _write(out,")");
                _write(out,"\n");
                log_stream()<<out.rdbuf();
            }
            /*quit the application*/
            std::exit(-7);
        }

    }
private:
    MEMORY_CLASS_NEW_DELETE
};

}/*__private*/
}/*namespace*/
 /****************************************************************/

namespace exception {

void exception_handle(
    int line,
    const char * functionName,
    const char * fileName) noexcept(true) {

    try {
        std::rethrow_exception(std::current_exception());
    }/*do not catched exception*/
    catch (const lua_exception_type &e) {
        {
            __private::stringstream out;
            out<<"you should rethrow lua exception yourself:"
                <<functionName<<":"<<fileName
                <<":"<<line;
            __private::log_stream()<<out.rdbuf();
        }
        std::exit(-1); (void)e;
    }
    catch (const std::bad_alloc &e) {
        {
            __private::stringstream out;
            out<<"bad_alloc:"
                <<functionName<<":"<<fileName
                <<":"<<line;
            __private::log_stream()<<out.rdbuf();
        }
        /*std::quick_exit(-1);*/
        std::exit(-1); (void)e;
    }
    catch (...) {
        auto handle=exception::getCreateExceptionHandleFunction()(line,functionName,fileName);
        handle->exception_handle();
    }

}/**/

namespace _0_private {
namespace {

static char static_mutex[sizeof(std::shared_timed_mutex)];
std::shared_timed_mutex & mutex() {
    static memory::StaticPoionter<std::shared_timed_mutex>
        ans(static_mutex);
    return *ans;
}

CreateExceptionHandleFunction & data() {
    static CreateExceptionHandleFunction _m_Data=[](
        int/*line*/a,
        const char * /*func*/b,
        const char * /*file*/c)->std::unique_ptr<ExceptionHandle> {
        return std::make_unique<__private::Handle>(a,b,c);
    };
    return _m_Data;
}

}/*namespace*/
}/*_0_private*/

CreateExceptionHandleFunction getCreateExceptionHandleFunction() {
    std::shared_lock<std::shared_timed_mutex> varLock{ _0_private::mutex() };
    return _0_private::data();
}

CreateExceptionHandleFunction setCreateExceptionHandleFunction(CreateExceptionHandleFunction arg) {
    if (arg==nullptr) { return getCreateExceptionHandleFunction(); }
    std::unique_lock<std::shared_timed_mutex > varLock{ _0_private::mutex() };
    auto varOld=_0_private::data();
    _0_private::data()=arg;
    return varOld;
}


}/**/

/**
**/
