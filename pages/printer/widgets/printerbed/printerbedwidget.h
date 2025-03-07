#ifndef PRINTERBEDWIDGET_H
#define PRINTERBEDWIDGET_H

#include <QFrame>
#include <QSpacerItem>
#include <QPushButton>
#include <QPropertyAnimation>

#include <QtDAWidgets/qgaugewidget.h>
#include <QKlipper/qklipper.h>
#include "../../bedmesh/health/bedmeshhealthcard.h"

#include "printerbedinfodialog.h"
#include "printerbedtoolsdialog.h"
#include "ui/LineGraphWidget/linegraphwidget.h"
#include <pages/printer/bedmesh/bedmeshwidget.h>

#include <ui/QIconButton/qiconbutton.h>
#include <QtDAWidgets/qthrobberwidget.h>

#include <dialogs/PidDialog/piddialog.h>

namespace Ui {
class PrinterBedWidget;
}

class PrinterPage;

class PrinterBedWidget : public QFrame
{
    Q_OBJECT
        friend PrinterPage;
public:
    explicit PrinterBedWidget(QKlipperPrintBed *printerBed, QWidget *parent = nullptr);
    ~PrinterBedWidget();

    QKlipperPrintBed *printerBed() const;
    void setPrinterBed(QKlipperPrintBed *printerBed);

    void setPrintActionsEnabled(bool enabled);
    void setupIcons();
    void setStyleSheet(const QString &styleSheet);

    QIconButton *bedMeshViewerButton();

public slots:

signals:
    void dialogRequested(QDialog *);

protected slots:
    void onPrintbedCurrentTempChanged();
    void onPrintbedTargetTempChanged();
    void onPrintbedPowerChanged();
    void onToolheadHomedChanged();
    void showThrobber();
    void hideThrobber();
    virtual void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_applyButton_clicked();
    void on_resetButton_clicked();
    void on_targetTempSpinBox_valueChanged(double arg1);

    void onSettingsButtonClicked();

    void onViewBedMeshButtonClicked();

    void onCalibrateBedMeshButtonClicked();

    void onCalibrateScrewsButtonClicked();
    void onPidTuneButtonClicked();

    void onBedMeshDataChanged();

    void onPidDialogFinished(int returnCode);
    void onSettingsDialogFinished(int returnCode);

private:
    LineGraphWidget *m_temperatureGraph = nullptr;

    Ui::PrinterBedWidget *ui;

    QGaugeWidget *m_bedTemperatureBar = nullptr;
    QGaugeWidget *m_bedPowerProgressBar = nullptr;
    QGaugeWidget *m_bedHealthProgressBar = nullptr;
    QKlipperPrintBed *m_printerBed = nullptr;

    ProbedMeshFrame *m_bedMeshFrame = nullptr;

    QSpacerItem *m_adjustmentScrewSpacer = nullptr;

    QIconButton *m_pidButton = nullptr;
    QIconButton *m_calibrateMeshButton = nullptr;
    QIconButton *m_calibrateScrewsButton = nullptr;
    QIconButton *m_meshViewerButton = nullptr;
    QIconButton *m_bedInfoButton = nullptr;

    bool m_targetTempEdited = false;
    BedMeshData *m_bedMeshData = nullptr;

    QFrame *m_throbberFrame = nullptr;
    QThrobberWidget *m_throbber = nullptr;

    PidDialog *m_pidDialog = nullptr;
    PrinterBedInfoDialog *m_settingsDialog = nullptr;
};

#endif // PRINTERBEDWIDGET_H
