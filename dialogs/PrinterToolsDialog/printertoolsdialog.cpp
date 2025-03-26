#include "printertoolsdialog.h"
#include "ui_printertoolsdialog.h"
#include "flo/settings.h"

PrinterToolsDialog::PrinterToolsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PrinterToolsDialog)
{
    ui->setupUi(this);
}

PrinterToolsDialog::~PrinterToolsDialog()
{
    delete ui;
}

void PrinterToolsDialog::on_pidCalibrateButton_clicked()
{
    finished(PIDCalibrate);
}

void PrinterToolsDialog::on_zOffsetWizardButton_clicked()
{
    finished(ZOffset);
}

void PrinterToolsDialog::on_inputShaperWizardButton_clicked()
{
    finished(InputShaper);
}

void PrinterToolsDialog::on_cancelButton_clicked()
{
    reject();
}

void PrinterToolsDialog::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setIcons();

    QDialog::changeEvent(event);
}

void PrinterToolsDialog::setIcons()
{
    ui->inputShaperWizardButton->setIcon(
        Settings::getThemeIcon(
            "input-shaper",
            QColor::fromString(Settings::get("theme/accent-color").toString())
            )
        );
    ui->zOffsetWizardButton->setIcon(
        Settings::getThemeIcon(
            "zoffset",
            QColor::fromString(Settings::get("theme/accent-color2").toString())
            )
        );
    ui->pidCalibrateButton->setIcon(
        Settings::getThemeIcon(
            "sine",
            QColor::fromString(Settings::get("theme/accent-color3").toString())
            )
        );
    ui->cancelButton->setIcon(
        Settings::getThemeIcon(
            "cancel",
            QColor::fromString(Settings::get("theme/icon-color").toString())
            )
        );
}
