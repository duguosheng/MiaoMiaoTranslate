#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "common.h"

const QString SettingDialog::apiType[] = {"baidu", "youdao"};

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    initDialog();
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::initDialog()
{
    setting->beginGroup("Global");
    if (setting->value("autostart", false).toBool())
        ui->cBoxAutoStart->setCheckState(Qt::Checked);
    else
        ui->cBoxAutoStart->setCheckState(Qt::Unchecked);

    if (setting->value("selecttrans", false).toBool())
        ui->cBoxSelectTrans->setCheckState(Qt::Checked);
    else
        ui->cBoxSelectTrans->setCheckState(Qt::Unchecked);

    if (setting->value("api", "baidu").toString() == "baidu")
        ui->cBoxApi->setCurrentIndex(0);
    else
        ui->cBoxApi->setCurrentIndex(1);

    QString rmLB = setting->value("rmlb", "nothing").toString();
    if (rmLB == "nothing")
        ui->cBoxRmLB->setCurrentIndex(0);
    else if (rmLB == "all")
        ui->cBoxRmLB->setCurrentIndex(1);
    else
        ui->cBoxRmLB->setCurrentIndex(2);
    setting->endGroup();

    ui->lineEditBaiduKey->setEchoMode(QLineEdit::Password);
    ui->lineEditYoudaoKey->setEchoMode(QLineEdit::Password);

    setting->beginGroup("Baidu");
    ui->lineEditBaiduAppid->setText(setting->value("appid", QString()).toString());
    ui->lineEditBaiduKey->setText(setting->value("key", QString()).toString());
    setting->endGroup();

    setting->beginGroup("Youdao");
    ui->lineEditYoudaoAppid->setText(setting->value("appid", QString()).toString());
    ui->lineEditYoudaoKey->setText(setting->value("key", QString()).toString());
    setting->endGroup();
}

void SettingDialog::on_btnSave_clicked()
{
    setting->beginGroup("Global");
    setting->setValue("autostart", ui->cBoxAutoStart->isChecked());
    setting->setValue("selecttrans", ui->cBoxSelectTrans->isChecked());
    setting->setValue("api", apiType[ui->cBoxApi->currentIndex()]);
    int rmLBIndex = ui->cBoxRmLB->currentIndex();
    switch (rmLBIndex) {
    case 0:
        setting->setValue("rmlb", "nothing");
        break;
    case 1:
        setting->setValue("rmlb", "all");
        break;
    case 2:
        setting->setValue("rmlb", "nopunc");
        break;
    default: break;
    }
    setting->endGroup();

    setting->beginGroup("Baidu");
    setting->setValue("appid", ui->lineEditBaiduAppid->text());
    setting->setValue("key", ui->lineEditBaiduKey->text());
    setting->endGroup();

    setting->beginGroup("Youdao");
    setting->setValue("appid", ui->lineEditYoudaoAppid->text());
    setting->setValue("key", ui->lineEditYoudaoKey->text());
    setting->endGroup();

    emit settingChanged();
    close();
}


void SettingDialog::on_btnClose_clicked()
{
    close();
}

