/*
* Flo :: SettingsPage
*
* Provides pages to edit application settings
*
* Copyright (C) 2024-2025 DigitalArtifex
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QFrame>
#include <QMessageBox>
#include <QParallelAnimationGroup>
#include <qquickview.h>

#include "3rdparty/QtSheet/sheet.h"
#include "edit_printer/editprinterdialog.h"
#include "printerlistwidget.h"

#include "qpropertyanimation.h"
#include "theme/themesettingspage.h"
#include "system/systemsettingspage.h"
#include "common/Page/page.h"

#include "3rdparty/QSourceHighlite/qsourcehighliter.h"

using namespace QSourceHighlite;

namespace Ui {
class SettingsPage;
}

class SettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);
    ~SettingsPage();

    void updatePrinterList();

    void reset();
    void apply();
    bool requiresRestart();

public slots:
    // virtual void setStyleSheet(const QString &styleSheet);

signals:
    void printerAdded(QKlipperInstance *definition);
    void dialogRequested(QDialog *);
    void wizardRequested(QWizard *);

protected slots:

private slots:
    void printerListWidgetItemSelectedEvent(PrinterListItem *item);

    void onEditPrinterButtonClicked();
    void onEditPrinterDialogFinished(int returnCode);
    void onAddPrinterButtonClicked();
    void onAddPrinterDialogFinished(int returnCode);
    void onRemovePrinterButtonClicked();

    void printersActionButtonClickEvent();
    void themeActionButtonClickEvent();
    void systemActionButtonClickEvent();

    void onResetButtonClicked();
    void onCancelButtonClicked();
    void onApplyButtonClicked();

    void setupIcons();

    void showPrinterButtons();
    void showSettingsButtons();

    void onDialogRequested(QDialog *dialog);
    void onDialogFinished(int returnCode);
    void onWizardRequested(QWizard *wizard);
    void onWizardFinished(int returnCode);

protected:
    virtual void changeEvent(QEvent *event) override;

private:
    Ui::SettingsPage *ui;

    EditPrinterDialog *m_editPrinterDialog = nullptr;
    PrinterListWidget *m_printerListWidget = nullptr;

    ThemeSettingsPage *m_themeSettingsPage = nullptr;
    SystemSettingsPage *m_systemSettingsPage = nullptr;

    QIconButton *m_addPrinterButton = nullptr;
    QIconButton *m_editPrinterButton = nullptr;
    QIconButton *m_removePrinterButton = nullptr;

    QIconButton *m_printersActionButton = nullptr;
    QIconButton *m_themeActionButton = nullptr;
    QIconButton *m_systemActionButton = nullptr;

    QIconButton *m_acceptButton = nullptr;
    QIconButton *m_cancelButton = nullptr;
    QIconButton *m_resetButton = nullptr;
    QSpacerItem *m_footerSpacer = nullptr;

    QQuickView *m_viewer = nullptr;
    QWidget *m_viewerWidget = nullptr;

    Sheet *m_dialogSheet = nullptr;
    QDialog *m_requestedDialog = nullptr;
    QWizard *m_requestedWizard = nullptr;
};

#endif // SETTINGSPAGE_H
