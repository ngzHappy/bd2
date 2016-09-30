#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QtCore/qstring.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800,800);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateData(){
    auto varClassName = ui->className->text();

    QString varData=u8R"__($C$(const $C$&)=delete;
$C$($C$&&)=delete;
$C$&operator=(const $C$&)=delete;
$C$&operator=($C$&&)=delete;

$C$(const $C$&)=default;
$C$($C$&&)=default;
$C$&operator=(const $C$&)=default;
$C$&operator=($C$&&)=default;
)__";
    
    varData.replace("$C$",varClassName);

    ui->textEdit->setFontPointSize(18);
    ui->textEdit->setText(varData);
}

void MainWindow::on_className_editingFinished(){
    updateData();
}
