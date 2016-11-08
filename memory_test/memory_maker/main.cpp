
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cinttypes>
#include <initializer_list>

class string_view {
public:
    const char * data;
    std::size_t length;
};

using namespace  std::string_literals;

inline constexpr string_view operator""_sw(const char * arg,std::size_t n) {
    return{ arg,n };
}

inline std::ostream & operator<<(std::ostream& arg,
                          const string_view&data) {
    arg.write(data.data,data.length);
    return arg;
}

using int_t=int;

class Item {
public:
    int_t source;
    int_t target;
    Item(int_t a,int_t b):source(a),target(b) {}
    Item():source(0),target(0) {}
};

inline void make(
        std::ostream & ofs,
        std::vector<int_t> &items
) {
    std::sort(items.begin(),items.end());
    int_t var_max=*items.rbegin();
    std::vector<Item> var_items;

    {
        auto j=items.begin();
        for (int_t i=1; i<=var_max; ++i) {
            if (i<=(*j)) {
                var_items.emplace_back(i,*j);
            }
            else {
                ++j;
                var_items.emplace_back(i,*j);
            }
        }
    }

    {/*write bom*/
        const char bom[]={ char(0x00EF),char(0x00BB),char(0x00BF) };
        ofs.write(bom,3);
    }

    {
        ofs<<"/*"_sw;
        ofs<<items.size();
        ofs<<u8R"(*/
)"_sw;
    }

    {/*write header*/
        ofs<<u8R"___(/*std::*/
#include <mutex>
     #include <memory>
     #include <atomic>
     #include <thread>
     #include <cstddef>
     #include <utility>
     #include <cstdbool>
     #include <cinttypes>
     #include <type_traits>
     #include <initializer_list>

     /*boost::pool*/
     #include "../../cplusplus_base_library/Qt/boost/pool/pool.hpp"

     namespace  {
     namespace  _p_file{

     class Memory{
     public:
         typedef int int_t;
          /*boost::pool*/
    class pool_t {
        typedef boost::pool<boost::default_user_allocator_malloc_free> _pool_t;
        typedef std::recursive_mutex _mutex_t;
        typedef std::unique_lock<_mutex_t> _mlock_t;
        _pool_t _pm_data;
        _mutex_t _pm_mutex;
        public:
            pool_t(int_t arg):_pm_data(arg) {}
            void * malloc() { _mlock_t _{_pm_mutex}; return _pm_data.malloc(); }
            void free(void *arg) {_mlock_t _{_pm_mutex}; return _pm_data.free(arg); }
            void release_memory() {_mlock_t _{_pm_mutex}; _pm_data.release_memory(); }
    };
     public:
         std::atomic_bool _pm_is_free_memroy_not_used{false};
     public:

         class MFItem{
         public:
             virtual ~MFItem()=default;
             virtual void free(void *)=0;
             virtual int_t size(void *) const =0;
         };

         class Item{
         public:
             MFItem * data;
         };

         class Item_default final:public MFItem{
         public:
             int_t size(void *arg)const override{
#if defined(WIN32)||defined(_WIN32)
            return static_cast<int_t>(::_msize(arg));
#else
            return static_cast<int_t>(::malloc_usable_size(arg));
#endif
    return -1;
    (void)arg;
}
             void free(void * arg) override{std::free(arg);}
             void * malloc(int_t arg){
                auto var=reinterpret_cast<Item *>(std::malloc(arg));
                if (var) { 
                 var->data=this;
                  return ++var;
             }
             return nullptr;
             }/*malloc(int_t arg)*/
         }_pm_item_default;

         template<int_t N>
         class Item_N final:public MFItem{
             pool_t _pm_pool{N};
         public:
             void clean(){_pm_pool.release_memory();}
             int_t size(void *)const override{return N;}
             void free(void * arg) override{_pm_pool.free(arg);}
             void * malloc(){
                 auto var=reinterpret_cast<Item *>(_pm_pool.malloc());
                if(var){
                var->data=this;
                return ++var;
            }
            return nullptr;
             }/*void * malloc()*/
         }/*class Item_N*/;

         /*+++*/
         )___"_sw;
    }

    {
        int j=0;
        for (const auto & i:items) {
            ofs<<u8R"(Item_N<)"_sw;
            ofs<<i;
            ofs<<u8R"(> _pm_item_)"_sw;
            ofs<<i;
            ofs<<u8R"(;static void *_p_malloc_)"_sw;
            ofs<<i;
            ofs<<u8R"((Memory *arg){)";
            ofs<<u8R"(return arg->_pm_item_)"_sw;
            ofs<<i;
            ofs<<u8R"(.malloc();})"_sw;
            if ((++j)==63) {
                j=0;
                ofs<<"\n";
            }
        }
        ofs<<"\n";
    }

    {
        ofs<<u8R"(
typedef void*(*type_malloc)(Memory *);
    type_malloc _pm_malloc_functions[)"_sw;
        ofs<<var_items.size();
        ofs<<u8R"(+1]={
/*0*/[](Memory*)->void* {return nullptr; },
    )"_sw;

        {
            int j=0;
            for (const auto &i:var_items) {
                ofs<<u8R"(/*)"_sw;
                ofs<<i.source;
                ofs<<u8R"(*/)"_sw;
                ofs<<u8R"(&Memory::_p_malloc_)"_sw;
                ofs<<i.target;
                ofs<<u8R"(,)"_sw;
                if (++j==64) {
                    ofs<<"\n"; j=0;
                }
            }
            ofs<<"\n";
        }

        ofs<<u8R"(};
Memory() =default;
Memory(const Memory&)=delete;
Memory&operator=(const Memory&)=delete;
Memory(Memory&&)=delete;
Memory&operator=(Memory&&)=delete;
)"_sw;
    }

    {
        ofs<<u8R"(
/*+++*/ 
void * malloc(int_t n){
        constexpr static int_t var_size_of_Item=sizeof(Item);
        if(n<1){return nullptr;}
        if(n>()"_sw;

        ofs<<var_max;

        ofs<<u8R"(-var_size_of_Item)){return _pm_item_default.malloc(n+var_size_of_Item);}
        return _pm_malloc_functions[ n+var_size_of_Item ](this) ;
}

)"_sw;

    }

    {
        ofs<<u8R"(    void free(void * arg){
        if(arg==nullptr){return ;}
        auto var=reinterpret_cast<Item *>(arg);
        --var;
        var->data->free(var);
    }

    int_t size(void * arg)const{
        if(arg==nullptr){return 0;}
        auto var=reinterpret_cast<Item *>(arg);
        --var;
        return var->data->size(var);
    }
private:
)"_sw;
    }

    {
        ofs<<u8R"( /*+++*/
    void _p_clean() noexcept(true){
        try{
)"_sw;

        {
            int j=0;
            for (const auto & i:items) {
                ofs<<u8R"(_pm_item_)"_sw;
                ofs<<i;
                ofs<<u8R"(.clean();)"_sw;
                if ((j++)==63) {
                    j=0; ofs<<"\n";
                }
            }
            ofs<<"\n";
        }

        ofs<<u8R"( 
}catch(...){}
    }
)"_sw;
    }

    {
        ofs<<u8R"(
public:
    /*clean not used memory in another thread*/
    void clean(){
        if( false == _pm_is_free_memroy_not_used.load() ){
            _pm_is_free_memroy_not_used.store(true);
            std::thread([this](){
                _p_clean();
                _pm_is_free_memroy_not_used.store(false);
            }).detach();
        }
    }
};

/*memory::*/
static char _pd_memory[sizeof(Memory)+4];
inline Memory * get_memory(){
    /*never destruct*/
    static auto var=::new(_pd_memory) Memory;
    return var;
}


}/*_p_file*/
}/*namespace*/


namespace memory {

void * malloc(int arg){ return _p_file::get_memory()->malloc(arg); }
void free(void * arg){ return _p_file::get_memory()->free(arg); }
int size(void * arg){ return _p_file::get_memory()->size(arg); }
int cookie_size() { return sizeof(_p_file::Memory::Item*); }

}/*memroy*/


)"_sw;
    }

}

int main(int,char **) {

    std::ofstream ofs("xxx123.cpp");
    std::vector<int_t> s;
    s.reserve(1024*1024);
    for (int i=1; i<=1024; ++i) {
        s.push_back(i*4);
    }
    for (int i=(4096+64); i<=(32*1024); i+=64) {
        s.push_back(i);
    }
    make(ofs,s);

}



