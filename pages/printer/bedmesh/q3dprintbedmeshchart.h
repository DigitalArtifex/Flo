#ifndef Q3DPRINTBEDMESHCHART_H
#define Q3DPRINTBEDMESHCHART_H

#include <QWidget>
#include <QGridLayout>
#include <Q3DSurface>
#include <QSurface3DSeries>
#include <QSurfaceDataArray>
#include <QSurfaceDataProxy>
#include <QSurfaceDataRow>
#include <QChartView>

#include "types/position.h"
#include "types/bed.h"

class Q3DPrintBedMeshChart : public QWidget
{
    Q_OBJECT
public:
    explicit Q3DPrintBedMeshChart(QWidget *parent = nullptr);
    ~Q3DPrintBedMeshChart();

    virtual void setData(Q3DPrintBed::Mesh data);
    virtual void setAreaBoundaries(qreal x, qreal y);

protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);

signals:

private:
    Q3DSurface *m_surface = nullptr;
    QSurfaceDataProxy *m_dataProxy = nullptr;
    QSurface3DSeries *m_series = nullptr;
    QWidget *m_view = nullptr;

    qreal m_areaBoundaryX = 220.0;
    qreal m_areaBoundaryY = 220.0;

    QGridLayout *m_layout = nullptr;
};

#endif // Q3DPRINTBEDMESHCHART_H
