#ifndef COMMON_H
#define COMMON_H

#include <QSettings>
#include "baiduapi.h"
#include "youdaoapi.h"

extern QSettings *setting;
extern QFont textFont;

void autoStart(bool isAutoRun);
#endif // COMMON_H
