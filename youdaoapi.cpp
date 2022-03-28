#include "youdaoapi.h"

#include <QRandomGenerator>

YoudaoApi::YoudaoApi(QObject *parent)
    : TranslateAPI{parent}
{
    quint32 randomVal = QRandomGenerator::global()->bounded(1000000000, 9999999999);
    salt = QString::number(randomVal);
}

void YoudaoApi::replyFinished(QNetworkReply *reply)
{

}

void YoudaoApi::setTransLang(bool enToZh)
{

}

QString YoudaoApi::getUrl(QString &text)
{
    return "";
}

void YoudaoApi::query(QString &text)
{

}
