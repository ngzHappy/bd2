/*BaiDuUser cpp*/
#include "../BaiDuUser.hpp"
#include "../private/BaiDuUserData.hpp"
#include "../private/BaiDuUserPrivateFunction.hpp"
#include <text/gzip.hpp>
#include <QtGui>
#include <QtCore>
#include <QtScript>
#include <QtCrypto>
#include <QtNetwork>
#include <regex>
#include <ctime>
#include <string>
#include <thread>
#include <cstdlib>
#include <chrono>

namespace baidu {

namespace {

using string=std::basic_string<char,std::char_traits<char>,memory::Allocator<char>>;

inline Q_DECL_CONSTEXPR QLatin1Literal operator""_qsl(const char *arg,std::size_t n) {
    return QLatin1Literal(arg,int(n));
}

inline QByteArray operator""_qb(const char *arg,std::size_t n) {
    return QByteArray(arg,int(n));
}

namespace __private {
namespace __baidu {

class Static_init_on_qcoreapplication_create {
    QCA::Initializer _qca_init;

    class Image final:public QImage{
    public:
        using QImage::QImage;
    private:
        CPLUSPLUS_CLASS_META
    };

public:
    Static_init_on_qcoreapplication_create(){
        std::srand(int(std::time(nullptr)));
        /*异步加载QImage插件,因为加载QImage插件非常耗费时间*/
        std::thread([]() {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(50ms);
            auto * _tmp_=new Image(QString(
                "____________________________.png"_qsl));
            delete _tmp_;
        }).detach();
    }
    ~Static_init_on_qcoreapplication_create() {}
};
static char _psd_[sizeof(Static_init_on_qcoreapplication_create)];
static void init_on_qcoreapplication_create() {
    static memory::StaticPoionter<Static_init_on_qcoreapplication_create>
        _(_psd_);
}

Q_COREAPP_STARTUP_FUNCTION(init_on_qcoreapplication_create)

}/*__baidu*/
}/*__private*/
}/*namespace*/
}/*namespace baidu*/

namespace baidu {

namespace {

template<typename _T_>
class StringRef;

template<typename T,std::size_t N>
class StringRef<T[N]> {
    const T(&_m_Data)[N];
public:
    constexpr StringRef(const T(&argData)[N]):_m_Data(argData) {}
    constexpr const char * data() const { return _m_Data; }
    constexpr int size() const { return int(N-1); }
};

template<>
class StringRef<QByteArray> {
    const QByteArray & _m_Data;
public:
    constexpr StringRef(const QByteArray&arg):_m_Data(arg) {}
    const char *data() const { return _m_Data.data(); }
    int size() const { return _m_Data.size(); }
};

template<>
class StringRef<string> {
    const string & _m_Data;
public:
    constexpr StringRef(const string&arg):_m_Data(arg) {}
    const char *data() const { return _m_Data.data(); }
    int size() const { return _m_Data.size(); }
};

template<typename _T_>
constexpr auto make_string_ref(const _T_&arg) {
    return StringRef<_T_>(arg);
}

template<std::size_t N>
constexpr auto make_string_ref(const char(&arg)[N]) {
    return StringRef<char[N]>(arg);
}

/******************************************************************/
namespace utility_cpp14 {/*此函数最好在c++17重写*/
#include "BaiDuUserCatToUrl.hpp"
}/*namespace utility_cpp14*/
/******************************************************************/

/* &a=b */
template<typename ..._T_>
string cat_to_url(const _T_&...arg) {
    return utility_cpp14::__cat_to_url(make_string_ref(arg)...);
}

}/*namespace*/

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
    public QObject,
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
        s_getbaidu_cookie,
        s_getlogin_cookie,
        s_get_baidu_token,
        s_get_RSAKey,
        s_encryptRSA,
        s_postLogin,
        s_finished
    };

    static QString step_to_string(LogInSteps arg) {
        switch (arg) {
            case s_error:return "error"_qsl; break;
            case s_getbaidu_cookie:return"get baidu cookie"_qsl; break;
            case s_getlogin_cookie:return"get login cookie"_qsl; break;
            case s_get_baidu_token:return "getBaiduToken"_qsl; break;
            case s_get_RSAKey:return "getRSAKey"_qsl; break;
            case s_encryptRSA:return "encryptRSA"_qsl; break;
            case s_postLogin:return "postLogin"_qsl; break;
            case s_finished:return "finished"_qsl; break;
            default:break;
        }
        return "unknow step"_qsl;
    }

    void do_next_step() {
        switch (loginStepNext) {
            case s_error:login_error(); break;
            case s_getbaidu_cookie:getBaiDuCookie(); break;
            case s_getlogin_cookie:getLoginCookie(); break;
            case s_get_baidu_token:getBaiduToken(); break;
            case s_get_RSAKey:getRSAKey(); break;
            case s_encryptRSA:encryptRSA(); break;
            case s_postLogin:postLogin(); break;
            case s_finished:login_finished(); break;
        }
    }

    /*栈状态*/
    LogInSteps loginStep=s_getbaidu_cookie;
    LogInSteps loginStepNext=s_getbaidu_cookie;
    QString errorString{ "unknow error"_qsl };
    bool logInFinishedCalled=false;
    QByteArray baiduTooken;
    QByteArray rasKey/*key id*/;
    QByteArray publicKey/*rsa public key*/;
    QByteArray passWord/*加密后的密码*/;

    class StaticData_postLogin final {
    public:
    };
    static char _psd_postLogin[sizeof(StaticData_postLogin)];
    void postLogin() {
        static memory::StaticPoionter<StaticData_postLogin>
            varPsd{_psd_postLogin};

        loginStep=s_postLogin;
        loginStepNext=s_error;

        auto varBaiDuUser=baiDuUser.lock();
        if (false==varBaiDuUser) { return; }

        do {

        } while (false);

        this->next_step();

    }

    void encryptRSA() {

        loginStep=s_encryptRSA;
        loginStepNext=s_postLogin;

        auto varBaiDuUser=baiDuUser.lock();
        if (false==varBaiDuUser) { return; }

        const QByteArray & varPublicKey=this->publicKey;
        const QByteArray varPassWord=varBaiDuUser->getPassword().toUtf8();
        QByteArray & varAns=this->passWord;

        do {
            try {

                if (varPassWord.isEmpty()||varPublicKey.isEmpty()) {
                    loginStepNext=s_error;
                    break;
                }

                QCA::ConvertResult varIsPublicKeyOk;

                QCA::PublicKey pubkey_=
                    QCA::RSAPublicKey::fromPEM(varPublicKey,&varIsPublicKeyOk);

                if ((!(QCA::ConvertGood==varIsPublicKeyOk))
                    ||(pubkey_.canEncrypt()==false)) {
                    loginStepNext=s_error;
                    break;
                }

                /* reset password */
                QCA::SecureArray result_=pubkey_.encrypt(
                    varPassWord,QCA::EME_PKCS1v15_SSL);

                {/*deep copy data*/
                    QByteArray result(result_.constData(),result_.size());
                    result=result.toBase64();
                    varAns=result.toPercentEncoding();
                }

            }
            catch (...) {
                loginStepNext=s_error;
            }
        } while (false);

        this->next_step();

    }

    class StaticData_getRSAKey final{
    public:
        const QByteArray url;
        const QByteArray keyUserAgent;
        const QByteArray keyAcceptEncoding;
        const QByteArray valueAcceptEncoding;
        const QString zero;
        StaticData_getRSAKey()
            :url("https://passport.baidu.com/v2/getpublickey?token="_qb)
            ,keyUserAgent("User-Agent"_qb)
            ,keyAcceptEncoding("Accept-Encoding"_qb)
            ,valueAcceptEncoding("gzip, deflate"_qb)
            ,zero("0"_qb) {
        }
    };
    static char _psd_getRSAKey[sizeof(StaticData_getRSAKey)];
    void getRSAKey() {
        loginStep=s_get_RSAKey;
        static memory::StaticPoionter<StaticData_getRSAKey> varPSD(_psd_getRSAKey);

        auto varBaiDuUser=baiDuUser.lock();
        if (false==varBaiDuUser) { return; }

        zone_this_data(varBaiDuUser.get());

        QUrl varURL;
        {
            const auto && gid=varBaiDuUser->gid();
            const auto && tt=BaiDuUser::currentTime();

            auto urlData=cat_to_url(
                "tpl","mn",
                "apiver","v3",
                "tt",tt,
                "class","login",
                "gid",gid,
                "callback","bd__cbs__dmwxux");

            QByteArray varTmpUrl;
            varTmpUrl.reserve(4
                +varPSD->url.size()
                +this->baiduTooken.size()
                +static_cast<int>(urlData.size()));
            varTmpUrl.append(varPSD->url);
            varTmpUrl.append(this->baiduTooken);
            varTmpUrl.append(urlData.c_str(),static_cast<int>(urlData.size()));
            varURL.setUrl(varTmpUrl);
        }

        QNetworkRequest req(varURL);
        req.setRawHeader(varPSD->keyUserAgent,varBaiDuUser->userAgent());
        req.setRawHeader(varPSD->keyAcceptEncoding,varPSD->valueAcceptEncoding);

        auto varReply=varThisData->_m_NetworkAccessManager.get(req);

        varReply->connect(varReply,&QNetworkReply::finished,
            [varLockThis=this->shared_from_this(),varReply,this]() {
            this->loginStepNext=s_encryptRSA;
            do {
                varReply->deleteLater();

                auto varBaiDuUser=baiDuUser.lock();
                if (false==varBaiDuUser) { return; }

                {
                    QString varPublicKey;
                    auto json=varReply->readAll();
                    varReply->close();

                    if (json.isEmpty()) {
                        this->loginStepNext=s_error;
                        errorString="can not get json"_qsl;
                        break;
                    }

                    if (json[0]==char(0x001F)) {
                        json=text::ungzip(json.cbegin(),json.cend());
                    }

                    /*去除括号*/
                    json=json.mid(json.indexOf("(")+1);
                    json.resize(json.size()-1);

                    QScriptEngine eng;
                    eng.evaluate("var bd__cbs__dmwxux = "_qsl+json);
                    const auto error=eng.evaluate(u8R"(bd__cbs__dmwxux["errno"])"_qsl).toString();
                    varPublicKey=eng.evaluate(u8R"(bd__cbs__dmwxux["pubkey"])"_qsl).toString();
                    const auto key=eng.evaluate(u8R"(bd__cbs__dmwxux["key"])"_qsl).toString();

                    if ((varPSD->zero!=error)||varPublicKey.isEmpty()||key.isEmpty()) {
                        this->loginStepNext=s_error;
                        errorString="can not get json  "_qsl+std::move(error);
                        break;
                    }

                    this->rasKey=key.toUtf8();
                    this->publicKey=varPublicKey.toUtf8();

                }

            } while (false);

            this->next_step();

        });

    }

    class StaticData_getBaiduToken {
    public:
        const QByteArray url;
        const QByteArray userAgent;
        const QString zero;
        const std::regex tokenCheck;
        StaticData_getBaiduToken()
            :url(u8R"(https://passport.baidu.com/v2/api/?getapi)"_qb)
            ,userAgent("User-Agent"_qb)
            ,zero("0"_qsl)
            ,tokenCheck(u8R"([0-9a-zA-Z]+)") {
        }
    };
    static char _psd_getBaiduToken[sizeof(StaticData_getBaiduToken)];
    void getBaiduToken() {

        loginStep=s_get_baidu_token;

        /*静态数据*/
        static memory::StaticPoionter<StaticData_getBaiduToken>
            _psd_(_psd_getBaiduToken);

        auto varBaiDuUser=baiDuUser.lock();
        if (false==varBaiDuUser) { return; }

        zone_this_data(varBaiDuUser.get());

        QUrl varUrl;
        {/*set url*/
            const auto && tt=BaiDuUser::currentTime();
            const auto && gid=varBaiDuUser->gid();
            const auto url_=cat_to_url(
                "tpl","mn",
                "apiver","v3",
                "tt",tt,
                "class","login",
                "gid",gid,
                "logintype","dialogLogin",
                "callback","bd__cbs__akwyzc"
            );
            QByteArray varTmpUrl;
            varTmpUrl.reserve(4
                +_psd_->url.size()
                +static_cast<int>(url_.size()));
            varTmpUrl.append(_psd_->url);
            varTmpUrl.append(url_.c_str(),static_cast<int>(url_.size()));
            varUrl.setUrl(varTmpUrl);
        }

        QNetworkRequest varRequest(varUrl);
        varRequest.setRawHeader(_psd_->userAgent,BaiDuUser::userAgent());
        varRequest.setHeader(QNetworkRequest::CookieHeader,
           QVariant::fromValue<QList<QNetworkCookie>>(varThisData->_m_NetworkCookieJar->allCookies()));

        auto varReply=varThisData->_m_NetworkAccessManager.get(varRequest);
        varReply->connect(varReply,&QNetworkReply::finished,
            [varLockThis=this->shared_from_this(),varReply,this]() {

                {
                    varReply->deleteLater();

                    auto varBaiDuUser=baiDuUser.lock();
                    if (false==varBaiDuUser) { return; }

                    auto json=varReply->readAll();
                    varReply->close();

                    /*remove ()*/
                    json=json.mid(json.indexOf("("_qsl)+1);
                    json.resize(json.size()-1);

                    /*读取error 和 token*/
                    QScriptEngine eng;
                    eng.evaluate("var bd__cbs__89tioq = "_qsl+json);
                    auto error=eng.evaluate(u8R"(bd__cbs__89tioq["errInfo"]["no"])"_qsl).toString();
                    auto token=eng.evaluate(u8R"(bd__cbs__89tioq["data"]["token"])"_qsl).toString();

                    if (error==_psd_->zero) {
                        loginStepNext=s_get_RSAKey;
                        this->baiduTooken=token.toUtf8();
                        /*进一步检查token是否正确*/
                        if (false==std::regex_match(this->baiduTooken.cbegin(),
                            this->baiduTooken.cend(),
                            _psd_->tokenCheck)) {
                            goto label_error;
                        }
                    }
                    else {
                    label_error:
                        loginStepNext=s_error;
                        errorString="can not find baidu token : "_qsl+token;
                    }

                }

                this->next_step();

        });
    }

    class NextStepEvent final:public QEvent{
        std::shared_ptr<Login> _m_Login;
    public:
        NextStepEvent(std::shared_ptr<Login>&&arg) :
            QEvent(QEvent::MaxUser),
            _m_Login(std::move(arg)){}
        void next() { _m_Login->do_next_step(); }
    private:
        CPLUSPLUS_CLASS_META
    };

    bool event(QEvent *e)override {
        {
            auto var=dynamic_cast<NextStepEvent*>(e);
            if (var) { var->next(); return true; }
        }
        return false;
    }

    void next_step() {
        QCoreApplication::postEvent(this,
            new NextStepEvent{this->shared_from_this()});
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

    class StaticData_getLoginCookie {
    public:
        QUrl baidu_url;
        QByteArray key_user_agent;
        StaticData_getLoginCookie():
            baidu_url(QString("https://www.baidu.com/cache/user/html/login-1.2.html")),
            key_user_agent("User-Agent"_qb) {
        }
    };
    static char _psd_getLoginCookie[sizeof(StaticData_getLoginCookie)];
    void getLoginCookie() {
        static memory::StaticPoionter<StaticData_getLoginCookie> varStaticData{
            _psd_getLoginCookie };

        loginStep=s_getlogin_cookie;

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

    class StaticData_getBaiDuCookie {
    public:
        QUrl baidu_url;
        QByteArray key_user_agent;
        StaticData_getBaiDuCookie():
            baidu_url(QString("http://www.baidu.com"_qsl)),
            key_user_agent("User-Agent"_qb) {
        }
    };
    static char _psd_getBaiDuCookie[sizeof(StaticData_getBaiDuCookie)];
    void getBaiDuCookie() {
        static memory::StaticPoionter<StaticData_getBaiDuCookie> varStaticData{
            _psd_getBaiDuCookie };

        loginStep=s_getbaidu_cookie;

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
                        loginStepNext=s_getlogin_cookie;
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
    CPLUSPLUS_CLASS_META
};

char Login::_psd_getBaiDuCookie[sizeof(StaticData_getBaiDuCookie)];
char Login::_psd_getBaiduToken[sizeof(StaticData_getBaiduToken)];
char Login::_psd_getRSAKey[sizeof(StaticData_getRSAKey)];
char Login::_psd_getLoginCookie[sizeof(StaticData_getLoginCookie)];
char Login::_psd_postLogin[sizeof(StaticData_postLogin)];
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

QString BaiDuUser::getLocalCacheFilePath()const {
    zone_const_this_data(this);
    return varThisData->_m_BaiDuUserCache.fileName();
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
            "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:49.0) Gecko/20100101 Firefox/49.0"_qb
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

#undef zone_this_data

