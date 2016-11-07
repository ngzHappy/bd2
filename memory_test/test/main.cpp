namespace memory {

extern void * malloc(int arg);
extern void free(void * arg);
extern int size(void * arg);

}/*memroy*/


#include<cassert>
#include<iostream>
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

    for (int i=1; i<1024*33; ++i) {
        void *data=memory::malloc(i);
        auto size=memory::size(data);
        if (size>0) {
            assert(size>=i);
        }
        memory::free(data);
    }

}
