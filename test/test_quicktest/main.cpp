#include "MainWindow.hpp"
#include <QtWidgets/QApplication>
#include <memory/MemoryLibrary.hpp>
#include "TestStaticPointer.hpp"

class Application
        :public QApplication,memory::Application{
public:
    using QApplication::QApplication;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TestStaticPointer static_pointer_test;

    MainWindow window;
    window.show();

    return app.exec();
}
