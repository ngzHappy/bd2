#include "TestGumbo.hpp"
#include <gumbo/gumbo.hpp>
#include <QtCore/qtextstream.h>
#include <QtCore/qfile.h>
#include <QtCore/qdebug.h>

TestGumbo::TestGumbo(){

    QFile file(THIS_PROJECT_SOURCE_DIR "/data/test_gumbo.htm");
    QFile ofile( THIS_PROJECT_SOURCE_DIR "/data/ans_test_gumbo.txt" );

    if(file.open( QIODevice::ReadOnly )&&ofile.open(QIODevice::WriteOnly)){
        const auto test= file.readAll();
        QTextStream ostream(&ofile);
        for(const auto & i: gumbo::getAllJavaScript( test.begin(),test.end() )){
            ostream<<QString::fromUtf8(i.c_str(),int(i.size()))<<endl;
        }
    }

}




