#include "TestStaticPointer.hpp"
#include <memory/MemoryLibrary.hpp>

namespace {

class TestClass {
    int a,b,c;
    double e,f,g;
    float i,j,k;
public:
    TestClass() :a(0),b(1),c(2),
    e(0),f(1),g(2),
    i(0),j(1),k(2){}
    ~TestClass() {}
};

static unsigned char test_data[sizeof(TestClass)];

}

TestStaticPointer::TestStaticPointer(){

    static memory::StaticPoionter<TestClass> test(test_data);

}
