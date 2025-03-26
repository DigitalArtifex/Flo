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
#include <QStyle>

class AdjustmentScrewEmptyFrame : public QFrame
{
    Q_OBJECT

public:
    explicit AdjustmentScrewEmptyFrame(QWidget *parent = nullptr);
    ~AdjustmentScrewEmptyFrame();

protected slots:
    virtual void changeEvent(QEvent *event) override;
    void setIcons();

private slots:

private:
    QLabel *m_iconLabel = nullptr;
    QLabel *m_textLabel = nullptr;
    QHBoxLayout *m_layout = nullptr;
};

#endif // ADJUSTMENTSCREWEMPTYFRAME_H
