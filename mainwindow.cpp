#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 添加作者信息
    QLabel* infoLabel = new QLabel(this);
    infoLabel->setText("https://github.com/duguosheng/MiaoMiaoTranslate");
    ui->statusbar->addPermanentWidget(infoLabel);
    // 创建设置管理器
    QCoreApplication::setOrganizationName("DuGuosheng");
    QCoreApplication::setOrganizationDomain("dgs.zone");
    QCoreApplication::setApplicationName("Translation");
    //所有系统都以ini文件方式创建设置对象
    setting = new QSettings(QSettings::IniFormat, QSettings::UserScope,
                            QApplication::organizationName(), QApplication::applicationName(), this);
    // 初始化设置
    initSetting();
    // 创建设置窗口
    settingDialog = new SettingDialog(this);
    settingDialog->setModal(true);
    // 创建浮动窗口
    floatWidget = new TranslateWidget();
    // 创建api管理器
    api = new ApiManager(this);
    // 读取设置
    readSetting();
    // 连接信号和槽
    connect(settingDialog, SIGNAL(settingChanged()), this, SLOT(readSetting()));
    connect(api, SIGNAL(queryOk(QString)), this, SLOT(showResult(QString)));
    connect(api, SIGNAL(queryFail(QString)), this, SLOT(showError(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete floatWidget;
}

void MainWindow::on_action_T_triggered(bool checked)
{
    setWindowFlag(Qt::WindowStaysOnTopHint, checked);
    show();
    if (checked) {
        ui->action_T->setText("取消置顶(&T)");
    } else {
        ui->action_T->setText("窗口置顶(&T)");
    }
}

void MainWindow::showResult(QString res)
{
    ui->textBrowseroutput->setText(res);
}

void MainWindow::showError(QString err)
{
    ui->textBrowseroutput->setText("获取结果出错，请检查您的配置！" + err);
}

void MainWindow::initSetting()
{
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
}

void MainWindow::readSetting()
{
    setting->beginGroup("Global");
    autoStart(setting->value("autostart", false).toBool());
    setting->endGroup();
    api->readSetting();
    floatWidget->readSetting();
}


void MainWindow::on_buttonLanguage_clicked(bool checked)
{
    if (checked) {
        api->setTransLang(false);
        ui->buttonLanguage->setText("中文->英文");
    } else {
        api->setTransLang(true);
        ui->buttonLanguage->setText("英文->中文");
    }
}


void MainWindow::on_buttonTranslate_clicked()
{
    QString text = ui->textEditInput->toPlainText();
    api->query(text);
}


void MainWindow::on_action_S_triggered()
{
    settingDialog->show();
}

