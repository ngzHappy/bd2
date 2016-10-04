#include "TestGzip.hpp"
#include <text/gzip.hpp>

TestGzip::TestGzip()
{
    QByteArray test("12345");
    QByteArray tmp=text::gzip(test.begin(),test.end());
    QByteArray test1=text::ungzip(tmp.begin(),tmp.end());
    if(test==test1){

    }
}
