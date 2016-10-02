#include "../private_cplusplus_base_library/cplusplus_base_library_global.hpp"
#include "../cplusplus_base_library.hpp"
#include "../argument/argument.hpp"

/*用于测试动态链接库*/
cplusplus_base_library::cplusplus_base_library(){


}

/*用于测试编译器*/
void cplusplus_base_library::test_code_never_used(){

    using argument::akv;
    using argument::aget;
    using argument::atie;

    {
        int a=12;
        int xee=aget<int>(atie(akv<int>(a),akv<double>(2)));
        (void)xee;
    }

    {
        int a=12;
        void * xee=aget<float>(atie(akv<int>(a),akv<double>(2)));
        (void)xee;
    }

    {
        argument::cat_tuple_t<
            std::tuple<int>,
            std::tuple<double,float>,
            std::tuple<int*>,
            std::tuple<float*,double*>
        > test{1,1.0,1.0f,nullptr,nullptr,nullptr};
        (void)test;
    }

    {
        int test=0;
        switch (test) {
            case 0: {using namespace std; }break;
            case 1: {using namespace argument; } break;
            default:break;
        }
        (void)test;
    }

}

cplusplus_base_library::~cplusplus_base_library(){

}


/*endl of the file*/
