#include "baiduapi.h"
#include <QRandomGenerator>
#include <QJsonObject>
#include <QJsonDocument>

BaiduApi::BaiduApi(QObject *parent)
    : TranslateAPI{parent},
      baseUrl("http://api.fanyi.baidu.com/api/trans/vip/translate")
{
    fromLang = "en";
    toLang = "zh";
    quint32 randomVal = QRandomGenerator::global()->bounded(1000000000, 9999999999);
    salt = QString::number(randomVal);
}

void BaiduApi::replyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit queryFail("Network Error");
        qDebug() << "error1";
        return;
    }
    QString all = reply->readAll();
    qDebug() << all;
    reply->deleteLater();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(all.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();
    auto errMsg = jsonObject["error_msg"].toString();
    if (!errMsg.isEmpty()) {
        emit queryFail(errMsg);
        qDebug() << "error2";
        return;
    }
    auto resultArr = jsonObject.value("trans_result").toArray();
    QString res;
    for (auto resultLine : resultArr) {
        auto obj = resultLine.toObject();
        res += obj["dst"].toString() + "\n";
    }

    emit queryOk(res);
    qDebug() << "ok";
}

void BaiduApi::setTransLang(bool enToZh)
{
    if (enToZh) {
        fromLang = "en";
        toLang = "zh";
    } else {
        fromLang = "zh";
        toLang = "en";
    }
}

QString BaiduApi::getUrl(const QString &text)
{
    QString res;
    QString sign = appid + text + salt + secretKey;
    QString signMd5 = calculateMd5(sign);
    res = baseUrl + "?q=" + text + "&from=" + fromLang + "&to=" + toLang
        + "&appid=" + appid + "&salt=" + salt + "&sign=" + signMd5;
    return res;
}

