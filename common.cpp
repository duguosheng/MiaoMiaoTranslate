#include "common.h"
#include <QApplication>
#include <QDir>

QSettings *setting = nullptr;

/**
 * @brief appAutoRun 设置开机自启动
 * @param bAutoRun 是否开机自启动
 */
void autoStart(bool isAutoRun)
{
    QSettings reg("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    QString applicationName = QApplication::applicationName();
    if (isAutoRun) {
        QString strAppPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
        reg.setValue(applicationName, strAppPath);
    } else {
        reg.remove(applicationName);
    }
}
