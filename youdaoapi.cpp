#include "youdaoapi.h"

#include <QRandomGenerator>
#include <QCryptographicHash>

YoudaoApi::YoudaoApi(QObject *parent)
    : TranslateAPI{parent},
    baseUrl("https://openapi.youdao.com/api")
{
    fromLang = "en";
    toLang = "zh-CHS";
}

void YoudaoApi::replyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit queryFail("Network Error");
        return;
    }
    QString all = reply->readAll();
    reply->deleteLater();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(all.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();
    auto errCode = jsonObject["errorCode"].toString();
    if (errCode != "0") {
        emit queryFail("错误代码：" + errCode);
        return;
    }
    auto resultArr = jsonObject.value("translation").toArray();
    QString res;
    for (auto resultLine : resultArr) {
        res += resultLine.toString();
    }
    emit queryOk(res);
}

void YoudaoApi::setTransLang(bool enToZh)
{
    if (enToZh) {
        fromLang = "en";
        toLang = "zh-CHS";
    } else {
        fromLang = "zh-CHS";
        toLang = "en";
    }
}

QUrl YoudaoApi::getUrl(QString &text)
{
    QUrl res(baseUrl);
    quint32 randomVal = QRandomGenerator::global()->bounded(1000000000, 9999999999);
    salt = QString::number(randomVal);
    QString curTime = QString::number(QDateTime::currentDateTime().toSecsSinceEpoch());
    QString input;
    if (text.size() > 20) {
        input = text.first(10) + QString::number(text.size()) + text.last(10);
    } else {
        input = text;
    }
    QString sign = appid + input + salt + curTime + secretKey;
    QString signHash = calculateHash(sign, QCryptographicHash::Sha256);

    QUrlQuery query;
    query.addQueryItem("from", fromLang);
    query.addQueryItem("to", toLang);
    query.addQueryItem("signType", "v3");
    query.addQueryItem("curtime", curTime);
    query.addQueryItem("appKey", appid);
    query.addQueryItem("q", text);
    query.addQueryItem("salt", salt);
    query.addQueryItem("sign", signHash);

    res.setQuery(query);
    return res;
}
