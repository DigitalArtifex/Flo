/*
* Flo :: PrinterSettingsPage
*
* Provides an overview of the system and configuration
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

#ifndef PRINTERSETTINGSPAGE_H
#define PRINTERSETTINGSPAGE_H

#include <QFrame>
#include <QStyle>

#include "pages/printer/filebrowser/filebrowser.h"

#include <QKlipper/qklipper.h>

#include "updates/printerupdateview.h"
#include "announcements/printerannouncementview.h"
#include "services/printerservicesview.h"
#include "users/printerusersview.h"
#include "system/printersystemview.h"
#include "ui/QIconButton/qiconbutton.h"

namespace Ui {
class PrinterSettingsPage;
}

class PrinterSettingsPage : public Page
{
    Q_OBJECT

public:
    explicit PrinterSettingsPage(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~PrinterSettingsPage();

public slots:

protected slots:
    void onDialogRequested(QDialog *dialog);
    void onWizardRequested(QWizard *wizard);

protected:
    void setIcons();
    virtual void changeEvent(QEvent *event) override;

private slots:
    void on_restartButton_clicked();
    void on_restartFirmwareButton_clicked();

private:
    Ui::PrinterSettingsPage *ui;

    QKlipperInstance *m_instance = nullptr;

    FileBrowser *m_configBrowser = nullptr;
    PrinterUpdateView *m_updateView = nullptr;
    PrinterAnnouncementView *m_announcementView = nullptr;
    PrinterServicesView *m_servicesView = nullptr;
    PrinterUsersView *m_usersView = nullptr;
    PrinterSystemView *m_systemView = nullptr;

    QIconButton *m_closeButton = nullptr;
};

#endif // PRINTERSETTINGSPAGE_H
