#include "MainWindow.hpp"
#include <QApplication>

#include "BaiDuUserCache.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    baidu::BaiDuUserCache xx(THIS_PROJECT_SOURCE_DIR "/login_info/login_info.lua");
    xx.read();
    xx.write();
    xx.getUserName();
    xx.setUserName("xxxxx");
    auto yy= xx.getUserName();

    MainWindow window;
    window.show();

    return app.exec();
}
