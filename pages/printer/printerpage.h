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

#include "widgets/printerbed/printerbedwidget.h"
#include "widgets/printerwebcam/printerwebcamwidget.h"
#include "widgets/temperature/temperaturewidget.h"
#include "../../ui/layouts/qflowlayout.h"

#include "widgets/toolhead/control/toolheadcontrolframe.h"

#include "settings/printersettingspage.h"
#include "bedmesh/bedmeshwidget.h"

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

    virtual void setStyleSheet(QString styleSheet);
    void setIcons();

    QKlipperPrinter *printer() const;
    void setPrinter(QKlipperPrinter *printer);

    bool animating() const;
    void setAnimating(bool animating);

signals:
    void animatingChanged(bool);

protected slots:
    virtual void setPrintActionsEnabled(bool enabled);

protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);
    void setupAnimations();

    void showFansWidget();
    void hideFansWidget();
    void showPositionWidget();
    void hidePositionWidget();
    void showZOffsetWidget();
    void hideZOffsetWidget();
    void showWebcamWidget();
    void hideWebcamWidget();

private slots:
    void on_xPosDecreaseButton_clicked();
    void terminalButtonClickEvent();
    void overviewButtonClickEvent();
    void fileBrowserButtonClickEvent();
    void bedMeshViewerButtonClickEvent();
    void settingsButtonClickEvent();

    void on_homeToolheadButton_clicked();

    void on_posIncrementSelect_currentTextChanged(const QString &arg1);

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
    void onPrinterFansChanged();
    void onPrinterEndingTimeChanged();
    void onToolHeadExtrudersChanged();
    void onToolheadPositionChanged();
    void onToolHeadDestinationChanged();
    void onToolHeadPartsFanSpeedChanged();

    void onInstanceError(QKlipperInstance *instance, QKlipperError &error);

    void onFansAnimationFinished();
    void onPositionAnimationFinished();
    void onZOffsetAnimationFinished();
    void onWebcamAnimationFinished();

    void onFansToggleButtonClicked(bool toggled);
    void onPositionToggleButtonClicked(bool toggled);
    void onZOffsetToggleButtonClicked(bool toggled);
    void onWebcamToggleButtonClicked(bool toggled);

    void on_restartButton_clicked();

private:
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

    void addFanLabels(QKlipperFan *fan, QString name);

    QFlowLayout *m_centerLayout = nullptr;
    QSpacerItem *m_centerLayoutBottomSpacer = nullptr;

    PrinterWebcamWidget *m_webcamWidget = nullptr;

    ToolHeadControlFrame *m_toolheadControlFrame = nullptr;

    bool m_animating = false;

    QRegularExpression m_number_expression = QRegularExpression("\\d+");

    QIconButton *m_overviewButton = nullptr;
    QIconButton *m_terminalButton = nullptr;
    QIconButton *m_fileBrowserButton = nullptr;
    QIconButton *m_bedMeshViewerButton = nullptr;
    QIconButton *m_settingsButton = nullptr;
    QSpacerItem *m_buttonSpacer = nullptr;

    PrinterSettingsPage *m_printerSettingsPage = nullptr;

    //Fan widget animations
    QPropertyAnimation *m_fansWidgetAnimation = nullptr;
    QPropertyAnimation *m_fansFrameAnimation = nullptr;
    QParallelAnimationGroup *m_fansAnimationGroup = nullptr;

    bool m_fansShown = true;

    qint32 m_fansWidgetHeight = 0;
    qint32 m_fansFrameHeight = 0;

    //Position widget animations
    QPropertyAnimation *m_positionWidgetAnimation = nullptr;
    QPropertyAnimation *m_positionFrameAnimation = nullptr;
    QParallelAnimationGroup *m_positionAnimationGroup = nullptr;

    bool m_positionShown = true;

    qint32 m_positionFrameHeight = 0;
    qint32 m_positionWidgetHeight = 0;

    //Z Offset Widget Animations
    QPropertyAnimation *m_zOffsetWidgetAnimation = nullptr;
    QPropertyAnimation *m_zOffsetFrameAnimation = nullptr;
    QParallelAnimationGroup *m_zOffsetAnimationGroup = nullptr;

    bool m_zOffsetShown = true;

    qint32 m_zOffsetFrameHeight = 0;
    qint32 m_zOffsetWidgetHeight = 0;

    //Webcam Widget Animations
    QPropertyAnimation *m_webcamWidgetAnimation = nullptr;
    QPropertyAnimation *m_webcamFrameAnimation = nullptr;
    QParallelAnimationGroup *m_webcamAnimationGroup = nullptr;

    bool m_webcamShown = true;

    qint32 m_webcamFrameHeight = 0;
    qint32 m_webcamWidgetHeight = 0;

    //Status Widget Animations
    QPropertyAnimation *m_statusWidgetAnimation = nullptr;
    QPropertyAnimation *m_statusFrameAnimation = nullptr;
    QParallelAnimationGroup *m_statusAnimationGroup = nullptr;

    bool m_statusShown = true;

    qint32 m_statusFrameHeight = 0;
    qint32 m_statusWidgetHeight = 0;
};

#endif // PRINTERPAGE_H
