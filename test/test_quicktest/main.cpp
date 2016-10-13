﻿#include "MainWindow.hpp"
#include <QtCore>
#include <QtWidgets/QApplication>
#include <memory/MemoryLibrary.hpp>
#include "TestStaticPointer.hpp"
#include "TestCompiler.hpp"
#include "TestNetWork.hpp"
#include "TestGzip.hpp"
#include "TestGumbo.hpp"
#include "BoostICL.hpp"

class Application
        :public QApplication,memory::Application{
public:
    using QApplication::QApplication;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

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

    return app.exec();
}
