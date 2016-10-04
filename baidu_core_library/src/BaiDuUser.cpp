/*BaiDuUser cpp*/
#include "../BaiDuUser.hpp"
#include "../private/BaiDuUserData.hpp"
#include "../private/BaiDuUserPrivateFunction.hpp"
#include <QtCore/qdatetime.h>
#include <QtCore/qurl.h>
#include <QtScript>
#include <QtCrypto>
#include <QtNetwork>

namespace baidu {

namespace {

inline Q_DECL_CONSTEXPR QLatin1Literal operator""_qsl(const char *arg,std::size_t n) {
    return QLatin1Literal(arg,int(n));
}

inline QByteArray operator""_qb(const char *arg,std::size_t n) {
    return QByteArray(arg,int(n));
}

}

template<>
inline auto getThisData<zone_data::BaiDuUserData *,0>(const BaiDuUser * arg) ->zone_data::BaiDuUserData * {
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
    [](auto *arg) {delete arg; },memory::Allocator<int>{})) {
}

BaiDuUser::BaiDuUser(ThisDataType && _arg_):
    thisData_(std::move(_arg_)) {
}

auto BaiDuUser::thisData()->zone_data::BaiDuUserData * {
    return static_cast<zone_data::BaiDuUserData *>(thisData_.get());
}

auto BaiDuUser::thisData() const->const zone_data::BaiDuUserData *{
    return static_cast<const zone_data::BaiDuUserData *>(thisData_.get());
}

void BaiDuUser::open(const QString&arg) {
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

void BaiDuUser::setUserName(const QString&arg) {
    zone_this_data(this);
    varThisData->_m_BaiDuUserCache.setUserName(arg);
}

void BaiDuUser::setPassWord(const QString&arg) {
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

class Login final :
    public BaiDuUser::StepNext,
    public std::enable_shared_from_this<Login> {
    Login(const Login&)=delete;
    Login(Login&&)=delete;
    Login&operator=(const Login&)=delete;
    Login&operator=(Login&&)=delete;
public:
    Login() {}
    std::weak_ptr<BaiDuUser> baiDuUser;

    enum LogInSteps :int {
        s_error,
        s_start,s_getbaidu_cookie=s_start,
        s_get_baidu_token,
        s_finished
    };

    static QString step_to_string(LogInSteps arg) {
        switch (arg) {
            case s_error:return "error"_qsl; break;
            case s_start:return "get baidu cookie"_qsl; break;
            case s_get_baidu_token:return "getBaiduToken"_qsl; break;
            case s_finished:return "finished"_qsl; break;
            default:break;
        }
        return "unknow step"_qsl;
    }

    LogInSteps loginStep=s_start;
    LogInSteps loginStepNext=s_start;
    QString errorString{ "unknow error"_qsl };
    bool logInFinishedCalled=false;

    void getBaiduToken() {

        auto varBaiDuUser=baiDuUser.lock();
        if (false==varBaiDuUser) { return; }

        zone_this_data(varBaiDuUser.get());

        /*varLockThis=this->shared_from_this(),*/

    }

    void next_step() {
        switch (loginStepNext) {
            case s_error:login_error(); break;
            case s_start:getBaiDuCookie(); break;
            case s_get_baidu_token:getBaiduToken(); break;
            case s_finished:login_finished(); break;
        }
    }

    void next() override {
        next_step();
    }

    void login_error() {
        logInFinishedCalled=true;
        auto var_step_name=step_to_string(loginStep);
        auto varBaiDuUser=baiDuUser.lock();
        if (false==varBaiDuUser) { return; }
        varBaiDuUser->loginFinished(false,
            "login error@"_qsl
            +std::move(var_step_name)
            +" : "_qsl
            +std::move(errorString)
        );
    }

    void login_finished() {
        logInFinishedCalled=true;
        loginStep=s_finished;
        loginStepNext=s_finished;
        auto varBaiDuUser=baiDuUser.lock();
        if (false==varBaiDuUser) { return; }
        varBaiDuUser->loginFinished(true,{});
    }

    class StaticData_getBaiDuCookie {
    public:
        QUrl baidu_url;
        QByteArray key_user_agent;
        StaticData_getBaiDuCookie():
            baidu_url(QString("http://www.baidu.com")),
            key_user_agent("User-Agent"_qb) {
        }
    };
    static char _psd_getBaiDuCookie[sizeof(StaticData_getBaiDuCookie)];
    void getBaiDuCookie() {
        static memory::StaticPoionter<StaticData_getBaiDuCookie> varStaticData{
            _psd_getBaiDuCookie };

        /*初始化请求*/
        QNetworkRequest varRequest;
        varRequest.setUrl(varStaticData->baidu_url);
        varRequest.setRawHeader(varStaticData->key_user_agent,BaiDuUser::userAgent());

        /*获得baidu user*/
        auto varBaiDuUser=baiDuUser.lock();
        if (false==varBaiDuUser) { return; }

        /*获得networkaccessmanager*/
        auto varNAM=varBaiDuUser->getNetworkAccessManager();

        /*获得reply*/
        auto varReply=varNAM->get(varRequest);

        /*cookie 已经写入 cookiejar*/
        varReply->connect(varReply,&QNetworkReply::finished,
            [varLockThis=this->shared_from_this(),varReply,this]() {

                {
                    /*这些数据无用*/
                    varReply->close();
                    varReply->deleteLater();

                    auto varBaiDuUser=baiDuUser.lock();
                    if (false==varBaiDuUser) { return; }

                    if (varReply->error()!=QNetworkReply::NoError) {
                        loginStepNext=s_error;
                        errorString=varReply->errorString();
                    }
                    else {
                        loginStepNext=s_get_baidu_token;
                    }
                }

                next_step();

        });

    }

    ~Login() {
        if (false==logInFinishedCalled) {
            logInFinishedCalled=true;
            login_error();
        }
    }
private:
    MEMORY_CLASS_NEW_DELETE
};

char Login::_psd_getBaiDuCookie[sizeof(StaticData_getBaiDuCookie)];

}/*namespace*/
}/*namespace __login*/

void BaiDuUser::login() {
    auto varLogin=memory::make_shared<__login::Login>();
    {/*init login data*/
        varLogin->baiDuUser=this->shared_from_this();
        zone_this_data(this);
        varThisData->_m_GID=gid();
    }
    varLogin->next_step();
}

NetworkAccessManager * BaiDuUser::getNetworkAccessManager() const {
    zone_const_this_data(this);
    return const_cast<NetworkAccessManager *>(
        &(varThisData->_m_NetworkAccessManager));
}

bool BaiDuUser::isLogin() const {
    zone_const_this_data(this);
    return varThisData->_m_IsLogin;
}

QByteArray BaiDuUser::currentTime() {
    return QByteArray::number(QDateTime::currentMSecsSinceEpoch());
}

static char _p_userAgent_[sizeof(QByteArray)];
QByteArray BaiDuUser::userAgent() {
    static memory::StaticPoionter<QByteArray> varAns{ _p_userAgent_,
            "Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko"_qb
    };
    return *varAns;
}

QByteArray BaiDuUser::gid() {

    QByteArray ans{ 35,Qt::Uninitialized };

    constexpr const static char toHex0[]={
        '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
    };

    constexpr const static char toHex1[]={
        '8','9','A','B','C','D','E','F','8','9','A','B','C','D','E','F',
    };

    class Array {
        char data[35];
    public:
        Array():data{
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15], '-',toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            '-','4',toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15], '-',
            toHex1[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15],'-',toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15],toHex0[std::rand()&15],
            toHex0[std::rand()&15],toHex0[std::rand()&15]
        } {
        }
    };

    ::new(ans.data()) Array;

    return std::move(ans);
}

}/*namespace baidu*/


