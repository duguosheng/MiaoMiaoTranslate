#include "widget.h"
#include "./ui_widget.h"
#include "common.h"

#include <QDir>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initSetting();
    connect(baidu, SIGNAL(queryOk(QString)), this, SLOT(showResult(QString)));
    connect(youdao, SIGNAL(queryOk(QString)), this, SLOT(showResult(QString)));
    connect(baidu, SIGNAL(queryFail(QString)), this, SLOT(showError(QString)));
    connect(youdao, SIGNAL(queryFail(QString)), this, SLOT(showError(QString)));
    settingDialog = new SettingDialog(this);
    connect(settingDialog, &SettingDialog::settingChanged, this, &Widget::readSetting);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_buttonLanguage_clicked(bool checked)
{
    if (checked) {
        currentApi->setTransLang(false);
        ui->buttonLanguage->setText("中文->英文");
    } else {
        currentApi->setTransLang(true);
        ui->buttonLanguage->setText("英文->中文");
    }
}

void Widget::on_buttonTranslate_clicked()
{
    QString text = ui->textEditInput->toPlainText();
    currentApi->query(text);
}


void Widget::on_buttonSetting_clicked()
{
    // 设置为模态
    settingDialog->setModal(true);
    settingDialog->show();
}

void Widget::showResult(QString res)
{
    ui->textBrowseroutput->setText(res);
}

void Widget::showError(QString err)
{
    ui->textBrowseroutput->setText("获取结果出错，请检查您的配置: " + err);
}

void Widget::querySelect()
{
    QString text = clip->text();
    ui->textEditInput->setPlainText(text);

    move(cursor().pos());
    activateWindow();
    raise();

    currentApi->query(text);
}

void Widget::readSetting()
{
    // 读取配置
    // 百度API配置
    setting->beginGroup("Baidu");
    baidu->appid = setting->value("appid", QString()).toString();
    baidu->secretKey = setting->value("key", QString()).toString();
    setting->endGroup();

    // 有道API配置
    setting->beginGroup("Youdao");
    youdao->appid = setting->value("appid", QString()).toString();
    youdao->secretKey = setting->value("key", QString()).toString();
    setting->endGroup();

    // 全局配置
    setting->beginGroup("Global");
    autoStart(setting->value("autostart", false).toBool());

    selectTrans = setting->value("selecttrans", false).toBool();

    if (selectTrans)
        connect(clip, &QClipboard::dataChanged, this, &Widget::querySelect);
    else
        disconnect(clip, &QClipboard::dataChanged, this, &Widget::querySelect);

    if (setting->value("api", "baidu").toString() == "baidu")
        currentApi = baidu;
    else
        currentApi = youdao;

    QString rmLB = setting->value("rmlb", "nothing").toString();
    if (rmLB == "nothing")
        currentApi->rmType = TranslateAPI::RM_NOTHING;
    else if (rmLB == "all")
        currentApi->rmType = TranslateAPI::RM_ALL;
    else
        currentApi->rmType = TranslateAPI::RM_NOPUNC;
    setting->endGroup();
}

void Widget::initSetting()
{
    QCoreApplication::setOrganizationName("DuGuosheng");
    QCoreApplication::setOrganizationDomain("dgs.zone");
    QCoreApplication::setApplicationName("Translation");

    clip = QGuiApplication::clipboard();

    baidu = new BaiduApi(this);
    youdao = new YoudaoApi(this);
    //所有系统都以ini文件方式创建设置对象
    setting = new QSettings(QSettings::IniFormat, QSettings::UserScope,
                            QApplication::organizationName(), QApplication::applicationName(), this);

    //向ini文件中不存在的配置项写入初始值
    setting->beginGroup("Global");
    if (!setting->contains("autostart"))
        setting->setValue("autostart", false);
    if (!setting->contains("selecttrans"))
        setting->setValue("selecttrans", false);
    if (!setting->contains("api"))
        setting->setValue("api", "baidu");
    if (!setting->contains("rmlb"))  // remove line break
        setting->setValue("rmlinebreak", "nothing");
    setting->endGroup();

    setting->beginGroup("Baidu");
    if (!setting->contains("appid"))
        setting->setValue("appid", QString());
    if (!setting->contains("key"))
        setting->setValue("key", QString());
    setting->endGroup();

    setting->beginGroup("Youdao");
    if (!setting->contains("appid"))
        setting->setValue("appid", QString());
    if (!setting->contains("key"))
        setting->setValue("key", QString());
    setting->endGroup();

    readSetting();
}
