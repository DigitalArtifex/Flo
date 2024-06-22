#ifndef PRINTERBEDWIDGET_H
#define PRINTERBEDWIDGET_H

#include <QFrame>
#include <QSpacerItem>
#include <QPushButton>

#include "../../../../ui/circularprogressbar.h"
#include "../../../../types/bed.h"
#include "../../../../types/printer.h"

#include "adjustment/adjustmentscrewframe.h"

#include "bedmesh/bedmeshframe.h"

namespace Ui {
class PrinterBedWidget;
}

class PrinterBedWidget : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterBedWidget(Q3DPrintBed *printerBed, QWidget *parent = nullptr);
    ~PrinterBedWidget();

    Q3DPrintBed *printerBed() const;
    void setPrinterBed(Q3DPrintBed *printerBed);

    virtual void setPrintActionsEnabled(bool enabled);

    virtual void setIcons();

protected slots:
    void on_printerBed_update(Q3DPrintBed *printBed);
    void on_printerOnline(Printer* printer);

private:
    Ui::PrinterBedWidget *ui;

    CircularProgressBar *m_bedTemperatureBar = nullptr;
    Q3DPrintBed *m_printerBed = nullptr;

    AdjustmentScrewFrame* m_adjustmentScrewFrame = nullptr;

    BedMeshFrame *m_bedMeshFrame = nullptr;

    QSpacerItem *m_adjustmentScrewSpacer = nullptr;

    QPushButton *m_recalibrateButton = nullptr;
};

#endif // PRINTERBEDWIDGET_H
