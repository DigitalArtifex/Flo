#ifndef ADJUSTMENTSCREWFRAME_H
#define ADJUSTMENTSCREWFRAME_H

#include <QFrame>
#include <QMovie>
#include <QLabel>

#include "empty/adjustmentscrewemptyframe.h"
#include "item/adjustmentscrewitemframe.h"

#include <common/CardWidget/cardwidget.h>
#include <QKlipper/qklipper.h>

class AdjustmentScrewFrame : public CardWidget
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

    QMovie *m_loadingGif = nullptr;
    QLabel *m_loadingLabel = nullptr;

    QFrame *m_loadingFrame = nullptr;
    QHBoxLayout *m_loadingFrameLayout = nullptr;

    AdjustmentScrewEmptyFrame *m_emptyAdjustmentScrewFrame = nullptr;

    QKlipperPrintBed *m_printerBed = nullptr;
    QFrame *m_dataFrame = nullptr;
    QGridLayout *m_dataLayout = nullptr;
};

#endif // ADJUSTMENTSCREWFRAME_H
