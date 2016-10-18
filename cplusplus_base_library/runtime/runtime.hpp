#include<memory>
#include<cstddef>
#include<typeinfo>
#include<typeindex>
#include<cinttypes>
#include<type_traits>

namespace runtimetype {

class SharedVoid {
    union _DataSharedVoid {
        _DataSharedVoid():_m_vd_(nullptr) {}
        _DataSharedVoid(void *arg):_m_vd_(arg) {}
        _DataSharedVoid(const void *arg):_m_vd_(const_cast<void*>(arg)) {}
        ~_DataSharedVoid() {}
        void * _m_vd_;
        std::shared_ptr<void> _m_sd_;
    };
    _DataSharedVoid _m_data_;
    bool _m_is_shared_:1;
    bool _m_is_const_:1;
    inline void _p_free() { _m_data_._m_sd_.~shared_ptr(); }
    inline void _p_try_free() { if (_m_is_shared_) { _p_free(); } }
    inline void _p_create() { ::new(&_m_data_._m_sd_) std::shared_ptr<void>{}; }
    inline void _p_try_create() { if (!_m_is_shared_) { _p_create(); } }
    inline void _p_reset() { _p_try_free(); _m_data_._m_vd_=nullptr; _m_is_shared_=false; }
public:
    inline bool isShared() const { return _m_is_shared_; }
    inline bool isConst() const { return _m_is_const_; }
    inline void * getData() const;
    explicit inline operator bool() const { return getData()!=nullptr; }
public:
    inline SharedVoid():_m_is_shared_(false),_m_is_const_(false) {}
    inline SharedVoid(const decltype(nullptr)&):SharedVoid() {}
    inline SharedVoid(const void * const & arg):_m_data_(arg),_m_is_shared_(false),_m_is_const_(true) {}
    inline SharedVoid(void * const & arg):_m_data_(arg),_m_is_shared_(false),_m_is_const_(false) {}
    inline SharedVoid(const std::shared_ptr<void>&);
    inline SharedVoid(const std::shared_ptr<const void>&);
    inline SharedVoid(std::shared_ptr<void>&&);
    inline SharedVoid(std::shared_ptr<const void>&&);
    inline ~SharedVoid();
public:
    inline void setVoid(void *);
    inline void setVoid(const void *);
    inline void setShared(const std::shared_ptr<void>&);
    inline void setShared(std::shared_ptr<void>&&);
    inline void setShared(const std::shared_ptr<const void>&);
    inline void setShared(std::shared_ptr<const void>&&);
    inline void set(void * const & arg) { setVoid(arg); }
    inline void set(const void * const & arg) { setVoid(arg); }
    inline void set(std::shared_ptr<void>&& arg) { setShared(std::move(arg)); }
    inline void set(std::shared_ptr<const void>&&arg) { setShared(std::move(arg)); }
    inline void set(const std::shared_ptr<const void>&arg) { setShared(arg); }
    inline void set(const std::shared_ptr<void>&arg) { setShared(arg); }
    inline void set(const decltype(nullptr)&) { _p_reset(); _m_is_const_=false; }
public:
    inline SharedVoid&operator=(const SharedVoid&);
    inline SharedVoid&operator=(SharedVoid&&);
    inline SharedVoid(const SharedVoid&);
    inline SharedVoid(SharedVoid&&);
public:
    friend bool operator<(const SharedVoid& l,const SharedVoid & r) { return l.getData()<r.getData(); }
    friend bool operator>(const SharedVoid& l,const SharedVoid & r) { return l.getData()>r.getData(); }
    friend bool operator>=(const SharedVoid& l,const SharedVoid & r) { return l.getData()>=r.getData(); }
    friend bool operator<=(const SharedVoid& l,const SharedVoid & r) { return l.getData()<=r.getData(); }
    friend bool operator==(const SharedVoid& l,const SharedVoid & r) { return l.getData()==r.getData(); }
    friend bool operator!=(const SharedVoid& l,const SharedVoid & r) { return l.getData()!=r.getData(); }
};

class RuntimeType {
public:
    SharedVoid data;
    std::type_index type;
    RuntimeType(const SharedVoid &argD,const std::type_index&argT):data(argD),type(argT) {}
    RuntimeType(const SharedVoid &argD,std::type_index&&argT):data(argD),type(std::move(argT)) {}
    RuntimeType(SharedVoid &&argD,const std::type_index&argT):data(std::move(argD)),type(argT) {}
    RuntimeType(SharedVoid &&argD,std::type_index&&argT):data(std::move(argD)),type(std::move(argT)) {}
};

template<typename __U__,typename __T__>
inline RuntimeType make_runtime_type(__T__&&argData) {
    using __A__=std::remove_cv_t<
        std::remove_pointer_t<
        std::remove_reference_t<__U__>/**/>/**/>;
    return{ std::forward<__T__>(argData)
    ,std::type_index{typeid(__A__)} };
}

inline void * SharedVoid::getData() const {
    if (isShared()) {
        return _m_data_._m_sd_.get();
    }
    return _m_data_._m_vd_;
}

inline SharedVoid::~SharedVoid() { _p_try_free(); }

inline void SharedVoid::setVoid(void *arg) {
    _p_try_free();
    _m_is_shared_=false;
    _m_is_const_=false;
    _m_data_._m_vd_=arg;
}

inline void SharedVoid::setVoid(const void *arg) {
    _p_try_free();
    _m_is_shared_=false;
    _m_is_const_=true;
    _m_data_._m_vd_=const_cast<void*>(arg);
}

inline void SharedVoid::setShared(const std::shared_ptr<void>&arg) {
    using _T_=std::shared_ptr<void>;
    if (bool(arg)==false) { return set(nullptr); }
    if (isShared()) {
        _m_data_._m_sd_=arg;
    }
    else {
        ::new (&_m_data_._m_sd_) _T_{ arg };
        _m_is_shared_=true;
    }
    _m_is_const_=false;
}

inline void SharedVoid::setShared(std::shared_ptr<void>&&arg) {
    using _T_=std::shared_ptr<void>;
    if (bool(arg)==false) { return set(nullptr); }
    if (isShared()) {
        _m_data_._m_sd_=std::move(arg);
    }
    else {
        ::new (&_m_data_._m_sd_) _T_{ std::move(arg) };
        _m_is_shared_=true;
    }
    _m_is_const_=false;
}

inline void SharedVoid::setShared(const std::shared_ptr<const void>&arg) {
    using _T_=std::shared_ptr<void>;
    if (bool(arg)==false) { return set(nullptr); }
    if (isShared()) {
        _m_data_._m_sd_=std::const_pointer_cast<void>(arg);
    }
    else {
        ::new (&_m_data_._m_sd_) _T_{ std::const_pointer_cast<void>(arg) };
        _m_is_shared_=true;
    }
    _m_is_const_=true;
}

inline void SharedVoid::setShared(std::shared_ptr<const void>&&arg) {
    using _T_=std::shared_ptr<void>;
    if (bool(arg)==false) { return set(nullptr); }
    if (isShared()) {
        _m_data_._m_sd_=std::const_pointer_cast<void>(std::move(arg));
    }
    else {
        ::new (&_m_data_._m_sd_) _T_{ std::const_pointer_cast<void>(std::move(arg)) };
        _m_is_shared_=true;
    }
    _m_is_const_=true;
}

inline SharedVoid::SharedVoid(const std::shared_ptr<void>&arg)
    :_m_is_shared_(true),_m_is_const_(false) {
    if (false==bool(arg)) {
        _m_is_shared_=false;
        return;
    }
    using _T_=std::shared_ptr<void>;
    ::new (&_m_data_._m_sd_) _T_{ arg };
}

inline SharedVoid::SharedVoid(const std::shared_ptr<const void>&arg)
    :_m_is_shared_(true),_m_is_const_(true) {
    if (false==bool(arg)) {
        _m_is_shared_=false;
        return;
    }
    using _T_=std::shared_ptr<void>;
    ::new (&_m_data_._m_sd_) _T_{ std::const_pointer_cast<void>(arg) };
}

inline SharedVoid::SharedVoid(std::shared_ptr<void>&&arg)
    :_m_is_shared_(true),_m_is_const_(false) {
    if (false==bool(arg)) {
        _m_is_shared_=false;
        return;
    }
    using _T_=std::shared_ptr<void>;
    ::new (&_m_data_._m_sd_) _T_{ std::move(arg) };
}

inline SharedVoid::SharedVoid(std::shared_ptr<const void>&&arg)
    :_m_is_shared_(true),_m_is_const_(true) {
    if (false==bool(arg)) {
        _m_is_shared_=false;
        return;
    }
    using _T_=std::shared_ptr<void>;
    ::new (&_m_data_._m_sd_) _T_{ std::const_pointer_cast<void>(std::move(arg)) };
}

inline SharedVoid&SharedVoid::operator=(const SharedVoid&arg) {
    if (this==&arg) { return *this; }
    _m_is_const_=arg._m_is_const_;
    using _T_=std::shared_ptr<void>;
    if (arg.isShared()) {

        if (false==bool(arg._m_data_._m_sd_)) {
            _p_reset();
            return *this;
        }

        if (this->isShared()) {
            _m_data_._m_sd_=arg._m_data_._m_sd_;
        }
        else {
            ::new (&_m_data_._m_sd_)_T_{ arg._m_data_._m_sd_ };
            _m_is_shared_=true;
        }
    }
    else {
        if (this->isShared()) {
            _p_free();
            _m_is_shared_=false;
            _m_data_._m_vd_=arg._m_data_._m_vd_;
        }
        else {
            _m_data_._m_vd_=arg._m_data_._m_vd_;
        }
    }
    return *this;
}

inline SharedVoid&SharedVoid::operator=(SharedVoid&&arg) {
    if (this==&arg) { return *this; }
    _m_is_const_=arg._m_is_const_;
    using _T_=std::shared_ptr<void>;
    if (arg.isShared()) {

        if (false==bool(arg._m_data_._m_sd_)) {
            _p_reset();
            return *this;
        }

        if (this->isShared()) {
            _m_data_._m_sd_=std::move(arg._m_data_._m_sd_);
        }
        else {
            ::new (&_m_data_._m_sd_)_T_{ std::move(arg._m_data_._m_sd_) };
            _m_is_shared_=true;
        }
    }
    else {
        if (this->isShared()) {
            _p_free();
            _m_is_shared_=false;
            _m_data_._m_vd_=arg._m_data_._m_vd_;
        }
        else {
            _m_data_._m_vd_=arg._m_data_._m_vd_;
        }
    }
    return *this;
}

inline SharedVoid::SharedVoid(const SharedVoid&arg)
    :_m_data_(arg._m_data_._m_vd_)
    ,_m_is_shared_(arg._m_is_shared_)
    ,_m_is_const_(arg._m_is_const_) {
    using _T_=std::shared_ptr<void>;
    if (arg.isShared()) {
        if (bool(arg._m_data_._m_sd_)==false) {
            _m_is_shared_=false;
            _m_data_._m_vd_=nullptr;
            return;
        }
        ::new (&_m_data_._m_sd_) _T_{ arg._m_data_._m_sd_ };
    }
}

inline SharedVoid::SharedVoid(SharedVoid&&arg)
    :_m_data_(arg._m_data_._m_vd_)
    ,_m_is_shared_(arg._m_is_shared_)
    ,_m_is_const_(arg._m_is_const_) {
    using _T_=std::shared_ptr<void>;
    if (arg.isShared()) {
        if (bool(arg._m_data_._m_sd_)==false) {
            _m_is_shared_=false;
            _m_data_._m_vd_=nullptr;
            return;
        }
        ::new (&_m_data_._m_sd_) _T_{ std::move(arg._m_data_._m_sd_) };
    }
}

}/*namespace runtimetype*/



