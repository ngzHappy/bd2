#ifndef TESTCOMPILER_HPP
#define TESTCOMPILER_HPP

namespace class_namespace {
namespace TestCompiler {

constexpr int key_0=0;typedef int value_0;
constexpr int key_1=1;
constexpr int key_2=2;

template<int>class Value;

template<>
class Value<0>{
public:
    value_0 _m_Value0;
    auto & value(){return _m_Value0;}
    const auto & value()const{return _m_Value0;}
};

template<>
class Value<1>{
public:
    value_0 _m_Value0;
    auto & value(){return _m_Value0;}
    const auto & value()const{return _m_Value0;}
};

template<>
class Value<2>{
public:
    value_0 _m_Value0;
    auto & value(){return _m_Value0;}
    const auto & value()const{return _m_Value0;}
};

template<>
class Value<3>{
public:
    value_0 _m_Value0;
    auto & value(){return _m_Value0;}
    const auto & value()const{return _m_Value0;}
};

}/*TestCompiler*/
}/*class_namespace*/

class TestCompiler
        :public class_namespace::TestCompiler::Value<class_namespace::TestCompiler::key_0>
        ,public class_namespace::TestCompiler::Value<class_namespace::TestCompiler::key_1>
        ,public class_namespace::TestCompiler::Value<class_namespace::TestCompiler::key_2>
{
public:
    TestCompiler(decltype(nullptr)=nullptr);

    template<int _N_>
    decltype(auto) get(){
        using namespace class_namespace::TestCompiler;
        return Value<_N_>::value();
    }

    template<int _N_>
    decltype(auto) get() const {
        using namespace class_namespace::TestCompiler;
        return Value<_N_>::value();
    }

};

#endif // TESTCOMPILER_HPP
