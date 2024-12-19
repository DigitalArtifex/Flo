#ifndef PRINTERPAGE_H
#define PRINTERPAGE_H

#include <QFrame>
#include <QMap>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include <QShowEvent>

#include <QKlipper/qklipper.h>

#include "widgets/extruder/extruderwidget.h"

#include "filebrowser/filebrowser.h"
#include "offline/printerofflinescreen.h"
#include "terminal/printerterminal.h"
#include "macros/gcodemacrodialog.h"

#include "widgets/printerbed/printerbedwidget.h"
#include "widgets/printerwebcam/printerwebcamwidget.h"
#include "widgets/temperature/temperaturewidget.h"
#include "../../ui/layouts/qflowlayout.h"

#include "widgets/toolhead/control/toolheadcontrolframe.h"

#include "settings/printersettingspage.h"
#include "bedmesh/bedmeshwidget.h"
#include "powerdevices/powerdeviceview.h"
#include "ledstrips/ledstripview.h"
#include "sensors/sensorview.h"

#include "ui/messagedialog.h"

#include "widgets/printerfan/printerfanwidget.h"

namespace Ui {
class PrinterPage;
}

class PrinterPage : public QFrame
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

    void setupAnimations();
    void setupIcons();

private slots:
    void onOverviewButtonClicked();
    void onSettingsButtonClicked();

    void on_homeToolheadButton_clicked();

    void on_posIncrementSelect_currentTextChanged(const QString &arg1);

    void on_xPosDecreaseButton_clicked();
    void on_xPosIncreaseButton_clicked();
    void on_yPosDecreaseButton_clicked();
    void on_yPosIncreaseButton_clicked();
    void on_zPosDecreaseButton_clicked();
    void on_zPosIncreaseButton_clicked();

    void on_xDestinationSpinBox_valueChanged(double arg1);

    void on_yDestinationSpinBox_valueChanged(double arg1);

    void on_zDestinationSpinBox_valueChanged(double arg1);

    void on_positionResetButton_clicked();

    void on_positionApplyButton_clicked();

    void printerStartupEvent();
    void printerDisconnectEvent();

    void onPrinterStatusChanged();
    void onPrinterStatusMessageChanged();
    void onPrinterEndingTimeChanged();
    void onToolHeadExtrudersChanged();
    void onToolheadPositionChanged();
    void onToolHeadDestinationChanged();
    void onSystemStateChanged();

    void onInstanceError(QKlipperInstance *instance, QKlipperError &error);

    void on_stackedWidget_currentChanged(int arg1);

    void on_settingsButton_clicked();

    void on_browserButton_clicked();

    void on_terminalButton_clicked();

    void on_goBackButton_clicked();

    void on_gcodeButton_clicked();

private:
    PowerDeviceView *m_powerDeviceView = nullptr;
    SensorView *m_sensorDeviceView = nullptr;
    LedStripView *m_ledDeviceView = nullptr;
    BedMeshWidget *m_bedMeshWidget = nullptr;
    QFrame *m_statusOverlayFrame = nullptr;
    QLabel *m_statusLabel = nullptr;

    CircularProgressBar *m_chamberTemperatureBar = nullptr;
    CircularProgressBar *m_printProgressBar = nullptr;

    PrinterTemperatureWidget *m_temperatureWidget = nullptr;

    FileBrowser *m_fileBrowser = nullptr;
    FileBrowser *m_overviewBrowser = nullptr;
    PrinterOfflineScreen *m_printerOfflineScreen = nullptr;
    PrinterTerminal *m_terminal = nullptr;

    bool xPosEditing = false;
    bool yPosEditing = false;
    bool zPosEditing = false;

    QMap<int, ExtruderWidget*> m_extruderMap;

    QKlipperPrinter *m_printer = nullptr;
    QKlipperInstance *m_instance = nullptr;

    PrinterBedWidget *m_printerBedWidget = nullptr;

    Ui::PrinterPage *ui;
    void setupUiClasses();

    QFlowLayout *m_centerLayout = nullptr;
    QSpacerItem *m_centerLayoutBottomSpacer = nullptr;

    PrinterWebcamWidget *m_webcamWidget = nullptr;

    ToolHeadControlFrame *m_toolheadControlFrame = nullptr;

    bool m_animating = false;

    QRegularExpression m_number_expression = QRegularExpression("\\d+");

    PrinterSettingsPage *m_printerSettingsPage = nullptr;
    PrinterFanWidget *m_printerFanWidget = nullptr;
};

#endif // PRINTERPAGE_H
