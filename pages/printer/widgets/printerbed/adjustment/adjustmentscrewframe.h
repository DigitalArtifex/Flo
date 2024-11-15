#ifndef ADJUSTMENTSCREWFRAME_H
#define ADJUSTMENTSCREWFRAME_H

#include <QFrame>
#include <QMovie>
#include <QLabel>

#include "empty/adjustmentscrewemptyframe.h"
#include "item/adjustmentscrewitemframe.h"

#include <ui/qanimatedwidget.h>

#include <QKlipper/qklipper.h>

namespace Ui {
class AdjustmentScrewFrame;
}

class AdjustmentScrewFrame : public QFrame
{
    Q_OBJECT

public:
    explicit AdjustmentScrewFrame(QKlipperPrintBed *bed, QWidget *parent = nullptr);
    ~AdjustmentScrewFrame();

    void showLoadingScreen();
    void hideLoadingScreen();

public slots:
    void setStyleSheet(const QString &styleSheet);
    void setupIcons();

signals:

private slots:
    void on_recalibrateButton_clicked();
    void on_loadingAnimation_finished();

    void onPrinterBedCalibrating();
    void onPrinterBedCalibratingFinished();
    void onAdjustmentScrewsChanged();

    void onToolheadHoming();
    void onToolheadHomed();

    void clearLayout();

private:
    Ui::AdjustmentScrewFrame *ui;

    QMovie *m_loadingGif = nullptr;
    QLabel *m_loadingLabel = nullptr;

    QFrame *m_loadingFrame = nullptr;
    QHBoxLayout *m_loadingFrameLayout = nullptr;

    QWidgetAnimation *m_loadingAnimation = nullptr;

    AdjustmentScrewEmptyFrame *m_emptyAdjustmentScrewFrame = nullptr;

    QKlipperPrintBed *m_printerBed = nullptr;
};

#endif // ADJUSTMENTSCREWFRAME_H
