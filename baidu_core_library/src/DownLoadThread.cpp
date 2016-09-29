#include "../private/PrivateDownLoadThread.hpp"
#include "../RunInMainThread.hpp"
#include "../DownLoadThread.hpp"
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkrequest.h>
#include <QtNetwork/qnetworkreply.h>

namespace baidu {

DownLoadThread::DownLoadThread(QObject *arg):
    QObject(arg) ,_m_Data(new PrivateDownLoadThread){
}

DownLoadThread::~DownLoadThread() {
}

DownLoadThread::DownLoadThread(PrivateDownLoadThread*arg):_m_Data(arg) {
}

PrivateDownLoadThread::PrivateDownLoadThread() {
    _m_ThreadQuitMutex=memory::make_shared<std::shared_timed_mutex>();
    _m_Thread=new ThreadPrivateDownLoadThread;
    _m_Thread->_m_ThreadQuitMutex=this->_m_ThreadQuitMutex;

    /*删除线程*/
    connect(_m_Thread,&ThreadPrivateDownLoadThread::finished,
        _m_Thread,[_m_Thread=this->_m_Thread]() {
        baidu::runInMainThread([_m_Thread]() {delete _m_Thread; });
    },Qt::DirectConnection);

    this->moveToThread(_m_Thread);
}

void PrivateDownLoadThread::ThreadPrivateDownLoadThread::run() {
    auto varMutex=this->_m_ThreadQuitMutex;
  
    try{
        auto manager=memory::make_shared<QNetworkAccessManager>();
        _m_QNetworkAccessManager=QPointer<QNetworkAccessManager>(manager.get());
        exec();

        /*lock the thread when quit*/
        std::unique_lock<std::shared_timed_mutex> _lock_{*varMutex};
        manager.reset();
    }
    catch (...) {}
}

void PrivateDownLoadThread::download(std::shared_ptr<CallBackDownLoadThread> arg) {
    if (bool(arg)==false) { return; }
    if (arg->isSourceDeleted()) { return; }
    auto varMutex=this->_m_ThreadQuitMutex;
    std::shared_lock<std::shared_timed_mutex> varLock{*varMutex};
    auto & varQNetworkAccessManager=_m_Thread->_m_QNetworkAccessManager;
    if (varQNetworkAccessManager) {
        auto varReply=varQNetworkAccessManager->get(QNetworkRequest(arg->getUrl()));
        connect(varReply,&QNetworkReply::finished,varReply,
            [arg,varReply]() {
            if (arg->isSourceDeleted()) { return; }
            varReply->deleteLater();
            arg->setData(varReply->readAll());
            arg->finished(arg);
        });
    }
}

PrivateDownLoadThread::~PrivateDownLoadThread() {
    _m_Thread->quit();
}

}/*baidu*/









