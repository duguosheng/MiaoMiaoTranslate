#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QClipboard>
#include "settingdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_buttonLanguage_clicked(bool checked);
    void on_buttonTranslate_clicked();
    void on_buttonSetting_clicked();
    void showResult(QString res);
    void showError(QString err);
    void querySelect();
    void readSetting();

private:
    Ui::Widget *ui;
    QClipboard *clip;
    SettingDialog *settingDialog = nullptr;
    void initSetting();
};
#endif // WIDGET_H
