namespace memory {

extern void * malloc(int arg);
extern void free(void * arg);
extern int size(void * arg);

}/*memroy*/


#include<cassert>
#include<iostream>
#include<memory>

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

    {
        int *data;
        for (int i=sizeof(int); i<1024*33; ++i) {
            data=reinterpret_cast<int *>(memory::malloc(i));
            *data=332;
            auto size=memory::size(data);
            assert(size>0); 
            assert(size>i);
            assert((size-i)<=100);    
            
 
            memory::free(data);
        }
    }
    
}
