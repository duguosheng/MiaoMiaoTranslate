#include "translatewidget.h"
#include "./ui_translatewidget.h"
#include "common.h"

#include <QDir>
#include <QMouseEvent>

TranslateWidget::TranslateWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TranslateWidget)
    , isDrag(false)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setMouseTracking(true);
    api = new ApiManager(this);
    timer = new QTimer(this);
    clip = QGuiApplication::clipboard();
    animation = new QPropertyAnimation(this, "windowOpacity", this);
    animation->setDuration(750);
    animation->setStartValue(1);
    animation->setEndValue(0);
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
    timer->start(750);
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
    ui->textEditInput->setFont(textFont);
    ui->textBrowseroutput->setFont(textFont);
    setting->endGroup();
    api->readSetting();
}

void TranslateWidget::mousePressEvent(QMouseEvent *event)
{
    if (!event)
        return;

    if (event->button() == Qt::LeftButton) {
        isDrag = true;
        //获得鼠标的初始位置
        mouseStartPoint = event->globalPosition().toPoint();
        //获得窗口的初始位置
        widgetTopLeftPoint = this->frameGeometry().topLeft();
    }
}

int i = 0;

void TranslateWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!event)
        return;
    if (isDrag) {
        // 获取鼠标移动的距离
        QPoint distance = event->globalPosition().toPoint() - mouseStartPoint;
        // 改变窗口的位置
        this->move(widgetTopLeftPoint + distance);
    }
}

void TranslateWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (!event)
        return;

    if (event->button() == Qt::LeftButton) {
        isDrag = false;
    }
}

