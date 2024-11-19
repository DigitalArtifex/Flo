#ifndef BEDMESHDATA_H
#define BEDMESHDATA_H

#include <QObject>
#include <QQmlEngine>
#include <QtGraphs/qsurface3dseries.h>
#include <QKlipper/qklipper.h>
#include <QAbstractItemModel>

class BedMeshData : public QObject
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit BedMeshData(QKlipperPrintBed *bed, QObject *parent = nullptr);
        ~BedMeshData() override;

        Q_INVOKABLE void update(QSurface3DSeries *series);

        QSurfaceDataArray data() const;

    public slots:

        void setData(const QSurfaceDataArray &data);

    protected slots:
        void onBedMeshMatrixChanged();

    signals:

        void dataChanged();

    private:
        QKlipperPrintBed *m_printBed = nullptr;

        QSurfaceDataArray m_data;
        Q_PROPERTY(QSurfaceDataArray data READ data WRITE setData NOTIFY dataChanged FINAL)
};

#endif // BEDMESHDATA_H
