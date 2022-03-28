#ifndef COMMON_H
#define COMMON_H

#include <QSettings>
#include "baiduapi.h"
#include "youdaoapi.h"

extern QSettings* setting;
extern BaiduApi* baidu;
extern YoudaoApi* youdao;
extern TranslateAPI* currentApi;
extern bool selectTrans;

void autoStart(bool isAutoRun);
#endif // COMMON_H
