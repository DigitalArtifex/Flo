/*
* Flo :: ToolHeadControlFrame
*
* Provides a CNC-like control for positioning the toolhead
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

#ifndef TOOLHEADCONTROLFRAME_H
#define TOOLHEADCONTROLFRAME_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QComboBox>

#include <QBitmap>

#include <QtDAWidgets/qmaskedbutton.h>
#include <QKlipper/qklipper.h>

class ToolHeadControlFrame : public QFrame
{
    Q_OBJECT
public:
    ToolHeadControlFrame(QKlipperToolHead *toolhead, QWidget *parent);
    ~ToolHeadControlFrame();

    qreal increment() const;
    void setIncrement(qreal increment);

protected:
    virtual void resizeEvent(QResizeEvent *event);

protected slots:
    void xUpClickEvent();
    void xDownClickEvent();
    void yUpClickEvent();
    void yDownClickEvent();
    void zUpClickEvent();
    void zDownClickEvent();
    void homeClickEvent();

    void toolheadUpdateEvent();

private:

    QMaskedButton *m_xUpWidget = nullptr;
    QMaskedButton *m_xDownWidget = nullptr;
    QMaskedButton *m_yUpWidget = nullptr;
    QMaskedButton *m_yDownWidget = nullptr;
    QMaskedButton *m_zUpWidget = nullptr;
    QMaskedButton *m_zDownWidget = nullptr;
    QMaskedButton *m_homeWidget = nullptr;

    QKlipperToolHead *m_toolhead = nullptr;

    qreal m_increment = 1.0;
};

#endif // TOOLHEADCONTROLFRAME_H
