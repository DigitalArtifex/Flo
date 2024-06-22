#ifndef ADJUSTMENTSCREWFRAME_H
#define ADJUSTMENTSCREWFRAME_H

#include <QFrame>
#include <QMovie>
#include <QLabel>

#include "empty/adjustmentscrewemptyframe.h"
#include "item/adjustmentscrewitemframe.h"

#include "../../../../../types/bed.h"
#include "../../../../../types/printer.h"

namespace Ui {
class AdjustmentScrewFrame;
}

class AdjustmentScrewFrame : public QFrame
{
    Q_OBJECT

public:
    explicit AdjustmentScrewFrame(Q3DPrintBed *bed, QWidget *parent = nullptr);
    ~AdjustmentScrewFrame();

    void showLoadingScreen();
    void hideLoadingScreen();

signals:

private slots:
    void on_recalibrateButton_clicked();
    void on_printerBed_adjustmentScrewsCalibrated();
    void on_printerBed_adjustmentScrewsCalibrating();
    void on_loadingAnimation_finished();

    void on_printerBed_calibrating();
    void on_toolhead_homing();
    void on_toolhead_homed();

private:
    Ui::AdjustmentScrewFrame *ui;

    QMovie *m_loadingGif = nullptr;
    QLabel *m_loadingLabel = nullptr;

    QFrame *m_loadingFrame = nullptr;
    QHBoxLayout *m_loadingFrameLayout = nullptr;

    QWidgetAnimation *m_loadingAnimation = nullptr;

    AdjustmentScrewEmptyFrame *m_emptyAdjustmentScrewFrame = nullptr;

    Q3DPrintBed *m_printerBed = nullptr;
};

#endif // ADJUSTMENTSCREWFRAME_H
