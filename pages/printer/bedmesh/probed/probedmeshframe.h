/*
* Flo :: ProbedMeshFrame
*
* Provides the data from the probe for each point measured
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

#ifndef PROBEDMESHFRAME_H
#define PROBEDMESHFRAME_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QMovie>

#include <QKlipper/qklipper.h>
#include "common/CardWidget/cardwidget.h"

#include "empty/probedmeshemptyframe.h"
#include "item/probedmeshitemframe.h"

class ProbedMeshFrame : public CardWidget
{
    Q_OBJECT
public:
    explicit ProbedMeshFrame(QKlipperPrintBed *bed, QWidget *parent = nullptr);
    ~ProbedMeshFrame();

public slots:
    virtual void changeEvent(QEvent *event) override;

protected:
    void setupIcons();

protected slots:

    void onBedMeshCalibratingFinished();

    void clearLayout();

private:
    QWidget *m_centralWidget = nullptr;
    QGridLayout *m_centralLayout = nullptr;

    ProbedMeshEmptyFrame *m_emptyFrame = nullptr;

    QKlipperPrintBed *m_printerBed;

    bool m_calibrating = false;
};

#endif // PROBEDMESHFRAME_H
