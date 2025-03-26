#ifndef PRINTERTOOLSDIALOG_H
#define PRINTERTOOLSDIALOG_H

#include <QDialog>

namespace Ui {
class PrinterToolsDialog;
}

class PrinterToolsDialog : public QDialog
{
    Q_OBJECT

public:

    enum DialogCode
    {
        Rejected = 0,
        Accepted,
        PIDCalibrate,
        ZOffset,
        InputShaper
    };

    explicit PrinterToolsDialog(QWidget *parent = nullptr);
    ~PrinterToolsDialog();

protected:
    virtual void changeEvent(QEvent *event) override;
    void setIcons();

private slots:
    void on_pidCalibrateButton_clicked();

    void on_zOffsetWizardButton_clicked();

    void on_inputShaperWizardButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::PrinterToolsDialog *ui;
};

#endif // PRINTERTOOLSDIALOG_H
