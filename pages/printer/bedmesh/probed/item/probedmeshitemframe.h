/*
* Flo :: ProbedMeshItemFrame
*
* Provides a way to display a single probe data point
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

#ifndef PROBEDMESHITEMFRAME_H
#define PROBEDMESHITEMFRAME_H

#include <QFrame>
#include <QStyle>

namespace Ui {
class ProbedMeshItemFrame;
}

class ProbedMeshItemFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ProbedMeshItemFrame(QWidget *parent = nullptr);
    ~ProbedMeshItemFrame();

    qreal value() const;

    void setValue(qreal value);

private:
    Ui::ProbedMeshItemFrame *ui;

    qreal m_value = 0.0000;
    qreal m_thresholdLow = -0.025;
    qreal m_thresholdHigh = 0.025;
};

#endif // PROBEDMESHITEMFRAME_H
