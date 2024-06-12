#ifndef BEDMESHEMPTYFRAME_H
#define BEDMESHEMPTYFRAME_H

#include <QFrame>
#include "../../../../../../types/bed.h"

namespace Ui {
class BedMeshEmptyFrame;
}

class BedMeshEmptyFrame : public QFrame
{
    Q_OBJECT

public:
    explicit BedMeshEmptyFrame(Q3DPrintBed *bed, QWidget *parent = nullptr);
    ~BedMeshEmptyFrame();

protected slots:
    void on_toolhead_homing();
    void on_toolhead_homed();
    void on_toolhead_updated();

private slots:
    void on_homeButton_clicked();

    void on_calibrateButton_clicked();

private:
    Ui::BedMeshEmptyFrame *ui;
    Q3DPrintBed *_printerBed = nullptr;
};

#endif // BEDMESHEMPTYFRAME_H
