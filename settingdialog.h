#pragma once

#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include "ui_settingdialog.h"
#include <QDialog>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();
    int getSize();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
