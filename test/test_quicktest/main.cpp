﻿#include "MainWindow.hpp"
#include <QtCore>
#include <QtWidgets/QApplication>
#include <memory/MemoryLibrary.hpp>
#include <exception/exception.hpp>
#include <function/function.hpp>
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

#include <optional.hpp>
#include <string>

optional<int> xxx() {
    return 334;
}

int main(int argc,char *argv[]) {

    typedef function::BasicFunctionState<int> _FunctionState;
    constexpr _FunctionState varThisFunctionState;

    try {

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
    }cplusplus_catch();

    return varThisFunctionState.returnNormal();

}





