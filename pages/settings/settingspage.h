#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QFrame>

#include "add_printer/addprinterwizard.h"
#include "edit_printer/editprinterdialog.h"
#include "printerlistwidget.h"

#include "theme/themesettingspage.h"

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

signals:
    void printerAdded(PrinterDefinition definition);

private slots:
    void on_addPrinterButton_clicked();
    void on_addPrinterWizardFinished(int result);
    void on_addPrinterWizardCancelled();

    void on_printerListWidget_itemSelected(PrinterListItem *item);

    void on_removePrinterButton_clicked();

    void on_editPrinterButton_clicked();

    void on_printersButton_toggled(bool checked);

    void on_themeButton_toggled(bool checked);

    void on_systemButton_toggled(bool checked);

private:
    Ui::SettingsPage *ui;

    AddPrinterWizard *_addPrinterWizard = nullptr;
    EditPrinterDialog *_editPrinterDialog = nullptr;
    PrinterListWidget *_printerListWidget = nullptr;

    ThemeSettingsPage *_themeSettingsPage = nullptr;
};

#endif // SETTINGSPAGE_H
