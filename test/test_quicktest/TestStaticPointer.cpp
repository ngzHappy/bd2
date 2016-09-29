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

class TestClass2 {};
class TestClass3 :public TestClass2 {};

static unsigned char test_data[sizeof(TestClass)];
static unsigned char test_data1[sizeof(TestClass)];
static unsigned char test_data2[sizeof(TestClass2)];
static unsigned char test_data3[sizeof(TestClass3)];
}

TestStaticPointer::TestStaticPointer(){

    {/*标准测试*/
        static memory::StaticPoionter<TestClass> test(test_data);
    }
    {/*测试析构*/
        memory::StaticPoionter<TestClass> test1(test_data1);
    }
    {
        memory::StaticPoionter<TestClass2> test2(test_data2);
        memory::StaticPoionter<TestClass3> test3(test_data3);
        test2=test3;
       
    }
}
