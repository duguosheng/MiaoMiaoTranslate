#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui
{
    class SettingDialog;
}

class SettingDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();

private slots:
    void on_btnSave_clicked();
    void on_btnClose_clicked();
    void on_btnFont_clicked();

private:
    Ui::SettingDialog *ui;
    QFont font;
    static const QString apiType[];
    void initDialog();
signals:
    void settingChanged();
};

#endif // SETTINGDIALOG_H
