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

private slots:
    void on_recalibrateButton_clicked();
    void on_printerBed_adjustmentScrewsUpdated(Q3DPrintBed *printBed);
    void on_loadingAnimation_finished();

    void on_printerBed_calibrating();
    void on_toolhead_homing();
    void on_toolhead_homed();

private:
    Ui::AdjustmentScrewFrame *ui;

    QMovie *_loadingGif = nullptr;
    QLabel *_loadingLabel = nullptr;

    QFrame *_loadingFrame = nullptr;
    QHBoxLayout *_loadingFrameLayout = nullptr;

    QWidgetAnimation *_loadingAnimation = nullptr;

    AdjustmentScrewEmptyFrame *_emptyAdjustmentScrewFrame = nullptr;

    Q3DPrintBed *_printerBed = nullptr;
};

#endif // ADJUSTMENTSCREWFRAME_H
