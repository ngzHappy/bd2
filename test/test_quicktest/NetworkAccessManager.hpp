#ifndef NETWORKACCESSMANAGER_HPP
#define NETWORKACCESSMANAGER_HPP

#include <atomic>
#include <cinttypes>
#include <QtNetwork/qnetworkaccessmanager.h>

class NetworkAccessManager :
    public QNetworkAccessManager {
    Q_OBJECT
protected:
    std::atomic<std::intmax_t> _m_ReplyCount{ 0 };
public:
    NetworkAccessManager(QObject* /*parent*/=nullptr);
    ~NetworkAccessManager();
public:
    std::intmax_t replyCount()const { return _m_ReplyCount.load(); }
    bool isAllReplyFinished()const { return _is_wait_finished(); }
    void waitForAllReplyFinished() { _p_wait_for_all_reply_deleted(); }
protected:
    QNetworkReply *createRequest(Operation,const QNetworkRequest &,QIODevice *) override;
    void _p_wait_for_all_reply_deleted();
    bool _is_wait_finished()const;
};

#endif // NETWORKACCESSMANAGER_HPP
