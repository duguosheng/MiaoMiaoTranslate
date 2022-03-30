#include "apimanager.h"
#include "common.h"

ApiManager::ApiManager(QObject *parent)
    : QObject{parent}
{
    baidu = new BaiduApi(this);
    youdao = new YoudaoApi(this);
    connect(baidu,  SIGNAL(queryOk(QString)),   this, SLOT(recvOk(QString)));
    connect(baidu,  SIGNAL(queryFail(QString)), this, SLOT(recvFail(QString)));
    connect(youdao, SIGNAL(queryOk(QString)),   this, SLOT(recvOk(QString)));
    connect(youdao, SIGNAL(queryFail(QString)), this, SLOT(recvFail(QString)));
}

void ApiManager::readSetting()
{
    // 读取配置
    // 百度API配置
    setting->beginGroup("Baidu");
    baidu->appid = setting->value("appid", QString()).toString();
    baidu->secretKey = setting->value("key", QString()).toString();
    setting->endGroup();

    // 有道API配置
    setting->beginGroup("Youdao");
    youdao->appid = setting->value("appid", QString()).toString();
    youdao->secretKey = setting->value("key", QString()).toString();
    setting->endGroup();

    // 全局配置
    setting->beginGroup("Global");
    if (setting->value("api", "baidu").toString() == "baidu")
        currentApi = baidu;
    else
        currentApi = youdao;

    QString rmLB = setting->value("rmlb", "nothing").toString();
    if (rmLB == "nothing")
        currentApi->rmType = TranslateAPI::RM_NOTHING;
    else if (rmLB == "all")
        currentApi->rmType = TranslateAPI::RM_ALL;
    else
        currentApi->rmType = TranslateAPI::RM_NOPUNC;
    setting->endGroup();
}

void ApiManager::query(QString &text)
{
    currentApi->query(text);
}

void ApiManager::setTransLang(bool enToZh)
{
    currentApi->setTransLang(enToZh);
}

void ApiManager::recvOk(QString res)
{
    emit queryOk(res);
}

void ApiManager::recvFail(QString err)
{
    emit queryFail(err);
}
