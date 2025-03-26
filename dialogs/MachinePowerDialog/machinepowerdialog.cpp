#include "machinepowerdialog.h"
#include "ui_machinepowerdialog.h"
#include "flo/settings.h"

MachinePowerDialog::MachinePowerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MachinePowerDialog)
{
    ui->setupUi(this);
    //setIcons();
}

MachinePowerDialog::~MachinePowerDialog()
{
    delete ui;
}

void MachinePowerDialog::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setIcons();

    QDialog::changeEvent(event);
}

void MachinePowerDialog::setIcons()
{
    ui->shutdownButton->setIcon(
        Settings::getThemeIcon(
            "power",
            QColor::fromString(Settings::get("theme/accent-color").toString())
            )
        );
    ui->restartButton->setIcon(
        Settings::getThemeIcon(
            "restart",
            QColor::fromString(Settings::get("theme/accent-color2").toString())
            )
        );
    ui->firmwareRestartButton->setIcon(
        Settings::getThemeIcon(
            "firmware",
            QColor::fromString(Settings::get("theme/accent-color3").toString())
            )
        );
    ui->restartKlipperButton->setIcon(
        Settings::getThemeIcon(
            "restart",
            QColor::fromString(Settings::get("theme/accent-color4").toString())
            )
        );
    ui->acceptButton->setIcon(
        Settings::getThemeIcon(
            "accept",
            QColor::fromString(Settings::get("theme/icon-color").toString())
            )
        );
    ui->cancelButton->setIcon(
        Settings::getThemeIcon(
            "cancel",
            QColor::fromString(Settings::get("theme/icon-color").toString())
            )
        );
}

void MachinePowerDialog::on_shutdownButton_toggled(bool checked)
{
    if(checked)
        ui->optionTextLabel->setText("<h3>Machine Shutdown</h3>");
}

void MachinePowerDialog::on_restartButton_toggled(bool checked)
{
    if(checked)
        ui->optionTextLabel->setText("<h3>Machine Reboot</h3>");
}

void MachinePowerDialog::on_firmwareRestartButton_toggled(bool checked)
{
    if(checked)
        ui->optionTextLabel->setText("<h3>Firmware Restart</h3>");
}

void MachinePowerDialog::on_restartKlipperButton_toggled(bool checked)
{
    if(checked)
        ui->optionTextLabel->setText("<h3>Restart Klipper</h3>");
}

void MachinePowerDialog::on_cancelButton_clicked()
{
    reject();
}

void MachinePowerDialog::on_acceptButton_clicked()
{
    if(ui->shutdownButton->isChecked())
        finished(Shutdown);
    else if(ui->restartButton->isChecked())
        finished(Restart);
    else if(ui->firmwareRestartButton->isChecked())
        finished(FirmwareRestart);
    else if(ui->restartKlipperButton->isChecked())
        finished(KlipperRestart);
}
