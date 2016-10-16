#include "MainWindow.hpp"
#include <QtCore>
#include <QtWidgets/QApplication>
#include <memory/MemoryLibrary.hpp>
#include <exception/exception.hpp>
#include "TestStaticPointer.hpp"
#include "TestCompiler.hpp"
#include "TestNetWork.hpp"
#include "TestGzip.hpp"
#include "TestGumbo.hpp"
#include "BoostICL.hpp"

class Application
    :public QApplication,memory::Application {
public:
    using QApplication::QApplication;
};

class FunctionState {
    int xxx=2;
public:
    void f_return() const {}
    template<typename __T__=int>
    decltype(auto) f_return(__T__&&_arg_) {
        xxx=675;
        return std::forward<__T__>(_arg_);
    }
};
inline int test() {

    FunctionState f;

    return f.f_return({});

    try {

    }
    catch (const int &) {
    }

    return 7;
}

#
#
#
#

int main(int argc,char *argv[]) {

    class _FunctionState final {
        _FunctionState(const _FunctionState&)=delete;
        _FunctionState(_FunctionState&&)=delete;
        _FunctionState&operator=(const _FunctionState&)=delete;
        _FunctionState&operator=(_FunctionState&&)=delete;
    public:
        typedef int ans_type;
    public:/*state 0*/
        constexpr ans_type returnNormal() const  noexcept(true) { return 0; }
        constexpr decltype(auto) returnNormal(const ans_type &arg) const  noexcept(true) { return arg; }
        constexpr decltype(auto) returnNormal(ans_type &&arg) const  noexcept(true) { return static_cast<ans_type&&>(arg); }
        constexpr decltype(auto) returnNormal(const ans_type &&arg) const  noexcept(true) { return static_cast<const ans_type&&>(arg); }
        constexpr decltype(auto) returnNormal(ans_type&arg) const  noexcept(true) { return static_cast<ans_type&>(arg); }
        ~_FunctionState()=default;
        constexpr _FunctionState()=default;
    }varThisFunctionState;

    FUNCTION_WITH_EXCEPTION({

       QApplication app(argc,argv);

       TestGumbo test_gumbo;
       TestGzip test_gzip;
       TestStaticPointer static_pointer_test;
       TestCompiler testCompiler;
       BoostICL icl;
       std::unique_ptr<TestNetWork> testNetWork=nullptr;

       QTimer::singleShot(0,[&testNetWork]() {
           testNetWork.reset(new TestNetWork);
       });

       testCompiler.get<0>();

       MainWindow window;
       window.show();

       return varThisFunctionState.returnNormal(app.exec());
    });

    return varThisFunctionState.returnNormal();
}





