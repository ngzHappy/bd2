/*BaiDuUser cpp*/
#include "../BaiDuUser.hpp"
#include "../private/BaiDuUserData.hpp"
#include "../private/BaiDuUserPrivateFunction.hpp"
#include <text/gzip.hpp>
#include <gumbo/gumbo.hpp>
#include <QtGui>
#include <QtCore>
#include <QtScript>
#include <QtCrypto>
#include <QtNetwork>
#include <regex>
#include <ctime>
#include <map>
#include <string>
#include <thread>
#include <cstdlib>
#include <chrono>
#ifndef NDEBUG
#include <fstream>
/*debug*/
#include <cassert>
#ifndef _debug_info_
#define _debug_info_ /**/,__LINE__,__FILE__,__func__/**/
#endif

#else
#ifndef _debug_info_
#define _debug_info_
#endif
#endif

namespace baidu {

namespace {

using string=std::basic_string<char,std::char_traits<char>,memory::Allocator<char>>;

inline Q_DECL_CONSTEXPR QLatin1Literal operator""_qsl(const char *arg,std::size_t n) {
    return QLatin1Literal(arg,int(n));
}

inline auto operator""_qutf8(const char *arg,std::size_t n) {
    return QString::fromUtf8(arg,n);
}

inline QByteArray operator""_qb(const char *arg,std::size_t n) {
    return QByteArray(arg,int(n));
}

namespace __private {
namespace __baidu {

class Static_init_on_qcoreapplication_create {
    QCA::Initializer _qca_init;

    class Image final :public QImage {
    public:
        using QImage::QImage;
    private:
        CPLUSPLUS_CLASS_META
    };

public:
    Static_init_on_qcoreapplication_create() {
        std::srand(int(std::time(nullptr)));
        /*异步加载QImage插件,因为加载QImage插件非常耗费时间*/
        /*异步加载QScriptEngine,因为QScriptEngine第一次初始化非常耗时*/
        std::thread([]() {
            {/*wait a time*/
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(50ms);
            }
            {/*load qimage plugin*/
                auto * _tmp_=new Image(QString(
                    "____________________________.png"_qsl));
                delete _tmp_;
            }
            {/*load js engine*/
                QScriptEngine _0_eng;
            }
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
    varThisData->_m_LoginWithVertifyCode.reset();
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
    public BaiDuUser::LoginWithVertifyCode,
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
        s_getbaidu_cookie/*2*/,
        s_getlogin_cookie/*2*/,
        s_get_baidu_token/*2*/,
        s_get_RSAKey/*2*/,
        s_encryptRSA/*1*/,
        s_postLogin/*2*/,
        s_getbaidu_tieba_cookie/*2 http://tieba.baidu.com/ */,
        s_getbaidu_image_cookie/*2 http://image.baidu.com/ */,
        s_finished/**/,
        s_state_unknow,
        s_state_wait,
    };

#ifndef NDEBUG
    class StateLock {
        StateLock(const StateLock&)=delete;
        StateLock(StateLock&&)=delete;
        StateLock&operator=(const StateLock&)=delete;
        StateLock&operator=(StateLock&&)=delete;
        Login * _m_Login;
        int _m_Line;
        const char* _m_File;
        const char* _m_FunctionName;
    public:
        StateLock(Login*l,int a,const char*b,const char*c)
            :_m_Login(l)
            ,_m_Line(a)
            ,_m_File(b)
            ,_m_FunctionName(c) {
            l->loginStepNext=s_state_unknow;
        }
        ~StateLock() {
            if (_m_Login->baiDuUser.lock()==false) { return; }
            if (_m_Login->loginStepNext==s_state_unknow) {
                qDebug()<<_m_File<<_m_Line<<_m_FunctionName<<endl;
                assert(false);
            }
        }
    };
#endif

    static QString step_to_string(LogInSteps arg) {
        switch (arg) {
            case s_error:return "error"_qsl; break;
            case s_getbaidu_cookie:return"get baidu cookie"_qsl; break;
            case s_getlogin_cookie:return"get login cookie"_qsl; break;
            case s_get_baidu_token:return "getBaiduToken"_qsl; break;
            case s_get_RSAKey:return "getRSAKey"_qsl; break;
            case s_encryptRSA:return "encryptRSA"_qsl; break;
            case s_postLogin:return "postLogin"_qsl; break;
            case s_getbaidu_tieba_cookie:return "getbaidu_tieba_cookie"_qsl; break;
            case s_getbaidu_image_cookie:return "getbaidu_image_cookie"_qsl; break;
            case s_finished:return "finished"_qsl; break;
            default:break;
        }
        return "unknow step"_qsl;
    }

    void do_next_step() {
        switch (loginStepNext) {
            case s_error:return login_error(); break;
            case s_getbaidu_cookie:return getBaiDuCookie(); break;
            case s_getlogin_cookie:return getLoginCookie(); break;
            case s_get_baidu_token:return getBaiduToken(); break;
            case s_get_RSAKey:return getRSAKey(); break;
            case s_encryptRSA:return encryptRSA(); break;
            case s_postLogin:return postLogin(); break;
            case s_getbaidu_tieba_cookie:return getBaiDuTieBaCookie(); break;
            case s_getbaidu_image_cookie:return getBaiDuImageCookie(); break;
            case s_finished:return login_finished(); break;
        }
        return login_error();
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
    QByteArray _m_codestring/*验证码ID*/;
    QByteArray _m_vertifycode/*验证码内容*/;

    virtual QByteArray getVertifyCodeUrl()const override {
        return _m_vertifycode;
    }

    virtual void loginVertifyCode(const QString&arg) override {
        this->loginStepNext=s_getbaidu_cookie;
        _m_vertifycode=arg
            .toUtf8()
            .toPercentEncoding();
        next_step();
    }

    class StaticData_postLogin final {
    public:
        const QUrl url;
        const std::regex error_no_regex{ u8R"r(err_no=([0-9]+))r" };
        const std::regex code_string_regex{ u8R"r(codeString=([^&]+))r" };
        const QByteArray code_string_url{ "https://passport.baidu.com/cgi-bin/genimage?"_qb };
        const QByteArray key_Accept{ "Accept"_qb };
        const QByteArray value_Accept{ "text/html, application/xhtml+xml, */*"_qb };
        const QByteArray key_Referer{ "Referer"_qb };
        const QByteArray value_Referer{ "https://www.baidu.com/"_qb };
        const QByteArray key_Accept_Language{ "Accept-Language"_qb };
        const QByteArray value_Accept_Language{ "zh-CN"_qb };
        const QByteArray key_User_Agent{ "User-Agent"_qb };
        const QByteArray key_Content_Type{ "Content-Type"_qb };
        const QByteArray value_Content_Type{ "application/x-www-form-urlencoded"_qb };
        const QByteArray key_Accept_Encoding{ "Accept-Encoding"_qb };
        const QByteArray value_Accept_Encoding{ "gzip, deflate"_qb };
        const std::map<int,QString,std::less<>,memory::Allocator<int>> error_code=[]() {
            std::map<int,QString,std::less<>,memory::Allocator<int>> ans{
                { -1	    ,u8"系统错误,请您稍后再试"_qutf8 },
                { 1	        ,u8"您输入的帐号格式不正确"_qutf8 },
                { 2	        ,u8"您输入的帐号不存在"_qutf8 },
                { 3	        ,u8"验证码不存在或已过期,请重新输入"_qutf8 },
                { 4	        ,u8"您输入的帐号或密码有误"_qutf8 },
                { 5	        ,u8"请在弹出的窗口操作,或重新登录"_qutf8 },
                { 6	        ,u8"您输入的验证码有误"_qutf8 },
                { 7	        ,u8"密码错误"_qutf8 },
                { 16	    ,u8"您的帐号因安全问题已被限制登录"_qutf8 },
                { 257	    ,u8"请输入验证码"_qutf8 },
                { 100027	,u8"百度正在进行系统升级，暂时不能提供服务，敬请谅解"_qutf8 },
                { 400031	,u8"请在弹出的窗口操作,或重新登录"_qutf8 },
                { 401007	,u8"您的手机号关联了其他帐号，请选择登录"_qutf8 },
                { 120021	,u8"登录失败,请在弹出的窗口操作,或重新登录"_qutf8 },
                { 500010	,u8"登录过于频繁,请24小时后再试"_qutf8 },
                { 200010	,u8"验证码不存在或已过期"_qutf8 },
                { 100005	,u8"系统错误,请您稍后再试"_qutf8 },
                { 120019	,u8"请在弹出的窗口操作,或重新登录"_qutf8 },
                { 110024	,u8"此帐号暂未激活"_qutf8 },
                { 100023	,u8"开启Cookie之后才能登录"_qutf8 },
                { 17	    ,u8"您的帐号已锁定"_qutf8 },
                { 500002    ,u8"您输入的验证码有误"_qutf8},
                { 500018    ,u8"验证码已失效，请重试"_qutf8},
            };
            return ans;
        }();
    public:
        StaticData_postLogin()
            :url("https://passport.baidu.com/v2/api/?login"_qsl) {}
    };
    static char _psd_postLogin[sizeof(StaticData_postLogin)];
    class PostLoginJSParserAns {
    public:
        bool isOk=false;
        int errorCode=0;
        QString errorString;
        QByteArray VertifyCodeID;
        QByteArray VertifyCodeUrl;
    };
    static void parserPostLoginJS(
        const gumbo::string&varJS,
        const StaticData_postLogin*varPSD,
        PostLoginJSParserAns*varAns
    ) {
        int varErrorNO=0;
        do {
            std::cmatch error_no;
            if (std::regex_search(
                varJS.c_str(),varJS.c_str()+varJS.size(),
                error_no,varPSD->error_no_regex)) {
                varErrorNO=std::atoi(error_no[1].first);
                varAns->errorCode=varErrorNO;
                if (varErrorNO!=0) {

                    if (varErrorNO==257) {
                        /*https://passport.baidu.com/cgi-bin/genimage?*/
                        /*codeString=([^&]+)*/
                        std::cmatch code_string;
                        if (std::regex_search(varJS.c_str(),varJS.c_str()+varJS.size(),
                            code_string,varPSD->code_string_regex)) {
                            varAns->VertifyCodeID=QByteArray(code_string[1].first,
                                static_cast<int>(code_string[1].length()));
                            varAns->VertifyCodeUrl=varPSD->code_string_url
                                +varAns->VertifyCodeID;
                            varAns->errorString=u8"请输入验证码"_qutf8;
                            return;
                        }
                    }

                    if (varErrorNO==18) {
                        varAns->isOk=true/*要求手机验证码*/;
                        break;
                    }

                    auto it=varPSD->error_code.find(varErrorNO);
                    if (it==varPSD->error_code.end()) {

                    }
                    else {
                        varAns->errorString=it->second;
                        return;
                    }

                }
                else {
                    varAns->isOk=true;
                }
            }
            else {
                varAns->errorString="can not find err_no="_qsl;
                return;
            }
        } while (false);

    }
    void postLogin() try {
#ifndef NDEBUG
        StateLock _lock_{ this _debug_info_ };
#endif
        const static constexpr char staticPage[]={ "https%3A%2F%2Fwww.baidu.com%2Fcache%2Fuser%2Fhtml%2Fv3Jump.html" };
        const static constexpr char u[]={ "https%3A%2F%2Fwww.baidu.com%2F" };
        const static constexpr char splogin[]={ "rate" };
        const static constexpr char logLoginType[]={ "pc_loginDialog" };
        const static constexpr char safeflg[]={ "0" };
        const static constexpr char detect[]={ "1" };
        const static constexpr char quick_user[]={ "0" };
        const static constexpr char memberPass[]={ "on" };
        const static constexpr char loginType[]={ "dialogLogin" };
        const static constexpr char loginmerge[]={ "true" };

        static memory::StaticPoionter<StaticData_postLogin>
            varPsd{ _psd_postLogin };

        loginStep=s_postLogin;

        auto varBaiDuUser=baiDuUser.lock();
        if (false==varBaiDuUser) { return; }

        do {
            QByteArray varPostData;
            {
                /*当前时间戳*/
                const auto tt=BaiDuUser::currentTime();
                /*用户名*/
                const QByteArray varUserName=varBaiDuUser
                    ->getUsername()
                    .toUtf8()
                    .toPercentEncoding();
                /*一个随机数*/
                const auto ppui_logintime=
                    QByteArray::number(9900+(std::rand()&511));
                /*构建临时对象缓存数据*/
                const auto varTmpPostData=cat_to_url(
                    "staticpage",staticPage,
                    "charset","utf-8",
                    "token",this->baiduTooken,
                    "tpl","mn",
                    "subpro","",
                    "apiver","v3",
                    "tt",tt,
                    "codestring",this->_m_codestring/*验证码id*/,
                    "safeflg",safeflg,
                    "u",u,
                    "isPhone","false",
                    "detect",detect,
                    "gid",varBaiDuUser->gid(),
                    "quick_user",quick_user,
                    "logintype",loginType,
                    "logLoginType",logLoginType,
                    "idc","",
                    "loginmerge",loginmerge,
                    "splogin",splogin,
                    "username",varUserName,
                    "password",this->passWord,
                    "verifycode",this->_m_vertifycode/*验证码*/,
                    "mem_pass",memberPass,
                    "rsakey",this->rasKey,
                    "crypttype","12",
                    "ppui_logintime",ppui_logintime,
                    "countrycode","",
                    "callback","parent.bd__pcbs__s09032"
                );

                auto varPostSize=static_cast<int>(varTmpPostData.size())-1;
                varPostData.reserve(varPostSize+4);
                /*去掉第一个&*/
                varPostData.append(varTmpPostData.data()+1,
                    varPostSize);
            }

            QNetworkRequest req(varPsd->url);
            req.setRawHeader(varPsd->key_Accept,varPsd->value_Accept);
            req.setRawHeader(varPsd->key_Referer,varPsd->value_Referer);
            req.setRawHeader(varPsd->key_Accept_Language,varPsd->value_Accept_Language);
            req.setRawHeader(varPsd->key_User_Agent,BaiDuUser::userAgent());
            req.setRawHeader(varPsd->key_Content_Type,varPsd->value_Content_Type);
            req.setRawHeader(varPsd->key_Accept_Encoding,varPsd->value_Accept_Encoding);

            zone_this_data(varBaiDuUser.get());
            auto manager=&(varThisData->_m_NetworkAccessManager);

            /*post data*/
            auto replyNext=manager->post(req,varPostData);

            replyNext->connect(replyNext,&QNetworkReply::finished,
                [varLockThis=this->shared_from_this(),
                varReply=replyNext,this]() {

                varReply->deleteLater();
#ifndef NDEBUG
                StateLock _lock_{ this _debug_info_ };
#endif

                try {
                    auto varBaiDuUser=baiDuUser.lock();
                    if (false==varBaiDuUser) { return; }

                    /*清除验证码*/
                    this->_m_vertifycode.clear();

                    do {

                        {
                            auto varReplyData=varReply->readAll();

                            if (varReplyData.isEmpty()) {
                                loginStepNext=s_error;
                                break;
                            }

                            if (varReplyData[0]==char(0x001F)) {
                                varReplyData=text::ungzip(varReplyData.cbegin(),varReplyData.cend());
                                if (varReplyData.isEmpty()) {
                                    errorString="unzip error"_qsl;
                                    loginStepNext=s_error;
                                    break;
                                }
                            }

                            auto varTmpJson=
                                gumbo::getAllJavaScript(varReplyData.cbegin(),varReplyData.cend());

                            if (varTmpJson.empty()) {
                                errorString="can not find js"_qsl;
                                this->loginStepNext=s_error;
                                break;
                            }

                            const auto &varJS=*varTmpJson.begin();
                            PostLoginJSParserAns varAns;
                            parserPostLoginJS(varJS,varPsd.pointer(),&varAns);

                            if (varAns.VertifyCodeUrl.isEmpty()==false) {
                                this->_m_vertifycode=std::move(varAns.VertifyCodeUrl);
                                this->_m_codestring=std::move(varAns.VertifyCodeID);
                                this->loginStepNext=s_error;
                                errorString=std::move(varAns.errorString);
                                break;
                            }
                            else {
                                if (varAns.isOk==false) {
                                    this->loginStepNext=s_error;
                                    errorString=std::move(varAns.errorString);
                                    break;
                                }
                            }

                            {/*登录成功*/
                                this->loginStepNext=s_getbaidu_tieba_cookie;
                            }

                        }

                    } while (false);

                }
                catch (...) {
                    this->loginStepNext=s_error;
                }

                this->next_step();

            });

            this->loginStepNext=s_state_wait;
        } while (false);

    }
    catch (...) {
        login_error();
    }

    void encryptRSA() try {
#ifndef NDEBUG
        StateLock _lock_{ this _debug_info_ };
#endif
        loginStep=s_encryptRSA;

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
                    loginStepNext=s_postLogin;
                }

            }
            catch (...) {
                loginStepNext=s_error;
            }
        } while (false);

        this->next_step();
    }
    catch (...) {
        login_error();
    }

    class StaticData_getRSAKey final {
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
    void getRSAKey() try {
#ifndef NDEBUG
        StateLock _lock_{ this _debug_info_ };
#endif
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
#ifndef NDEBUG
            StateLock _lock_{ this _debug_info_ };
#endif
            try {
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
                        this->loginStepNext=s_encryptRSA;
                    }

                } while (false);
            }
            catch (...) {
                loginStepNext=s_error;
            }

            this->next_step();

        });
        this->loginStepNext=s_state_wait;
    }
    catch (...) {
        login_error();
    }

    class StaticData_getBaiduToken final {
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
    void getBaiduToken() try {
#ifndef NDEBUG
        StateLock _lock_{ this _debug_info_ };
#endif
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
#ifndef NDEBUG
            StateLock _lock_{ this _debug_info_ };
#endif
            try {
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
            catch (...) {
                loginStepNext=s_error;
            }

            this->next_step();

        });

        this->loginStepNext=s_state_wait;
    }
    catch (...) {
        login_error();
    }

    class NextStepEvent final :public QEvent {
        std::shared_ptr<Login> _m_Login;
    public:
        NextStepEvent(std::shared_ptr<Login>&&arg):
            QEvent(QEvent::MaxUser),
            _m_Login(std::move(arg)) {
        }
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
            new NextStepEvent{ this->shared_from_this() });
    }

    void next() override {
        next_step();
    }

    void login_error() {
        logInFinishedCalled=true;
        auto varBaiDuUser=baiDuUser.lock();
        if (false==varBaiDuUser) { return; }
        auto var_step_name=step_to_string(loginStep);
        zone_this_data(varBaiDuUser.get());
        varThisData->setIsLoging(false);
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
        zone_this_data(varBaiDuUser.get());
        varThisData->_m_IsLogin=true;
        varThisData->setIsLoging(false);
        varThisData->_m_LoginWithVertifyCode.reset();
        varBaiDuUser->loginFinished(true,{});
    }

    class StaticData_getLoginCookie final {
    public:
        QUrl baidu_url;
        QByteArray key_user_agent;
        StaticData_getLoginCookie():
            baidu_url(QString("https://www.baidu.com/cache/user/html/login-1.2.html")),
            key_user_agent("User-Agent"_qb) {
        }
    };
    static char _psd_getLoginCookie[sizeof(StaticData_getLoginCookie)];
    void getLoginCookie() try {
#ifndef NDEBUG
        StateLock _lock_{ this _debug_info_ };
#endif
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

#ifndef NDEBUG
            StateLock _lock_{ this _debug_info_ };
#endif

            try {
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
            catch (...) {
                loginStepNext=s_error;
            }

            next_step();

        });
        this->loginStepNext=s_state_wait;
    }
    catch (...) {
        login_error();
    }

    class StaticData_getBaiDuCookie final {
    public:
        QUrl baidu_url;
        QByteArray key_user_agent;
        StaticData_getBaiDuCookie():
            baidu_url(QString("http://www.baidu.com"_qsl)),
            key_user_agent("User-Agent"_qb) {
        }
    };
    static char _psd_getBaiDuCookie[sizeof(StaticData_getBaiDuCookie)];
    void getBaiDuCookie() try {
#ifndef NDEBUG
        StateLock _lock_{ this _debug_info_ };
#endif
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
#ifndef NDEBUG
            StateLock _lock_{ this _debug_info_ };
#endif

            try {
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
            catch (...) {
                loginStepNext=s_error;
            }

            next_step();

        });
        this->loginStepNext=s_state_wait;
    }
    catch (...) {
        login_error();
    }

    class StaticData_getBaiDuTieBaCookie final {
    public:
        QUrl baidu_url;
        QByteArray key_user_agent;
        StaticData_getBaiDuTieBaCookie():
            baidu_url(QString("http://tieba.baidu.com"_qsl)),
            key_user_agent("User-Agent"_qb) {
        }
    };
    static char _psd_getBaiDuTieBaCookie[sizeof(StaticData_getBaiDuTieBaCookie)];
    void getBaiDuTieBaCookie() try {
#ifndef NDEBUG
        StateLock _lock_{ this _debug_info_ };
#endif
        static memory::StaticPoionter<StaticData_getBaiDuTieBaCookie> varStaticData{
            _psd_getBaiDuTieBaCookie };

        loginStep=s_getbaidu_tieba_cookie;

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
#ifndef NDEBUG
            StateLock _lock_{ this _debug_info_ };
#endif

            try {
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
                    loginStepNext=s_getbaidu_image_cookie;
                }
            }
            catch (...) {
                loginStepNext=s_error;
            }

            next_step();

        });
        this->loginStepNext=s_state_wait;
    }
    catch (...) {
        login_error();
    }

    class StaticData_getBaiDuImageCookie final {
    public:
        QUrl baidu_url;
        QByteArray key_user_agent;
        StaticData_getBaiDuImageCookie():
            baidu_url(QString("http://image.baidu.com"_qsl)),
            key_user_agent("User-Agent"_qb) {
        }
    };
    static char _psd_getBaiDuImageCookie[sizeof(StaticData_getBaiDuImageCookie)];
    void getBaiDuImageCookie() try {
#ifndef NDEBUG
        StateLock _lock_{ this _debug_info_ };
#endif
        static memory::StaticPoionter<StaticData_getBaiDuImageCookie> varStaticData{
            _psd_getBaiDuImageCookie };

        loginStep=s_getbaidu_image_cookie;

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
#ifndef NDEBUG
            StateLock _lock_{ this _debug_info_ };
#endif

            try {
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
                    loginStepNext=s_finished;
                }
            }
            catch (...) {
                loginStepNext=s_error;
            }

            next_step();

        });
        this->loginStepNext=s_state_wait;
    }
    catch (...) {
        login_error();
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
char Login::_psd_getBaiDuTieBaCookie[sizeof(StaticData_getBaiDuTieBaCookie)];
char Login::_psd_getBaiDuImageCookie[sizeof(StaticData_getBaiDuImageCookie)];
}/*namespace*/
}/*namespace __login*/

void BaiDuUser::login() {
    zone_this_data(this);

    {/*if is logining*/
        std::unique_lock<std::shared_timed_mutex>
            _(varThisData->_m_mutex_is_loging);
        if (varThisData->_m_is_loging) { return; }
        varThisData->_m_is_loging=true;
        varThisData->_m_IsLogin=false;
    }

    {
        auto varLogin=memory::make_shared<__login::Login>();
        {/*init login data*/
            varLogin->baiDuUser=this->shared_from_this();
            varThisData->_m_GID=gid();
        }
        varThisData->_m_LoginWithVertifyCode=varLogin;
        varLogin->next_step();
    }

}

void BaiDuUser::login(const QString&arg) {
    zone_this_data(this);

    if (varThisData->_m_LoginWithVertifyCode) {

        {/*if is logining*/
            std::unique_lock<std::shared_timed_mutex>
                _(varThisData->_m_mutex_is_loging);
            if (varThisData->_m_is_loging) { return; }
            varThisData->_m_is_loging=true;
            varThisData->_m_IsLogin=false;
        }

        varThisData->_m_LoginWithVertifyCode->loginVertifyCode(arg);
    }
    else {
        login();
    }
}

bool BaiDuUser::isLogining()const {
    zone_const_this_data(this);
    return varThisData->isLoging();
}

QByteArray BaiDuUser::getVertifyCodeUrl()const {
    zone_const_this_data(this);
    if (varThisData->_m_LoginWithVertifyCode==false) { return{}; }
    return varThisData->_m_LoginWithVertifyCode->getVertifyCodeUrl();
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

