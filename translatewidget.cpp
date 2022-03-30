#include "translatewidget.h"
#include "./ui_translatewidget.h"
#include "common.h"

#include <QDir>
#include <QMouseEvent>

TranslateWidget::TranslateWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TranslateWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    api = new ApiManager(this);
    timer = new QTimer(this);
    clip = QGuiApplication::clipboard();
    animation = new QPropertyAnimation(this, "windowOpacity", this);
    animation->setDuration(500);
    animation->setStartValue(1.0);
    animation->setEndValue(0.5);
    connect(timer, SIGNAL(timeout()), this, SLOT(hideWidget()));
    connect(api, SIGNAL(queryOk(QString)), this, SLOT(showResult(QString)));
    connect(api, SIGNAL(queryFail(QString)), this, SLOT(showError(QString)));
}

TranslateWidget::~TranslateWidget()
{
    delete ui;
}


void TranslateWidget::on_buttonLanguage_clicked(bool checked)
{
    if (checked) {
        api->setTransLang(false);
        ui->buttonLanguage->setText("中文->英文");
    } else {
        api->setTransLang(true);
        ui->buttonLanguage->setText("英文->中文");
    }
}

void TranslateWidget::on_buttonTranslate_clicked()
{
    QString text = ui->textEditInput->toPlainText();
    api->query(text);
}

void TranslateWidget::showResult(QString res)
{
    ui->textBrowseroutput->setText(res);
}

void TranslateWidget::showError(QString err)
{
    ui->textBrowseroutput->setText("获取结果出错，请检查您的配置！" + err);
}

void TranslateWidget::querySelect()
{
    QString text = clip->text();
    ui->textEditInput->setPlainText(text);

    move(cursor().pos());
    show();

    api->query(text);
}

void TranslateWidget::hideWidget()
{
    hide();
    timer->stop();
    animation->stop();
    setWindowOpacity(1);
}

void TranslateWidget::enterEvent(QEnterEvent *e)
{
    timer->stop();
    animation->stop();
    setWindowOpacity(1);
}

void TranslateWidget::leaveEvent(QEvent *e)
{
    animation->setCurrentTime(0);
    animation->start();
    timer->start(1000);
}

void TranslateWidget::readSetting()
{
    // 全局配置
    setting->beginGroup("Global");
    selectTrans = setting->value("selecttrans", false).toBool();
    if (selectTrans)
        connect(clip, &QClipboard::dataChanged, this, &TranslateWidget::querySelect);
    else
        disconnect(clip, &QClipboard::dataChanged, this, &TranslateWidget::querySelect);
    setting->endGroup();
    api->readSetting();
}


