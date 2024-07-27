#ifndef Q3DPRINTBEDMESHVIEWER_H
#define Q3DPRINTBEDMESHVIEWER_H

#include <QWidget>
#include <QGridLayout>

#include "q3dprintbedmeshchart.h"
#include "types/bed.h"
#include "types/printer.h"

class Q3DPrintBedMeshViewer : public QWidget
{
    Q_OBJECT
public:
    explicit Q3DPrintBedMeshViewer(Q3DPrintBed *bed, QWidget *parent = nullptr);
    ~Q3DPrintBedMeshViewer();

    void setPrintBed(Q3DPrintBed *printBed);

signals:

protected slots:
    void printBedMeshCalibratedEvent();

private:
    Q3DPrintBedMeshChart *m_chart = nullptr;
    Q3DPrintBed *m_printBed = nullptr;
    QGridLayout *m_layout = nullptr;
};

#endif // Q3DPRINTBEDMESHVIEWER_H
