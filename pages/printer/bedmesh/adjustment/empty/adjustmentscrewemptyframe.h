/*
* Flo :: AdjustmentScrewEmptyFrame
*
* Provides an overlay when Asjustment Screw data is empty
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

#ifndef ADJUSTMENTSCREWEMPTYFRAME_H
#define ADJUSTMENTSCREWEMPTYFRAME_H

#include <QFrame>
#include <QPixmap>
#include <QLabel>
#include <QMovie>
#include <QSpacerItem>
#include <QHBoxLayout>
#include "ui/QIconButton/qiconbutton.h"

#include <QStyle>

#include <QKlipper/qklipper.h>

class AdjustmentScrewEmptyFrame : public QFrame
{
    Q_OBJECT

public:
    explicit AdjustmentScrewEmptyFrame(QKlipperPrintBed *bed, QWidget *parent = nullptr);
    ~AdjustmentScrewEmptyFrame();

public slots:
    void setStyleSheet(const QString &styleSheet);
    virtual void setCalibrationEnabled(bool enabled);

signals:
    void calibrating();

private slots:
    void on_calibrateButton_clicked();
    void onToolheadHoming();
    void onToolheadHomingFinished();

    void on_homeButton_clicked();

private:

    QSpacerItem *m_rightSpacer = nullptr;
    QSpacerItem *m_topSpacer = nullptr;
    QSpacerItem *m_leftSpacer = nullptr;
    QSpacerItem *m_bottomSpacer = nullptr;

    QKlipperPrintBed *m_printerBed = nullptr;

    QLabel *m_iconLabel = nullptr;
    QLabel *m_textLabel = nullptr;
    QIconButton *m_homeButton = nullptr;
    QIconButton *m_calibrateButton = nullptr;
    QHBoxLayout *m_layout = nullptr;
};

#endif // ADJUSTMENTSCREWEMPTYFRAME_H
