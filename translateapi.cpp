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
    QUrl url = getUrl(text);
    manager->get(QNetworkRequest(url));
}

QString TranslateAPI::calculateHash(const QString &text, QCryptographicHash::Algorithm algo)
{
    return QString(QCryptographicHash::hash(text.toUtf8(), algo).toHex());
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
        re.setPattern("(?<!\\.|\\!|\\?)\\n");
        break;
    }
    text.replace(re, " ");
}
