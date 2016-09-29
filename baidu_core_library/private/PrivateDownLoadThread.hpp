#ifndef _private_DOWN_LOAD_THREAD_
#define _private_DOWN_LOAD_THREAD_

#include <mutex>
#include <shared_mutex>
#include <QtCore/qpointer.h>
#include <QtCore/qthread.h>
#include <QtNetwork/qnetworkaccessmanager.h>
#include "../DownLoadThread.hpp"

namespace baidu {



class BAIDU_CORE_LIBRARYSHARED_EXPORT PrivateDownLoadThread : public QObject{
    Q_OBJECT
public:
    PrivateDownLoadThread();
    virtual ~PrivateDownLoadThread();
public:
    std::shared_ptr<std::shared_timed_mutex> _m_ThreadQuitMutex;
    class ThreadPrivateDownLoadThread:public QThread {
    public:
        QPointer<QNetworkAccessManager> _m_QNetworkAccessManager;
        std::shared_ptr<std::shared_timed_mutex> _m_ThreadQuitMutex;
    protected:
        virtual void run()override;
    private:
        MEMORY_CLASS_NEW_DELETE
    };
    ThreadPrivateDownLoadThread * _m_Thread;
public:
    Q_SLOT void download(std::shared_ptr<CallBackDownLoadThread>);
private:
    PrivateDownLoadThread(PrivateDownLoadThread&&)=delete;
    PrivateDownLoadThread&operator=(PrivateDownLoadThread&&)=delete;
    PrivateDownLoadThread(const PrivateDownLoadThread&)=delete;
    PrivateDownLoadThread&operator=(const PrivateDownLoadThread&)=delete;
private:
    MEMORY_CLASS_NEW_DELETE
};

}


#endif
