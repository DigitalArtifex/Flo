#ifndef ADJUSTMENTSCREWITEMFRAME_H
#define ADJUSTMENTSCREWITEMFRAME_H

#include <QFrame>
#include <QPixmap>

#include "../../../../../../types/bed.h"

namespace Ui {
class AdjustmentScrewItemFrame;
}

class AdjustmentScrewItemFrame : public QFrame
{
    Q_OBJECT

public:
    explicit AdjustmentScrewItemFrame(QWidget *parent = nullptr);
    ~AdjustmentScrewItemFrame();

    Q3DPrintBed::AdjustmentScrew *adjustmentScrew() const;
    void setAdjustmentScrew(Q3DPrintBed::AdjustmentScrew *adjustmentScrew);

private:
    Ui::AdjustmentScrewItemFrame *ui;

    //Q3DPrintBed::AdjustmentScrew *_adjustmentScrew = nullptr;
};

#endif // ADJUSTMENTSCREWITEMFRAME_H
