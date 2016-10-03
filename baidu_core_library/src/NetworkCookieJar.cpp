#include "../NetworkCookieJar.hpp"

/*
 * http://stackoverflow.com/questions/13971787/how-do-i-save-cookies-with-qt
*/
namespace baidu {


QList<QNetworkCookie> NetworkCookieJar::cookiesForUrl(const QUrl &url) const {
    std::unique_lock<std::recursive_mutex> varLock{this->_m_ReadWriteMutex};
    return _Super_::cookiesForUrl(url);
}

bool NetworkCookieJar::setCookiesFromUrl(const QList<QNetworkCookie> &cookieList, const QUrl &url) {
    std::unique_lock<std::recursive_mutex> varLock{this->_m_ReadWriteMutex};
    return _Super_::setCookiesFromUrl(cookieList,url);
}

bool NetworkCookieJar::insertCookie(const QNetworkCookie &cookie) {
    std::unique_lock<std::recursive_mutex> varLock{this->_m_ReadWriteMutex};
    return _Super_::insertCookie(cookie);
}

bool NetworkCookieJar::updateCookie(const QNetworkCookie &cookie) {
    std::unique_lock<std::recursive_mutex> varLock{this->_m_ReadWriteMutex};
    return _Super_::updateCookie(cookie);
}

bool NetworkCookieJar::deleteCookie(const QNetworkCookie &cookie) {
    std::unique_lock<std::recursive_mutex> varLock{this->_m_ReadWriteMutex};
    return _Super_::deleteCookie(cookie);
}

QByteArray NetworkCookieJar::toByteArray(){
    QList<QNetworkCookie> varAllcookies;
    {
        std::unique_lock<std::recursive_mutex> varLock{this->_m_ReadWriteMutex};
        varAllcookies=allCookies();
    }
    if(varAllcookies.isEmpty()==false){
        QByteArray varAns;
        varAns.reserve( 1024*4*30/*cookies must less than 120K*/ );
        const auto & _varAllCookies=varAllcookies;
        for(const auto & i:_varAllCookies){
            if(i.isSessionCookie()){continue;}
            varAns+=i.toRawForm();
            varAns+='\n';
        }
        return std::move(varAns);
    }
    return{};
}

void NetworkCookieJar::fromByteArray(const QByteArray&arg){
    if(arg.isEmpty()){
        std::unique_lock<std::recursive_mutex> varLock{this->_m_ReadWriteMutex};
        setAllCookies({});
    }else{
        auto varTmp=QNetworkCookie::parseCookies(arg);
        std::unique_lock<std::recursive_mutex> varLock{this->_m_ReadWriteMutex};
        setAllCookies(std::move(varTmp));
    }
}

NetworkCookieJar::NetworkCookieJar(QObject* obj):_Super_(obj){}

NetworkCookieJar::~NetworkCookieJar(){

}

}/*baidu*/
