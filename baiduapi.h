#ifndef BAIDUAPI_H
#define BAIDUAPI_H

#include "translateapi.h"

class BaiduApi : public TranslateAPI
{
    Q_OBJECT
public:
    void setTransLang(bool enToZh) override;
    QString getUrl(QString& text) override;

    explicit BaiduApi(QObject *parent = nullptr);
private:
    QString salt;
    const QString baseUrl;
public slots:
    void replyFinished(QNetworkReply *reply) override;
};

#endif // BAIDUAPI_H
