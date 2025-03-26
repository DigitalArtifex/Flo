/*
* Flo :: AdjustmentScrewItemFrame
*
* Provides a display for the data of a single Adjustment Screw
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

#ifndef ADJUSTMENTSCREWITEMFRAME_H
#define ADJUSTMENTSCREWITEMFRAME_H

#include <QFrame>
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>

#include <QKlipper/qklipper.h>

class AdjustmentScrewItemFrame : public QFrame
{
    Q_OBJECT

public:
    explicit AdjustmentScrewItemFrame(QKlipperAdjustmentScrew *screw, QWidget *parent = nullptr);
    ~AdjustmentScrewItemFrame();

    QKlipperAdjustmentScrew *adjustmentScrew() const;
    void setAdjustmentScrew(QKlipperAdjustmentScrew *adjustmentScrew);

public slots:
    void setupIcons();

protected:
    virtual void changeEvent(QEvent *event) override;

protected slots:
    void onAdjustmentScrewAmountChanged();

private:
    QKlipperAdjustmentScrew *m_adjustmentScrew = nullptr;
    QLabel *m_iconLabel = nullptr;
    QLabel *m_screwNameLabel = nullptr;
    QLabel *m_adjustmentLabel= nullptr;
    QHBoxLayout *m_layout = nullptr;
};

#endif // ADJUSTMENTSCREWITEMFRAME_H
