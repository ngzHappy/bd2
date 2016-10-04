#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QtCore>
#include <BaiDuUserCache.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    baiduUser=baidu::BaiDuUser::instance();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_loginButton_clicked(){

    baiduUser->openUserName( ui->userName->text() );
    baiduUser->setPassWord( ui->passWord->text() );
    qDebug()<<
    baidu::BaiDuUserCache::filePathToUserName( baiduUser->getLocalCacheFilePath() );
    

}
