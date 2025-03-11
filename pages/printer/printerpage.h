/*
* Flo :: PrinterPage
*
* Provides an overview of a single printer
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

#ifndef PRINTERPAGE_H
#define PRINTERPAGE_H

#include <QFrame>
#include <QMap>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include <QShowEvent>

#include <QKlipper/qklipper.h>

#include "pages/printer/widgets/overview/printeroverviewwidget.h"
#include "widgets/extruder/extruderwidget.h"

#include "filebrowser/filebrowser.h"
#include "offline/printerofflinescreen.h"
#include "terminal/printerterminal.h"
#include "macros/gcodemacrodialog.h"

#include "widgets/printerbed/printerbedwidget.h"
#include "widgets/printerwebcam/printerwebcamwidget.h"
#include "widgets/toolhead/toolheadwidget.h"
#include "../../ui/layouts/qflowlayout.h"

#include "widgets/toolhead/control/toolheadcontrolframe.h"

#include "settings/printersettingspage.h"
#include "bedmesh/bedmeshwidget.h"
#include "widgets/powerdevices/powerdeviceview.h"
#include "widgets/ledstrips/ledstripview.h"
#include "widgets/sensors/sensorview.h"

#include "dialogs/MessageDialog/messagedialog.h"

#include "widgets/printerfan/printerfanwidget.h"

#include "printing/printingpage.h"

#include "dialogs/InputShaper/inputshaperwizard.h"
#include "dialogs/ZOffsetWizard/zoffsetwizard.h"

#include "widgets/chamber/printerchamberwidget.h"
#include "3rdparty/QtSheet/sheet.h"

#include "updating/printerupdatingscreen.h"

namespace Ui {
class PrinterPage;
}

class PrinterPage : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool isAnimating READ animating WRITE setAnimating NOTIFY animatingChanged FINAL)
public:
    explicit PrinterPage(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~PrinterPage();
    void addExtruder(QKlipperExtruder *extruder, QString name = QString("Extruder"));

    QKlipperPrinter *printer() const;
    void setPrinter(QKlipperPrinter *printer);

    bool animating() const;
    void setAnimating(bool animating);

signals:
    void animatingChanged(bool);

protected slots:
    virtual void setPrintActionsEnabled(bool enabled);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void changeEvent(QEvent *event) override;
    virtual void showEvent(QShowEvent *event) override;

    void setupAnimations();
    void setupIcons();

private slots:
    void onOverviewButtonClicked();
    void onSettingsButtonClicked();
    void onBedMeshButtonClicked();

    void on_homeToolheadButton_clicked();

    void onInstanceDisconnected(QKlipperInstance* instance);
    void createWebcamWidget();
    void deleteWebcamWidget();

    void onPrinterStatusChanged();
    void onPrinterStatusMessageChanged();
    void onPrinterEndingTimeChanged();
    void onToolHeadExtrudersChanged();
    void onSystemStateChanged();
    void onPrinterHasChamberChanged();
    void onPrinterPowerDevicesChanged();
    void onPrinterLedStripsChanged();
    void onPrinterSensorListChanged();

    void onInstanceError(QKlipperInstance *instance, QKlipperError &error);

    void on_settingsButton_clicked();

    void on_browserButton_clicked();

    void on_terminalButton_clicked();

    void on_goBackButton_clicked();

    void on_gcodeButton_clicked();

    void on_restartButton_clicked();

    void on_restartKlipperButton_clicked();

    void on_toolButton_clicked();
    void onPageClosed(Page *page);
    void onDialogRequested(QDialog *dialog);
    void onDialogFinished(int returnCode);
    void onWizardRequested(QWizard *wizard);
    void onWizardFinished(int returnCode);

private:
    //Used by dialogRequested
    int m_requestedWizardReturnIndex = 0;
    QDialog *m_requestedDialog = nullptr;
    QWizard *m_requestedWizard = nullptr;

    PowerDeviceView *m_powerDeviceView = nullptr;
    SensorView *m_sensorDeviceView = nullptr;
    LedStripView *m_ledDeviceView = nullptr;
    BedMeshWidget *m_bedMeshWidget = nullptr;
    PrinterTerminal *m_terminal = nullptr;
    PrinterChamberWidget *m_chamberWidget = nullptr;
    ToolheadWidget *m_toolheadWidget = nullptr;
    QFrame *m_statusOverlayFrame = nullptr;
    QLabel *m_statusLabel = nullptr;

    QGaugeWidget *m_printProgressBar = nullptr;

    PrinterOverviewWidget *m_overviewWidget = nullptr;

    PrintingPage *m_printingPage = nullptr;
    FileBrowser *m_fileBrowser = nullptr;
    FileBrowser *m_overviewBrowser = nullptr;
    PrinterOfflineScreen *m_printerOfflineScreen = nullptr;
    PrinterUpdatingScreen *m_updatingScreen = nullptr;

    QMap<int, ExtruderWidget*> m_extruderMap;

    QKlipperPrinter *m_printer = nullptr;
    QKlipperInstance *m_instance = nullptr;

    PrinterBedWidget *m_printerBedWidget = nullptr;

    Ui::PrinterPage *ui;
    void setupUiClasses();

    QFlowLayout *m_centerLayout = nullptr;
    QSpacerItem *m_centerLayoutBottomSpacer = nullptr;

    PrinterWebcamWidget *m_webcamWidget = nullptr;

    bool m_animating = false;

    PrinterSettingsPage *m_printerSettingsPage = nullptr;
    PrinterFanWidget *m_printerFanWidget = nullptr;

    Sheet *m_dialogSheet = nullptr;
};

#endif // PRINTERPAGE_H
