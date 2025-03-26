#ifndef MACHINEPOWERDIALOG_H
#define MACHINEPOWERDIALOG_H

#include <QDialog>

namespace Ui {
class MachinePowerDialog;
}

class MachinePowerDialog : public QDialog
{
    Q_OBJECT

public:

    enum DialogCode
    {
        Rejected = 0,
        Accepted,
        Shutdown,
        Restart,
        KlipperRestart,
        FirmwareRestart
    };

    explicit MachinePowerDialog(QWidget *parent = nullptr);
    ~MachinePowerDialog();

protected:
    virtual void changeEvent(QEvent *event) override;
    void setIcons();

private slots:
    void on_shutdownButton_toggled(bool checked);

    void on_restartButton_toggled(bool checked);

    void on_firmwareRestartButton_toggled(bool checked);

    void on_restartKlipperButton_toggled(bool checked);

    void on_cancelButton_clicked();

    void on_acceptButton_clicked();

private:
    Ui::MachinePowerDialog *ui;
};

#endif // MACHINEPOWERDIALOG_H
