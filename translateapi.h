#ifndef TRANSLATEAPI_H
#define TRANSLATEAPI_H

#include <QObject>
#include <QtNetwork>

class TranslateAPI : public QObject {
    Q_OBJECT
public:
    enum {
        RM_NOTHING,
        RM_ALL,
        RM_NOPUNC
    } rmType = RM_NOTHING;
    QString appid;
    QString secretKey;
    QString fromLang;
    QString toLang;
    QNetworkAccessManager *manager;
    virtual void setTransLang(bool enToZh) = 0;
    virtual QUrl getUrl(QString &text) = 0;
    virtual void query(QString &text);
    QString calculateHash(const QString &text, QCryptographicHash::Algorithm algo = QCryptographicHash::Md5);
    void rmLineBreak(QString &text);

    explicit TranslateAPI(QObject *parent = nullptr);
signals:
    void queryOk(QString res);
    void queryFail(QString err);
public slots:
    virtual void replyFinished(QNetworkReply *) = 0;
};

#endif // TRANSLATEAPI_H
