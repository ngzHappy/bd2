#ifndef __DOWN_LOAD_THREAD_
#define __DOWN_LOAD_THREAD_

#include "BaiduCoreLibrary.hpp"
#include <atomic>
#include <QtCore/qurl.h>
#include <QtCore/qobject.h>
#include <class/class.hpp>

namespace baidu {

class PrivateDownLoadThread;

class BAIDU_CORE_LIBRARYSHARED_EXPORT CallBackDownLoadThread :
    public QObject,
    public std::enable_shared_from_this<CallBackDownLoadThread>{
    Q_OBJECT
protected:
    QUrl _m_QUrl;
    QByteArray _m_Data;
    std::atomic<bool> _m_IsSourceDeleted{false};
    bool _m_IsFinished=false;
public:
    CallBackDownLoadThread()=default;

    static std::shared_ptr<CallBackDownLoadThread> instance() {
        return memory::make_shared<CallBackDownLoadThread>();
    }

    void connect_on_finished(
        QObject *o,std::function<void(std::shared_ptr<CallBackDownLoadThread>)>arg) {
        connect(this,&CallBackDownLoadThread::finished,o,std::move(arg),
            Qt::QueuedConnection);
        connect(o,&QObject::destroyed,this,
            [this]() {_m_IsSourceDeleted.store(true); },Qt::QueuedConnection);
    }

    void setUrl(const QUrl &arg) { _m_QUrl=arg; }
    void setUrl(QUrl &&arg) { _m_QUrl=std::move(arg); }
    const QUrl & getUrl() const { return _m_QUrl; }
    bool isSourceDeleted() const { return _m_IsSourceDeleted.load(); }
    void setData(const QByteArray&arg) { _m_IsFinished=true; _m_Data=arg; }
    void setData(QByteArray&&arg) { _m_IsFinished=true; _m_Data=std::move(arg); }

public:
    Q_SIGNAL void finished(std::shared_ptr<CallBackDownLoadThread>);
public:
    virtual ~CallBackDownLoadThread() {}
private:
    CPLUSPLUS_CLASS_META
};

/*每个实例启动一个新线程用于下载*/
class BAIDU_CORE_LIBRARYSHARED_EXPORT DownLoadThread:public QObject{
    Q_OBJECT
protected:
    PrivateDownLoadThread * _m_Data;
    explicit DownLoadThread(PrivateDownLoadThread*);
public:
    explicit DownLoadThread(QObject* /**/=nullptr);
    virtual~DownLoadThread();
public:
    Q_SIGNAL void download(std::shared_ptr<CallBackDownLoadThread>);
private:
    DownLoadThread(const DownLoadThread&)=delete;
    DownLoadThread(DownLoadThread&&)=delete;
    DownLoadThread&operator=(const DownLoadThread&)=delete;
    DownLoadThread&operator=(DownLoadThread&&)=delete;
private:
    CPLUSPLUS_CLASS_META
};

}/*baidu*/

Q_DECLARE_METATYPE(std::shared_ptr<baidu::CallBackDownLoadThread>)

#endif




