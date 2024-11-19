#include "bedmeshdata.h"

BedMeshData::BedMeshData(QKlipperPrintBed *bed, QObject *parent)
    : QObject{parent}
{
    qRegisterMetaType<QSurface3DSeries *>();
    m_printBed = bed;

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

            for(int col = 0; col < newColCount; col++)
            {
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
