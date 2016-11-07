namespace memory {

extern void * malloc(int arg);
extern void free(void * arg);
extern int size(void * arg);

}/*memroy*/



#include<iostream>
int main(int ,char **){

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

}
