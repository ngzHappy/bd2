#ifndef __NETWORKCOOKIEJAR__HPP_
#define __NETWORKCOOKIEJAR__HPP_

#include "BaiduCoreLibrary.hpp"
#include <mutex>
#include <QtNetwork/qnetworkcookie.h>
#include <QtNetwork/qnetworkcookiejar.h>
#include <QtCore/qbytearray.h>

namespace baidu {

class BAIDU_CORE_LIBRARYSHARED_EXPORT NetworkCookieJar :public QNetworkCookieJar {
    Q_OBJECT

private:
    using _Super_=QNetworkCookieJar;
    mutable std::recursive_mutex _m_ReadWriteMutex;
public:
    NetworkCookieJar(QObject* /**/=nullptr);
    ~NetworkCookieJar();
public:
    QByteArray toByteArray();
    void fromByteArray(const QByteArray&);
public:
    virtual QList<QNetworkCookie> cookiesForUrl(const QUrl &url) const override;
    virtual bool setCookiesFromUrl(const QList<QNetworkCookie> &cookieList, const QUrl &url) override;
    virtual bool insertCookie(const QNetworkCookie &cookie) override;
    virtual bool updateCookie(const QNetworkCookie &cookie) override;
    virtual bool deleteCookie(const QNetworkCookie &cookie) override;
private:
    MEMORY_CLASS_NEW_DELETE
};

}

#endif

