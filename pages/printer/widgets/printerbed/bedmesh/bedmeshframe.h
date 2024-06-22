#ifndef BEDMESHFRAME_H
#define BEDMESHFRAME_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QMovie>

#include "../../../../../types/bed.h"
#include "../../../../../ui/qwidgetanimation.h"

#include "empty/bedmeshemptyframe.h"
#include "item/bedmeshitemframe.h"

namespace Ui {
class BedMeshFrame;
}

class BedMeshFrame : public QFrame
{
    Q_OBJECT
public:
    explicit BedMeshFrame(Q3DPrintBed *bed, QWidget *parent = nullptr);
    ~BedMeshFrame();

    void showLoadingScreen();
    void hideLoadingScreen();

protected:
    void setupIcons();
    void setupUiClasses();

protected slots:
    void on_loadingAnimation_finished();

    void on_printerBed_calibrating();
    void on_toolhead_homing();
    void on_toolhead_homed();

    void on_printerBed_bedMeshCalibrated();
    void on_printerBed_bedMeshCalibrating();

private:
    Ui::BedMeshFrame *ui;

    QGridLayout *m_layout = nullptr;

    BedMeshEmptyFrame *m_emptyFrame = nullptr;

    QMovie *m_loadingGif = nullptr;
    QLabel *m_loadingLabel = nullptr;

    QFrame *m_loadingFrame = nullptr;
    QHBoxLayout *m_loadingFrameLayout = nullptr;

    QWidgetAnimation *m_loadingAnimation = nullptr;

    Q3DPrintBed *m_printerBed;
};

#endif // BEDMESHFRAME_H
