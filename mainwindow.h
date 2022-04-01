#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "apimanager.h"
#include "settingdialog.h"
#include "translatewidget.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_T_triggered(bool checked);
    void showResult(QString res);
    void showError(QString err);
    void initSetting();
    void readSetting();

    void on_buttonLanguage_clicked(bool checked);

    void on_buttonTranslate_clicked();

    void on_action_S_triggered();

private:
    Ui::MainWindow *ui;
    ApiManager *api;
    SettingDialog *settingDialog;
    TranslateWidget *floatWidget;  // 浮动窗口
};

#endif // MAINWINDOW_H
