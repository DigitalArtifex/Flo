#include "bedmeshdata.h"

BedMeshData::BedMeshData(QKlipperPrintBed *bed, QObject *parent)
    : QObject{parent}
{
    qRegisterMetaType<QSurface3DSeries *>();
    m_printBed = bed;
    onBedMeshMatrixChanged();
    connect(m_printBed->bedMesh(), SIGNAL(matrixChanged()), this, SLOT(onBedMeshMatrixChanged()));
}

BedMeshData::~BedMeshData()
{
    m_data.clear();
}

void BedMeshData::update(QSurface3DSeries *series)
{
    series->dataProxy()->resetArray(m_data);
}

void BedMeshData::onBedMeshMatrixChanged()
{
    QSurfaceDataArray newData;

    QVertexTable matrix = m_printBed->bedMesh()->verticies();

    if(!matrix.isEmpty())
    {
        int newRowCount = matrix.count();
        int newColCount = matrix[0].count();

        newData.reserve(newRowCount);

        for(int row = 0; row < newRowCount; row++)
        {
            newData.insert(row, QSurfaceDataRow());

            QSurfaceDataRow &rowData = newData[row];
            rowData.reserve(newColCount);

            for(int col = 0; col < matrix[0].count(); col++)
            {
                if((col == 0 && row == 0))
                {
                    setMaximum(matrix[row][col].z());
                    setMinimum(matrix[row][col].z());
                }
                else if(matrix[row][col].z() > m_minimum)
                    setMaximum(matrix[row][col].z());
                else if(matrix[row][col].z() < m_minimum)
                    setMinimum(matrix[row][col].z());

                QVector3D converted;
                converted.setX(matrix[row][col].x());
                converted.setY(matrix[row][col].z());
                converted.setZ(matrix[row][col].y());

                rowData.insert(col, QSurfaceDataItem(converted));
            }
        }
    }

    setData(newData);
}

qreal BedMeshData::maximum() const
{
    return m_maximum;
}

void BedMeshData::setMaximum(qreal maximum)
{
    if (qFuzzyCompare(m_maximum, maximum))
        return;

    m_maximum = maximum;
    emit maximumChanged();
}

qreal BedMeshData::minimum() const
{
    return m_minimum;
}

void BedMeshData::setMinimum(qreal minimum)
{
    if (qFuzzyCompare(m_minimum, minimum))
        return;

    m_minimum = minimum;
    emit minimumChanged();
}

QSurfaceDataArray BedMeshData::data() const
{
    return m_data;
}

void BedMeshData::setData(const QSurfaceDataArray &data)
{
    m_data.clear();

    m_data = data;
    emit dataChanged();
}
