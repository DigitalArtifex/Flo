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
