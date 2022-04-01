#ifndef TRANSLATEWIDGET_H
#define TRANSLATEWIDGET_H

#include <QWidget>
#include <QClipboard>
#include <QTimer>
#include <QPropertyAnimation>
#include "settingdialog.h"
#include "apimanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TranslateWidget; }
QT_END_NAMESPACE

class TranslateWidget : public QWidget {
    Q_OBJECT

public:
    TranslateWidget(QWidget *parent = nullptr);
    ~TranslateWidget();
    void readSetting();

private slots:
    void on_buttonLanguage_clicked(bool checked);
    void on_buttonTranslate_clicked();
    void showResult(QString res);
    void showError(QString err);
    void querySelect();
    void hideWidget();

private:
    Ui::TranslateWidget *ui;
    QClipboard *clip;
    ApiManager *api;
    QTimer *timer;
    QPropertyAnimation *animation;
    bool selectTrans;
    void initSetting();
    void enterEvent(QEnterEvent *e); // 鼠标移入事件
    void leaveEvent(QEvent *e); // 鼠标离开事件
};
#endif // TRANSLATEWIDGET_H
