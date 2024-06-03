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
    void on_printBed_updated(Q3DPrintBed *bed);

private slots:
    void on_homeButton_clicked();

private:
    Ui::BedMeshEmptyFrame *ui;
    Q3DPrintBed *_printBed = nullptr;
};

#endif // BEDMESHEMPTYFRAME_H
