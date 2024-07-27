#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QFrame>

#include "add_printer/addprinterwizard.h"
#include "edit_printer/editprinterdialog.h"
#include "printerlistwidget.h"

#include "theme/themesettingspage.h"

#include "QSourceHighlite/qsourcehighliter.h"

using namespace QSourceHighlite;

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
    void printerListWidgetItemSelectedEvent(PrinterListItem *item);

    void editPrinterButtonClickEvent();
    void addPrinterButtonClickEvent();
    void removePrinterButtonClickEvent();

    void printersActionButtonClickEvent();
    void themeActionButtonClickEvent();
    void systemActionButtonClickEvent();

private:
    Ui::SettingsPage *ui;

    AddPrinterWizard *m_addPrinterWizard = nullptr;
    EditPrinterDialog *m_editPrinterDialog = nullptr;
    PrinterListWidget *m_printerListWidget = nullptr;

    ThemeSettingsPage *m_themeSettingsPage = nullptr;

    QIconButton *m_addPrinterButton = nullptr;
    QIconButton *m_editPrinterButton = nullptr;
    QIconButton *m_removePrinterButton = nullptr;

    QIconButton *m_printersActionButton = nullptr;
    QIconButton *m_themeActionButton = nullptr;
    QIconButton *m_systemActionButton = nullptr;
};

#endif // SETTINGSPAGE_H
