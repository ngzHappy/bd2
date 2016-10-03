#include <QtNetwork>
#include <QtCore>
#include "NetworkAccessManager.hpp"
#include "TestNetWork.hpp"

class Cookies :public QNetworkCookieJar{
public:

    using QNetworkCookieJar::allCookies;

    virtual QList<QNetworkCookie> cookiesForUrl(
            const QUrl &url) const override{
        return QNetworkCookieJar::cookiesForUrl(url);
    }

    virtual bool setCookiesFromUrl(
            const QList<QNetworkCookie> &cookieList,
            const QUrl &url) override{
        return QNetworkCookieJar::setCookiesFromUrl(cookieList,url);
    }

    virtual bool insertCookie(const QNetworkCookie &cookie) override{
        return QNetworkCookieJar::insertCookie(cookie);
    }

    virtual bool updateCookie(const QNetworkCookie &cookie) override{
        return QNetworkCookieJar::updateCookie(cookie);
    }

    virtual bool deleteCookie(const QNetworkCookie &cookie) override{
        return QNetworkCookieJar::deleteCookie(cookie);
    }

    bool validateCookie(
            const QNetworkCookie &cookie,const QUrl &url) const {
        return QNetworkCookieJar::validateCookie(cookie,url);
    }

};

TestNetWork::TestNetWork()
{
    for(int i=0;i<10;++i){

        auto cookes=new Cookies;
        NetworkAccessManager manager;
        cookes->setParent(&manager);
        manager.setCookieJar(cookes);

        QUrl url(QString::fromUtf8(
                     u8R"(http://tieba.baidu.com/f?kw=%C0%FA%CA%B7&fr=ala0&tpl=5)"));
        QNetworkRequest req(url);

        auto replay=manager.get(req);

        replay->connect(replay,&QNetworkReply::finished,
                        [replay,cookes]() {

            replay->deleteLater();
            //qDebug()<<replay->readAll();

            qDebug()<<
                       replay->header(QNetworkRequest::SetCookieHeader);

            QByteArray data_=replay->readAll();

            qDebug()<<"cookies size:"<<
                      cookes->allCookies() ;

        });

    }

}

















