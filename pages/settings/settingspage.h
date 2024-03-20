#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QFrame>

#include "../../wizards/add_printer/addprinterwizard.h"
#include "printerlistwidget.h"

namespace Ui {
class SettingsPage;
}

class SettingsPage : public QFrame
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);
    ~SettingsPage();

    void updatePrinterList();

private slots:
    void on_addPrinterButton_clicked();
    void on_addPrinterWizardFinished(int result);
    void on_addPrinterWizardCancelled();

private:
    Ui::SettingsPage *ui;

    AddPrinterWizard *_addPrinterWizard = nullptr;
    PrinterListWidget *_printerListWidget = nullptr;
};

#endif // SETTINGSPAGE_H
