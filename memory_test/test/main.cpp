namespace memory {

extern void * malloc(int arg);
extern void free(void * arg);
extern int size(void * arg);

}/*memroy*/

#include<mutex>
#include<cassert>
#include<iostream>
#include<cstdlib>
#include<memory>
#include<thread>

int main(int,char **) {

    {
        void * data=memory::malloc(4);
        std::cout<<memory::size(data)<<std::endl;
        memory::free(data);
    }

    {
        void * data=memory::malloc(32768);
        std::cout<<memory::size(data)<<std::endl;
        memory::free(data);
    }

    auto test=[]() {
       
        {
            int *data;
            for (int i=sizeof(int); i<1024*33; ++i) {
                for (int j=0; j<8; ++j) {
                    data=reinterpret_cast<int *>(memory::malloc(i));
                    *data=332;
                    auto size=memory::size(data);
                    assert(size>0);
                    assert(size>i);
                    assert((size-i)<=100);

                    (void)size;
                    memory::free(data);
                }
            }
        }
    };

    /*test in one thread*/
    test();

    /*test in multi thread*/
    std::thread all_test[]={
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
        std::thread(test),
    };

    for (auto & i:all_test) {
        if (i.joinable()) {
            i.join();
        }
    }

#if defined(_MSC_VER)
    system("pause");
#endif

}
