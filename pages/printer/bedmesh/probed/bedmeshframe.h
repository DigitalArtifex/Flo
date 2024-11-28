#ifndef BEDMESHFRAME_H
#define BEDMESHFRAME_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QMovie>

#include <QKlipper/qklipper.h>
#include "ui/qwidgetanimation.h"
#include "ui/common/cardwidget/cardwidget.h"

#include "empty/bedmeshemptyframe.h"
#include "item/bedmeshitemframe.h"

class BedMeshFrame : public CardWidget
{
    Q_OBJECT
public:
    explicit BedMeshFrame(QKlipperPrintBed *bed, QWidget *parent = nullptr);
    ~BedMeshFrame();

    void showLoadingScreen();
    void hideLoadingScreen();

public slots:
    void setStyleSheet(const QString &styleSheet);

protected:
    void setupIcons();
    void setupUiClasses();

protected slots:
    void on_loadingAnimation_finished();

    void onToolheadHoming();
    void onToolheadHomed();

    void onBedMeshCalibratingFinished();
    void onBedMeshCalibrating();
    void onMatrixChanged();

    void clearLayout();

private:
    QWidget *m_centralWidget = nullptr;
    QGridLayout *m_centralLayout = nullptr;

    BedMeshEmptyFrame *m_emptyFrame = nullptr;

    QMovie *m_loadingGif = nullptr;
    QLabel *m_loadingLabel = nullptr;

    QFrame *m_loadingFrame = nullptr;
    QHBoxLayout *m_loadingFrameLayout = nullptr;

    QWidgetAnimation *m_loadingAnimation = nullptr;

    QKlipperPrintBed *m_printerBed;

    bool m_calibrating = false;
};

#endif // BEDMESHFRAME_H
