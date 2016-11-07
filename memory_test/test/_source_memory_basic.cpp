/*std::*/
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
    typedef boost::pool<boost::default_user_allocator_malloc_free> pool_t;
public:
    std::atomic_bool _pm_is_free_memroy_not_used{false};
public:

    class MFItem{
    public:
        virtual ~MFItem()=default;
        virtual void free(void *)=0;
        virtual int_t size() const =0;
    };

    class Item{
    public:
        MFItem * data;
    };

    class Item_default final:public MFItem{
    public:
        int_t size()const override{return -1;}
        void free(void * arg) override{std::free(arg);}
        void * malloc(int_t arg){
            auto var=reinterpret_cast<Item *>(std::malloc(arg));
            if(var){var->data=this;}
            return ++var;
        }
    }_pm_item_default;

    template<int_t N>
    class Item_N final:public MFItem{
        pool_t _pm_pool{N+sizeof(Item)};
    public:
        void clean(){_pm_pool.release_memory();}
        int_t size()const override{return N;}
        void free(void * arg) override{_pm_pool.free(arg);}
        void * malloc(){
            auto var=reinterpret_cast<Item *>(_pm_pool.malloc());
            if(var){
                var->data=this;
                return ++var;
            }
            return nullptr;
        }
    };

    /*+++*/
    Item_N<4> _pm_item_4;

    /*+++*/
    void * malloc(int_t n){
        if(n<1){return nullptr;}
        if(n>4){return _pm_item_default.malloc(n);}
        switch (n) {
        case 0:return nullptr;
        case 1:return _pm_item_4.malloc();
        case 2:return _pm_item_4.malloc();
        case 3:return _pm_item_4.malloc();
        case 4:return _pm_item_4.malloc();
        }
        return nullptr;
    }

    void free(void * arg){
        if(arg==nullptr){return ;}
        auto var=reinterpret_cast<Item *>(arg);
        --var;
        var->data->free(var);
    }

    int_t size(void * arg)const{
        if(arg==nullptr){return 0;}
        auto var=reinterpret_cast<Item *>(arg);
        --var;
        return var->data->size();
    }
private:
    /*+++*/
    void _p_clean() noexcept(true){
        try{
            _pm_item_4.clean();
        }catch(...){}
    }
public:
    /*clean not used memory in another thread*/
    void clean(){
        if( false == _pm_is_free_memroy_not_used.load() ){
            std::thread([this](){
                _pm_is_free_memroy_not_used.store(true);
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

namespace memory {

void * malloc(int arg){ return _p_file::get_memory()->malloc(arg); }
void free(void * arg){ return _p_file::get_memory()->free(arg); }
int size(void * arg){ return _p_file::get_memory()->size(arg); }

}/*memroy*/

}/*namespace*/
