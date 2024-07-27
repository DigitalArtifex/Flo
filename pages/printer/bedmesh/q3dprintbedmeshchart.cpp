#include "q3dprintbedmeshchart.h"

#include "system/settings.h"

Q3DPrintBedMeshChart::Q3DPrintBedMeshChart(QWidget *parent)
    : QWidget{parent}
{
    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    setLayout(m_layout);

    m_surface = new Q3DSurface;
    m_surface->setSurfaceType(Q3DSurface::OpenGLSurface);
    m_surface->setMinimumSize(QSize(200,200));

    m_surface->activeTheme()->setBackgroundColor(QColor::fromString(Settings::get("theme-graph-background-start").toString()));
    m_surface->activeTheme()->setGridLineColor(QColor::fromString(Settings::get("theme-graph-plot-foreground").toString()));
    m_surface->activeTheme()->setWindowColor(QColor::fromString(Settings::get("theme-graph-background-start").toString()));

    m_surface->axisZ()->setRange(-1.0f, 1.0f);
    m_surface->axisX()->setRange(0.0f, m_areaBoundaryX);
    m_surface->axisY()->setRange(0.0f, m_areaBoundaryY);

    m_surface->axisX()->setLabelAutoRotation(30);
    m_surface->axisY()->setLabelAutoRotation(90);
    m_surface->axisZ()->setLabelAutoRotation(30);

    m_surface->setHorizontalAspectRatio(1.0);
    m_surface->setAspectRatio(1.0);

    m_dataProxy = new QSurfaceDataProxy;
    m_series = new QSurface3DSeries(m_dataProxy);
    m_surface->addSeries(m_series);

    m_view = QWidget::createWindowContainer(m_surface, this, Qt::Widget);
    m_view->setProperty("class", QString("SubWidget"));

    m_layout->addWidget(m_view);
    m_surface->show();
}

Q3DPrintBedMeshChart::~Q3DPrintBedMeshChart()
{
}

void Q3DPrintBedMeshChart::setData(Q3DPrintBed::Mesh mesh)
{
    QSurfaceDataArray *data = new QSurfaceDataArray;
    data->reserve(mesh.matrix.count());

    m_surface->removeSeries(m_series);

    m_surface->axisZ()->setRange(-1.0f, 1.0f);
    m_surface->axisX()->setRange(0.0f, m_areaBoundaryX);
    m_surface->axisY()->setRange(0.0f, m_areaBoundaryY);
    m_surface->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetDirectlyAbove);

    for(int row = 0; row < mesh.matrix.count(); row++)
    {
        QList<qreal> dataPoints = mesh.matrix[row];
        QSurfaceDataRow *dataRow = new QSurfaceDataRow(dataPoints.count());

        for(int col = 0; col < dataPoints.count(); col++)
        {
            qreal x = (col * (m_areaBoundaryX / dataPoints.count()));
            qreal y = (row * (m_areaBoundaryY / mesh.matrix.count()));
            qreal z = dataPoints[col];

            qDebug() << "Probe point: " << row << col << x << y << z;

            (*dataRow)[col].setPosition(QVector3D(x,y,z));
        }

        *data << dataRow;
    }

    m_dataProxy->resetArray(data);
    m_surface->addSeries(m_series);
}

void Q3DPrintBedMeshChart::setAreaBoundaries(qreal x, qreal y)
{
    m_areaBoundaryX = x;
    m_areaBoundaryY = y;
}

void Q3DPrintBedMeshChart::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if(m_surface)
        m_surface->resize(size());
}

void Q3DPrintBedMeshChart::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
}

void Q3DPrintBedMeshChart::hideEvent(QHideEvent *event)
{
    QWidget::hideEvent(event);
}
