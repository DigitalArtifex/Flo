#include "q3dprintbedmeshviewer.h"

Q3DPrintBedMeshViewer::Q3DPrintBedMeshViewer(Q3DPrintBed *bed, QWidget *parent)
    : QWidget{parent}
{
    m_chart = new Q3DPrintBedMeshChart(this);
    m_chart->setData(bed->bedMesh());

    m_layout = new QGridLayout(this);
    m_layout->addWidget(m_chart);

    m_printBed = bed;
    connect(m_printBed, SIGNAL(bedMeshCalibrated()), this, SLOT(printBedMeshCalibratedEvent()));
}

Q3DPrintBedMeshViewer::~Q3DPrintBedMeshViewer()
{
    if(m_chart)
        m_chart->deleteLater();
}

void Q3DPrintBedMeshViewer::setPrintBed(Q3DPrintBed *printBed)
{
    m_printBed = printBed;
    connect(m_printBed, SIGNAL(bedMeshCalibrated()), this, SLOT(printBedMeshCalibratedEvent()));
}

void Q3DPrintBedMeshViewer::printBedMeshCalibratedEvent()
{
    //get the total bed area to set the boundaries of the chart
    Toolhead *toolhead = m_printBed->printer()->toolhead();
    qreal x = toolhead->maxPosition().x() - toolhead->minPosition().x();
    qreal y = toolhead->maxPosition().y() - toolhead->minPosition().y();

    m_chart->setAreaBoundaries(x, y);
    m_chart->setData(m_printBed->bedMesh());
}
