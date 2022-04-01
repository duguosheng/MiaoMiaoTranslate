#ifndef YOUDAOAPI_H
#define YOUDAOAPI_H

#include "translateapi.h"

class YoudaoApi : public TranslateAPI {
    Q_OBJECT
public:
    void setTransLang(bool enToZh) override;
    QUrl getUrl(QString &text) override;

    explicit YoudaoApi(QObject *parent = nullptr);
private:
    QString salt;
    const QString baseUrl;
public slots:
    void replyFinished(QNetworkReply *reply) override;
};


#endif // YOUDAOAPI_H
