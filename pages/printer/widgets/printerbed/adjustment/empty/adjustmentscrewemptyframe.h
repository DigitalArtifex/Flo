#ifndef ADJUSTMENTSCREWEMPTYFRAME_H
#define ADJUSTMENTSCREWEMPTYFRAME_H

#include <QFrame>
#include <QPixmap>
#include <QLabel>
#include <QMovie>
#include <QSpacerItem>
#include <QHBoxLayout>

#include <QStyle>

#include "../../../../../../ui/qwidgetanimation.h"
#include "../../../../../../types/bed.h"

namespace Ui {
class AdjustmentScrewEmptyFrame;
}

class AdjustmentScrewEmptyFrame : public QFrame
{
    Q_OBJECT

public:
    explicit AdjustmentScrewEmptyFrame(Q3DPrintBed *bed, QWidget *parent = nullptr);
    ~AdjustmentScrewEmptyFrame();

    virtual void setStyleSheet(QString &styleSheet);
    virtual void setCalibrationEnabled(bool enabled);

signals:
    void calibrating();

private slots:
    void on_calibrateButton_clicked();
    void on_toolhead_updated();
    void on_toolhead_homing();
    void on_toolhead_homed();

    void on_homeButton_clicked();

private:
    Ui::AdjustmentScrewEmptyFrame *ui;

    QSpacerItem *m_rightSpacer = nullptr;
    QSpacerItem *m_topSpacer = nullptr;
    QSpacerItem *m_leftSpacer = nullptr;
    QSpacerItem *m_bottomSpacer = nullptr;

    Q3DPrintBed *m_printerBed = nullptr;
};

#endif // ADJUSTMENTSCREWEMPTYFRAME_H
