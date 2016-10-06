#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtNetwork>
#include <BaiDuUserCache.hpp>

MainWindow::MainWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    baiduUser=baidu::BaiDuUser::instance();
    connect(baiduUser.get(),&baidu::BaiDuUser::loginFinished,
        [this](bool arg,QString) {

        if (arg==true) {
            ui->vertifyImage->setText(QString::fromUtf8(u8"登陆成功"));
            return;
        }

        static QNetworkAccessManager manager;

        do {
            auto url_=baiduUser->getVertifyCodeUrl();
            if (url_.isEmpty()) { break; }
            auto reply=manager.get(QNetworkRequest(QUrl(url_)));
            QEventLoop loop;
            connect(reply,&QNetworkReply::finished,
                [&]() {
                loop.quit();
                reply->deleteLater();
                ui->vertifyImage->setPixmap(
                    QPixmap::fromImage(
                    QImage::fromData(reply->readAll())));
            });
            loop.exec();
        } while (false);

    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_loginButton_clicked() {

    baiduUser->openUserName(ui->userName->text());
    baiduUser->setPassWord(ui->passWord->text());
    qDebug()<<
        baidu::BaiDuUserCache::filePathToUserName(baiduUser->getLocalCacheFilePath());
    
    baiduUser->login(ui->vertifyCode->text());

}
