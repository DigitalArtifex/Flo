/*
* Flo :: AdjustmentScrewFrame
*
* Provides a display for the Adjustment Screws data
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

#ifndef ADJUSTMENTSCREWFRAME_H
#define ADJUSTMENTSCREWFRAME_H

#include <QFrame>
#include <QMovie>
#include <QLabel>

#include "empty/adjustmentscrewemptyframe.h"
#include "item/adjustmentscrewitemframe.h"

#include <common/CardWidget/cardwidget.h>
#include <QKlipper/qklipper.h>

class AdjustmentScrewFrame : public CardWidget
{
    Q_OBJECT

public:
    AdjustmentScrewFrame(QKlipperPrintBed *bed, QWidget *parent = nullptr);
    AdjustmentScrewFrame(QWidget *parent = nullptr);
    ~AdjustmentScrewFrame();

public slots:

    void setPrinterBed(QKlipperPrintBed *printerBed);

signals:

protected:
    virtual void changeEvent(QEvent *event) override;

private slots:
    void setupUi();
    void setIcons();
    void on_recalibrateButton_clicked();
    void on_loadingAnimation_finished();

    void onAdjustmentScrewsChanged();

    void onToolheadHoming();
    void onToolheadHomed();

    void clearLayout();

private:

    QMovie *m_loadingGif = nullptr;
    QLabel *m_loadingLabel = nullptr;

    QFrame *m_loadingFrame = nullptr;
    QHBoxLayout *m_loadingFrameLayout = nullptr;

    AdjustmentScrewEmptyFrame *m_emptyAdjustmentScrewFrame = nullptr;

    QKlipperPrintBed *m_printerBed = nullptr;
    QFrame *m_dataFrame = nullptr;
    QGridLayout *m_dataLayout = nullptr;
};

#endif // ADJUSTMENTSCREWFRAME_H
