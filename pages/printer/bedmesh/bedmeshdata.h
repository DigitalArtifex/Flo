/*
* Flo :: BedMeshData
*
* Provides the data for the QML graph in the BedMeshViewer, formatted for QtGraphs
*
* Copyright (C) 2024-2025 DigitalArtifex
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
