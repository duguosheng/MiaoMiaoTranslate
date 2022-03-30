#include "translatewidget.h"
#include "mainwindow.h"
#include "translatewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;        // 主窗口
    mainWindow.show();
    return a.exec();
}

