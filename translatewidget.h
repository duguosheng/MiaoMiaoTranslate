#ifndef TRANSLATEWIDGET_H
#define TRANSLATEWIDGET_H

#include <QWidget>
#include <QClipboard>
#include "settingdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TranslateWidget; }
QT_END_NAMESPACE

class TranslateWidget : public QWidget
{
    Q_OBJECT

public:
    TranslateWidget(QWidget *parent = nullptr);
    ~TranslateWidget();

private slots:
    void on_buttonLanguage_clicked(bool checked);
    void on_buttonTranslate_clicked();
    void on_buttonSetting_clicked();
    void showResult(QString res);
    void showError(QString err);
    void querySelect();
    void readSetting();

private:
    Ui::TranslateWidget *ui;
    QClipboard *clip;
    SettingDialog *settingDialog = nullptr;
    void initSetting();
};
#endif // TRANSLATEWIDGET_H
