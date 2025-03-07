/*
* Flo :: ProbedMeshEmptyFrame
*
* Provides an overlay for when the probe data is empty
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

#ifndef PROBEDMESHEMPTYFRAME_H
#define PROBEDMESHEMPTYFRAME_H

#include <QFrame>
#include <QKlipper/qklipper.h>

namespace Ui {
class ProbedMeshEmptyFrame;
}

class ProbedMeshEmptyFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ProbedMeshEmptyFrame(QKlipperPrintBed *bed, QWidget *parent = nullptr);
    ~ProbedMeshEmptyFrame();

    void setupIcons();

public slots:
    void setStyleSheet(const QString &styleSheet);

protected slots:
    void onToolheadHomingChanged();

private slots:
    void on_homeButton_clicked();

    void on_calibrateButton_clicked();

private:
    Ui::ProbedMeshEmptyFrame *ui;
    QKlipperPrintBed *m_printerBed = nullptr;
};

#endif // PROBEDMESHEMPTYFRAME_H
