#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <QObject>
#include "baiduapi.h"
#include "youdaoapi.h"

class ApiManager : public QObject {
    Q_OBJECT
public:
    BaiduApi *baidu;
    YoudaoApi *youdao;
    TranslateAPI *currentApi;
    explicit ApiManager(QObject *parent = nullptr);
    void readSetting();
    void query(QString &text);
    void setTransLang(bool enToZh);

public slots:
    void recvOk(QString res);
    void recvFail(QString err);

signals:
    void queryOk(QString res);
    void queryFail(QString err);
};

#endif // APIMANAGER_H
