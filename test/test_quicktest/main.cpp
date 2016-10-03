#include "MainWindow.hpp"
#include <QtWidgets/QApplication>
#include <memory/MemoryLibrary.hpp>
#include "TestStaticPointer.hpp"
#include "TestCompiler.hpp"
#include "TestNetWork.hpp"

class Application
        :public QApplication,memory::Application{
public:
    using QApplication::QApplication;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TestStaticPointer static_pointer_test;
    TestCompiler testCompiler;
    TestNetWork testNetWork;

    testCompiler.get<0>();

    MainWindow window;
    window.show();

    return app.exec();
}
