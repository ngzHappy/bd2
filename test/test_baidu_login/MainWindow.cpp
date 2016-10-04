#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <BaiDuUserCache.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
