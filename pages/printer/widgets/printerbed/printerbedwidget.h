#ifndef PRINTERBEDWIDGET_H
#define PRINTERBEDWIDGET_H

#include <QFrame>
#include <QSpacerItem>
#include <QPushButton>
#include <QPropertyAnimation>

#include "../../../../ui/circularprogressbar.h"
#include <QKlipper/qklipper.h>

namespace Ui {
class PrinterBedWidget;
}

class PrinterBedWidget : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterBedWidget(QKlipperPrintBed *printerBed, QWidget *parent = nullptr);
    ~PrinterBedWidget();

    QKlipperPrintBed *printerBed() const;
    void setPrinterBed(QKlipperPrintBed *printerBed);

    virtual void setPrintActionsEnabled(bool enabled);

    virtual void setIcons();

public slots:
    void setStyleSheet(const QString &styleSheet);

protected slots:
    void onPrintbedCurrentTempChanged();
    void onPrintbedTargetTempChanged();
    void onPrintbedPowerChanged();
    virtual void resizeEvent(QResizeEvent *event);

private slots:
    void on_applyButton_clicked();
    void on_resetButton_clicked();
    void on_targetTempSpinBox_valueChanged(double arg1);

    void onToggleToolsButtonClicked(bool toggled);
    void onToggleBedMeshButtonClicked(bool toggled);
    void showAdjustmentScrews();
    void hideAdjustmentScrews();
    void showBedMesh();
    void hideBedMesh();
    void onToolsWidgetAnimationFinished();
    void onBedMeshAnimationFinished();
    void setupAnimations();

private:
    Ui::PrinterBedWidget *ui;

    QPropertyAnimation *m_adjustmentScrewWidgetAnimation = nullptr;
    QPropertyAnimation *m_adjustmentScrewFrameAnimation = nullptr;

    QPropertyAnimation *m_bedMeshWidgetAnimation = nullptr;
    QPropertyAnimation *m_bedMeshFrameAnimation = nullptr;

    bool m_toolsShown = true;
    bool m_bedMeshShown = true;

    qint32 m_bedMeshFrameHeight = 0;
    qint32 m_bedMeshWidgetHeight = 0;
    qint32 m_adjustmentScrewFrameHeight = 0;
    qint32 m_adjustmentScrewWidgetHeight = 0;

    CircularProgressBar *m_bedTemperatureBar = nullptr;
    QKlipperPrintBed *m_printerBed = nullptr;

    //BedMeshFrame *m_bedMeshFrame = nullptr;

    QSpacerItem *m_adjustmentScrewSpacer = nullptr;

    QPushButton *m_recalibrateButton = nullptr;

    bool m_targetTempEdited = false;
};

#endif // PRINTERBEDWIDGET_H
