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
        return;
    }
    QString all = reply->readAll();
    reply->deleteLater();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(all.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();
    auto errMsg = jsonObject["error_msg"].toString();
    if (!errMsg.isEmpty()) {
        emit queryFail(errMsg);
        return;
    }
    auto resultArr = jsonObject.value("trans_result").toArray();
    QString res;
    for (auto resultLine : resultArr) {
        auto obj = resultLine.toObject();
        res += obj["dst"].toString() + "\n";
    }

    emit queryOk(res);
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

QUrl BaiduApi::getUrl(QString &text)
{
    QUrl res(baseUrl);
    QString sign = appid + text + salt + secretKey;
    QString signHash = calculateHash(sign);

    QUrlQuery query;
    query.addQueryItem("q", text);
    query.addQueryItem("from", fromLang);
    query.addQueryItem("to", toLang);
    query.addQueryItem("appid", appid);
    query.addQueryItem("salt", salt);
    query.addQueryItem("sign", signHash);

    res.setQuery(query);
    return res;
}

