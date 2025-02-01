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

namespace Ui {
class PrinterSettingsPage;
}

class PrinterSettingsPage : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterSettingsPage(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~PrinterSettingsPage();

public slots:
    void setStyleSheet(const QString &styleSheet);

protected slots:

private:
    Ui::PrinterSettingsPage *ui;

    QKlipperInstance *m_instance = nullptr;

    FileBrowser *m_configBrowser = nullptr;
    PrinterUpdateView *m_updateView = nullptr;
    PrinterAnnouncementView *m_announcementView = nullptr;
    PrinterServicesView *m_servicesView = nullptr;
    PrinterUsersView *m_usersView = nullptr;
    PrinterSystemView *m_systemView = nullptr;
};

#endif // PRINTERSETTINGSPAGE_H
