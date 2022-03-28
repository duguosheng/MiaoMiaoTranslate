#include "translateapi.h"
#include <QCryptographicHash>
#include <QRegularExpression>

TranslateAPI::TranslateAPI(QObject *parent)
    : QObject{parent}
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &TranslateAPI::replyFinished);
}

void TranslateAPI::query(QString &text)
{
    rmLineBreak(text);
    QString url = getUrl(text);
    manager->get(QNetworkRequest(QUrl(url)));
}

QString TranslateAPI::calculateMd5(const QString& text)
{
    return QString(QCryptographicHash::hash(text.toUtf8(), QCryptographicHash::Md5).toHex());
}

void TranslateAPI::rmLineBreak(QString &text)
{
    QRegularExpression re;
    switch (rmType) {
    case RM_NOTHING:
        return;
    case RM_ALL:
        re.setPattern("\\n");
        break;
    case RM_NOPUNC:
        re.setPattern("[^.!?]\\n");
        break;
    }
    text.replace(re, " ");
}
