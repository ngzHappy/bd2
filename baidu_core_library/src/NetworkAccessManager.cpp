#include "../NetworkAccessManager.hpp"
#include <QtCore/qtimer.h>
#include <QtCore/qeventloop.h>
#include <QtCore/QCoreApplication>
#include <QtNetwork/qnetworkreply.h>

namespace baidu {


NetworkAccessManager::NetworkAccessManager(QObject *p)
    :QNetworkAccessManager(p) {

}

NetworkAccessManager::~NetworkAccessManager() {
    _p_wait_for_all_reply_deleted();
}

QNetworkReply *NetworkAccessManager::createRequest(Operation a,const QNetworkRequest & b,QIODevice *c) {
    auto varAns=QNetworkAccessManager::createRequest(a,b,c);
    if (varAns) {
        ++_m_ReplyCount;
        connect(varAns,&QObject::destroyed,this,[this]() {--_m_ReplyCount; });
    }
    return varAns;
}

bool NetworkAccessManager::_is_wait_finished()const {
    return (qApp==nullptr)
        ||(QCoreApplication::closingDown()==true)
        ||(_m_ReplyCount.load()<1);
}

void NetworkAccessManager::_p_wait_for_all_reply_deleted() {

    if (_is_wait_finished()) { return; }
    else {
        QEventLoop varLoop;
        QTimer varTimer;
        varTimer.connect(&varTimer,&QTimer::timeout,this,[this,&varLoop]() {
            if (_is_wait_finished()) { varLoop.quit(); }
            else { return; }
        });
        varTimer.start(1);
        varLoop.exec();
    }

}

}/*baidu*/
