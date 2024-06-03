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
    void on_printBed_updated(Q3DPrintBed *bed);
    void on_loadingAnimation_finished();

    void on_printerBed_calibrating();
    void on_toolhead_homing();
    void on_toolhead_homed();

private:
    Ui::BedMeshFrame *ui;

    QGridLayout *_layout = nullptr;

    BedMeshEmptyFrame *_emptyFrame = nullptr;

    QMovie *_loadingGif = nullptr;
    QLabel *_loadingLabel = nullptr;

    QFrame *_loadingFrame = nullptr;
    QHBoxLayout *_loadingFrameLayout = nullptr;

    QWidgetAnimation *_loadingAnimation = nullptr;

    Q3DPrintBed *_printerBed;
};

#endif // BEDMESHFRAME_H
