#include "MainWindow.hpp"
#include "ui_MainWindow.h"

/*

#include <type_traits>

template<int,typename,typename...>class Index;
template<typename T>using simple=std::remove_cv_t<std::remove_reference_t<T>>;

template<int I,typename A>class Index<I,A> {
public:
    constexpr static int value=-1;
};

template<int I,typename A,typename B>
class Index<I,A,B> {
public:
    constexpr static int value=std::is_same<simple<A>,simple<B>>::value?I:-1;
};

template<int I,typename A,typename B,typename C,typename ...D>
class Index<I,A,B,C,D...> {
public:
    constexpr static int value=std::is_same<simple<A>,simple<B>>::value?I:
        Index<1+I,A,C,D...>::value;
};

*/

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateData() {
    const auto varString=this->ui->stringValue->text();
    const auto varByteArray=varString.toUtf8();
    auto varTextEdit=this->ui->textEdit;

    varTextEdit->setFontPointSize(18);

    if (varByteArray.isEmpty()) {
        varTextEdit->setText(QString::fromUtf8(u8R"(字符串为空)"));
    }
    else {
        QString varAns;
        varAns=u8R"(#ifndef CNAME_)"+varString+"\n"
            "#define CNAME_"+varString+" /*"+varString+"*/";
        {
            auto pos=varByteArray.cbegin();
            auto posend=varByteArray.cend();
            {
                auto i=*pos;
                if ((i<char(1))||(i>=char(127))) {
                    varTextEdit->setText(QString::fromUtf8(u8R"(仅支持小于127的字符)"));
                    return;
                }
                varAns+="(char)("+QString::number(int(i))+")/*"+i+"*/";
            }
            for (++pos; pos!=posend; ++pos) {
                auto i=*pos;
                if ((i<char(1))||(i>=char(127))) {
                    varTextEdit->setText(QString::fromUtf8(u8R"(仅支持小于127的字符)"));
                    return;
                }
                varAns+=",(char)("+QString::number(int(i))+")/*"+i+"*/";
            }
        }
        varAns+="\n#endif\n";
        varTextEdit->setText(varAns);
    }

}

void MainWindow::on_stringValue_editingFinished() {
    updateData();
}
