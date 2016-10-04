/*BaiDuUser cpp*/
#include "../BaiDuUser.hpp"
#include "../private/BaiDuUserData.hpp"
#include "../private/BaiDuUserPrivateFunction.hpp"

namespace baidu {

template<>
inline auto getThisData<zone_data::BaiDuUserData *,0>(const BaiDuUser * arg) ->zone_data::BaiDuUserData *{
    return const_cast<BaiDuUser *>(arg)->thisData();
}

template<>
inline auto getThisData<const zone_data::BaiDuUserData *,1>(const BaiDuUser * arg) ->const zone_data::BaiDuUserData *{
    return arg->thisData();
}

#if !defined(zone_this_data)
#define zone_this_data(_v_) auto * varThisData=getThisData<zone_data::BaiDuUserData *,0>(_v_)
#endif
#if !defined(const_zone_this_data)
#define zone_const_this_data(_v_) const auto * varThisData=getThisData<const zone_data::BaiDuUserData *,1>(_v_)
#endif

namespace zone_data {
/********************************zone_data********************************/
BaiDuUserData::BaiDuUserData() {
    static_assert(
        std::has_virtual_destructor<BaiDuUserData>::value,
        "the class must has virtual destructor");

    _m_NetworkCookieJar=new NetworkCookieJar(&_m_NetworkAccessManager);
    _m_NetworkAccessManager.setCookieJar(_m_NetworkCookieJar);
}


BaiDuUserData::~BaiDuUserData() {
}
/********************************zone_data********************************/
}

namespace zone_private_function {
/********************************zone_function********************************/

/********************************zone_function********************************/
}

BaiDuUser::~BaiDuUser() {
    close();
}

BaiDuUser::BaiDuUser():BaiDuUser(ThisDataType(
                         new zone_data::BaiDuUserData,
                         [](auto *arg){delete arg;},memory::Allocator<int>{})) {
}

BaiDuUser::BaiDuUser(ThisDataType && _arg_):
    thisData_(std::move(_arg_)){
}

auto BaiDuUser::thisData()->zone_data::BaiDuUserData *{
    return static_cast<zone_data::BaiDuUserData *>(thisData_.get());
}

auto BaiDuUser::thisData() const->const zone_data::BaiDuUserData *{
    return static_cast<const zone_data::BaiDuUserData *>(thisData_.get());
}

void BaiDuUser::open(const QString&arg){
    zone_this_data(this);
    if (isOpen()) { return; }
    varThisData->_m_BaiDuUserCache.setFileName(arg);
    varThisData->_m_BaiDuUserCache.open();
}

void BaiDuUser::close() {
    zone_this_data(this);
    varThisData->_m_BaiDuUserCache.write();
    varThisData->_m_BaiDuUserCache={};
}

void BaiDuUser::setUserName(const QString&arg){
    zone_this_data(this);
    varThisData->_m_BaiDuUserCache.setUserName(arg);
}

void BaiDuUser::setPassWord(const QString&arg){
    zone_this_data(this);
    varThisData->_m_BaiDuUserCache.setPassWord(arg);
}

QString BaiDuUser::getUsername()const {
    zone_const_this_data(this);
    return varThisData->_m_BaiDuUserCache.getUserName();
}

QString BaiDuUser::getPassword()const {
    zone_const_this_data(this);
    return varThisData->_m_BaiDuUserCache.getPassWord();
}

bool BaiDuUser::isOpen() const {
    zone_const_this_data(this);
    return varThisData->_m_BaiDuUserCache.isOpen();
}

namespace __login {
namespace {

Q_DECL_CONSTEXPR QLatin1Literal operator""_qsl(const char *arg,std::size_t n){
    return QLatin1Literal(arg,int(n));
}

class Login final:
    public BaiDuUser::StepNext,
    public std::enable_shared_from_this<Login>{
    Login(const Login&)=delete;
    Login(Login&&)=delete;
    Login&operator=(const Login&)=delete;
    Login&operator=(Login&&)=delete;
public:
    Login() {}
    std::shared_ptr<BaiDuUser> baiDuUser;
    
    enum LogInSteps :int{
        s_error,
        s_start,
        s_finished
    };

    static QString step_to_string(LogInSteps arg) {
        switch (arg) {
            case s_error:return "error"_qsl; break;
            case s_start:return "start"_qsl; break;
            case s_finished:return "finished"_qsl; break;
            default:break;
        }
        return "unknow step"_qsl;
    }

    LogInSteps loginStep=s_start;
    LogInSteps loginStepNext=s_start;
    QString errorString{"unknow error"_qsl};
    bool logInFinishedCalled=false;

    void next_step() {
        switch (loginStepNext) {
            case s_error:login_error(); break;
            case s_start:break;
            case s_finished:login_finished(); break;
        }
    }

    void next() override { 
        next_step();
    }

    void login_error() {
        logInFinishedCalled=true;
        auto var_step_name=step_to_string(loginStep);
        baiDuUser->loginFinished(false,
            "login error@"_qsl
            +std::move(var_step_name)
            + " : "_qsl
            +std::move(errorString)
        );
    }

    void login_finished() {
        logInFinishedCalled=true;
        loginStep=s_finished;
        loginStepNext=s_finished;
        baiDuUser->loginFinished(true,{});
    }

    ~Login() {
        if (false==logInFinishedCalled) {
            login_error();
        }
    }
private:
    MEMORY_CLASS_NEW_DELETE
};

}/*namespace*/
}/*namespace __login*/

void BaiDuUser::login() {
    auto varLogin=memory::make_shared<__login::Login>();
    {/*init login data*/
        varLogin->baiDuUser=this->shared_from_this();
    }
    varLogin->next_step();
}

bool BaiDuUser::isLogin() const{
    zone_const_this_data(this);
    return varThisData->_m_IsLogin;
}

}/*namespace baidu*/


