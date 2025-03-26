/*
* Flo :: BedMeshHealthCard
*
* Provides a rudimentary bed health display. It measures the distance between the lowest and highest
* data point and calculates how close it is to 0.3mm.
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

#ifndef BEDMESHHEALTHCARD_H
#define BEDMESHHEALTHCARD_H

#include <QObject>
#include <QWidget>
#include <QProgressBar>
#include "common/CardWidget/cardwidget.h"

#include "QKlipper/qklipper.h"
#include "../bedmeshdata.h"
#include "flo/settings.h"

class BedMeshHealthCard : public CardWidget
{
        Q_OBJECT
    public:
        BedMeshHealthCard(BedMeshData *data, QWidget *parent = nullptr);
        BedMeshHealthCard(QWidget *parent = nullptr);

    public slots:
        void setMeshData(BedMeshData *meshData);

    protected:
        virtual void changeEvent(QEvent *event) override;
        void setupUi();
        void setupIcons();

    protected slots:
        void onBedMeshUpdated();

    private:
        QWidget *m_centralWidget = nullptr;
        QGridLayout *m_centralLayout = nullptr;

        QLabel *m_minLabel = nullptr;
        QLabel *m_maxLabel = nullptr;
        QLabel *m_varianceLabel = nullptr;
        QLabel *m_statusIconLabel = nullptr;

        QProgressBar *m_bedHealth = nullptr;

        BedMeshData *m_meshData = nullptr;
};

#endif // BEDMESHHEALTHCARD_H
