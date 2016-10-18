#include<iostream>
#include<cinttypes>
#include<fstream>
#include<string>
#include<vector>
#include<regex>

using namespace std::string_literals;

std::string headers=u8R"=___=(/**/
#include <memory>
#include <cstddef>
#include <typeinfo>
#include <typeindex>
#include <cinttypes>
#include <type_traits>

)=___=";

class TypeInfo {
    inline void _p_update_();
public:
    std::string type_name;
    std::string type_name_index;
    std::string type_name_name;
    TypeInfo(const std::string &arg):type_name(arg) { _p_update_(); }
    TypeInfo(std::string &&arg):type_name(std::move(arg)) { _p_update_(); }
};

inline void TypeInfo::_p_update_() {
    const static std::regex reg(u8R"=rrr=( )=rrr="s);
    auto tmp=std::regex_replace(type_name,reg,"_"s);
    type_name_index="basictype_"s+tmp;
    type_name_name="_m_"s+tmp;
}

std::vector<TypeInfo>types={
"int"s,
"char"s,
"bool"s,
"long"s,
"short"s,
"float"s,
"double"s,
"wchar_t"s,
"char16_t"s,
"char32_t"s,
"long long"s,
"long double"s,
"signed char"s,
"unsigned int"s,
"unsigned char"s,
"unsigned long"s,
"unsigned short"s,
"unsigned long long"s,
};
//u8R"==()==";
int main(int,char **){

    std::ofstream ofs("BasicSharedData.hpp"s);

    ofs<<headers;

    ofs<<u8R"(union BasicData {
)"s;
    ofs<<u8R"==(/*pointer data*/
    void * _m_void_pointer;
    /*shared pointer data*/
    std::shared_ptr<void> _m_shared_pointer;
    /*pod data*/
)=="s;

    for (const auto & i:types) {
        ofs<<i.type_name<<u8R"( /**/ )"<<i.type_name_name<<u8R"(;
)";
    }

    ofs<<u8R"(  /*construct*/
)"s;
    for (const auto & i:types) {
        ofs<<u8R"(BasicData(const )"s
            <<i.type_name
            <<u8R"(/**/& arg):)"s
            <<i.type_name_name
            <<u8R"((arg) {}
)"s;
    }

    ofs<<u8R"( /*void * construct*/
    BasicData(const void * const &arg):_m_void_pointer(const_cast<void*>(arg)) {}
    BasicData(void * const & arg):_m_void_pointer(arg) {}
    BasicData(const decltype(nullptr)&arg):_m_void_pointer(arg) {}
    /*construct and destruct*/
    BasicData() {}
    ~BasicData() {}
};

)"s;
        
    ofs<<u8R"(class BasicSharedData {
public:
    enum BasicDataType :std::uint8_t {
        basictype_void_pointer,
        basictype_shared_pointer,
)";

    for (const auto & i:types) {
        ofs<<i.type_name_index<<u8R"(,
)";
    }

    ofs<<u8R"(};
inline void * _p_get_data() const;
public:
    inline BasicDataType getType() const noexcept(true);
    inline bool isSharedPointer() const noexcept(true);
    inline const std::type_index&getTypeIndex() const noexcept(true);
    inline bool isConst() const noexcept(true);  
inline void * getData() const {return _p_get_data();}
)"s;

    ofs<<u8R"(
protected:
    using _T_=std::shared_ptr<void>;
    BasicData _m_data;
    std::type_index _m_type_index;
    BasicDataType _m_type:8;
    bool _m_is_const:1;
    inline void _p_free() { _m_data._m_shared_pointer.~shared_ptr(); }
    inline void _p_try_free() { if (isSharedPointer()) { _p_free(); } }
public:
    inline ~BasicSharedData() { _p_try_free(); }
    inline BasicSharedData();
    inline BasicSharedData(const void*&,const std::type_index&);
    inline BasicSharedData(void*&,const std::type_index&);
    inline BasicSharedData(const decltype(nullptr)&);
public:
)"s;

    for (const auto & i:types) {
        ofs<<u8R"( inline BasicSharedData(const )"s<<i.type_name<<u8R"(/**/&);
)"s;
    }

    ofs<<u8R"(
)"s;

    for (const auto & i:types) {
        ofs<<u8R"( inline BasicSharedData()"s<<i.type_name<<u8R"(/**/&);
)"s;
    }

    ofs<<u8R"(};
)"s;

    /****************************************/

    ofs<<u8R"(/****************************************************/
inline const std::type_index&
BasicSharedData::getTypeIndex() const noexcept(true) {
    return _m_type_index;
}

inline bool BasicSharedData::isSharedPointer() const noexcept(true) {
    return _m_type==basictype_shared_pointer;
}

inline auto BasicSharedData::getType() const noexcept(true)
->BasicSharedData::BasicDataType {
    return static_cast<BasicDataType>(_m_type);
}
)"s;

    ofs<<u8R"(
inline BasicSharedData::BasicSharedData():
    _m_data(nullptr),
    _m_type_index(typeid(void*)),
    _m_type(basictype_void_pointer),
    _m_is_const(false) {
}

inline BasicSharedData::BasicSharedData(const void *&arg,const std::type_index&argI):
    _m_data(arg),
    _m_type_index(argI),
    _m_type(basictype_void_pointer),
    _m_is_const(true) {
}

inline BasicSharedData::BasicSharedData(const decltype(nullptr)&arg):
    _m_data(arg),
    _m_type_index(typeid(void*)),
    _m_type(basictype_void_pointer),
    _m_is_const(true) {
}

inline BasicSharedData::BasicSharedData(void *&arg,const std::type_index&argI):
    _m_data(arg),
    _m_type_index(argI),
    _m_type(basictype_void_pointer),
    _m_is_const(false) {
}
)"s;

    for (const auto & i:types) {
        ofs<<u8R"(inline BasicSharedData::BasicSharedData()"s;
        ofs<<u8R"(const )"s<<i.type_name<<u8R"( & arg ): 
)"s;
        ofs<<u8R"(_m_data(arg),
)"s;
        ofs<<u8R"(_m_type_index(typeid( )"s<<i.type_name<<u8R"( )) ,
)"s;
        ofs<<u8R"(_m_type( )"s<<i.type_name_index <<u8R"( ), 
)"s;
        ofs<<u8R"(_m_is_const(true) {}
 )"s;

    } 

    ofs<<u8R"(
)"s;

    for (const auto & i:types) {
        ofs<<u8R"(inline BasicSharedData::BasicSharedData()"s;
        ofs<<u8R"()"s<<i.type_name<<u8R"( & arg ): 
)"s;
        ofs<<u8R"(_m_data(arg),
)"s;
        ofs<<u8R"(_m_type_index(typeid( )"s<<i.type_name<<u8R"( )) ,
)"s;
        ofs<<u8R"(_m_type( )"s<<i.type_name_index <<u8R"( ), 
)"s;
        ofs<<u8R"(_m_is_const(false) {}
 )"s;

    } 

    {
        ofs<<u8R"(inline void * BasicSharedData::_p_get_data() const {
    switch (this->_m_type) {
        case basictype_void_pointer:return _m_data._m_void_pointer;
        case basictype_shared_pointer:return _m_data._m_shared_pointer.get();
)"s;

        for (const auto & i:types) {
            ofs<<u8R"(case )"s<<i.type_name_index<<u8R"( : return const_cast< )"s
                <<i.type_name
                <<u8R"(* >( &(_m_data.)"s
                <<i.type_name_name<<u8R"( ) );
)"s;
        }

        ofs<<u8R"(}
return nullptr;
}
)"s;
    }

    ofs<<u8R"(inline bool BasicSharedData::isConst() const noexcept(true){
    return _m_is_const;
}
)"s;

   // system("pause");

}



















