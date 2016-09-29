#include <iostream>
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
    ~TestClass() {
        std::cout<<"this should not be run!"<<std::endl;
    }
};

static unsigned char test_data[sizeof(TestClass)];
static unsigned char test_data1[sizeof(TestClass)];
}

TestStaticPointer::TestStaticPointer(){

    {/*标准测试*/
        static memory::StaticPoionter<TestClass> test(test_data);
    }
    {/*测试析构*/
        memory::StaticPoionter<TestClass> test1(test_data1);
    }
}
