#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(768,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateData(){
    QString varAns=u8R"__(#include <memory>
template<typename,typename> class Value;

typedef ???? Key$ValueName$;
typedef ???? Type$ValueName$;

template<typename _ThisClassType_>
class Value<_ThisClassType_,Key$ValueName$>{
protected:
    Type$ValueName$ _m_$ValueName$;
    auto & value(){return _m_$ValueName$;}
    const auto & value()const{return _m_$ValueName$;}
    using type = Type$ValueName$;
    Value(decltype(nullptr)=nullptr){/*default construct*/}
    template<typename _0Type_,typename ... _Type_>
    Value(_0Type_ &&arg0,_Type_&&...args):
        _m_$ValueName$(std::forward<_0Type_>(arg0),std::forward<_Type_>(args)...){}
};

)__";
    
    varAns.replace("$ValueName$",_m_ValueName);
    varAns.replace("$ValueIndex$",QString::number(_m_ValueIndex));

    ui->textEdit->setFontPointSize(18);
    ui->textEdit->setText(varAns);
}

void MainWindow::on_ValueName_editingFinished() {
    QString varName=ui->ValueName->text();
    if (varName.isEmpty()) { return; }
    {
        auto varLeft=varName.left(1).toUpper();
        varName=varLeft+varName.mid(1);
    }
    if(varName==_m_ValueName){return;}
    _m_ValueName=varName;
    updateData();
}

void MainWindow::on_ValueIndex_valueChanged(int arg)
{
    if(arg==_m_ValueIndex){return;}
    _m_ValueIndex=arg;
    updateData();
}
