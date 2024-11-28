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
        qreal minimum() const;
        qreal maximum() const;

    public slots:

        void setData(const QSurfaceDataArray &data);
        void setMinimum(qreal minimum);
        void setMaximum(qreal maximum);

    protected slots:
        void onBedMeshMatrixChanged();

    signals:
        void dataChanged();
        void minimumChanged();
        void maximumChanged();

    private:
        qreal m_minimum = 0;
        qreal m_maximum = 0;

        QKlipperPrintBed *m_printBed = nullptr;

        QSurfaceDataArray m_data;
        Q_PROPERTY(QSurfaceDataArray data READ data WRITE setData NOTIFY dataChanged FINAL)
        Q_PROPERTY(qreal minimum READ minimum WRITE setMinimum NOTIFY minimumChanged FINAL)
        Q_PROPERTY(qreal maximum READ maximum WRITE setMaximum NOTIFY maximumChanged FINAL)
};

#endif // BEDMESHDATA_H
