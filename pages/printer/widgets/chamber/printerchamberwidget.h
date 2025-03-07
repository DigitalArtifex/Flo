/*
* Flo :: PrinterChamberWidget
*
* Provides an overview of the printer chamber conditions
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

#ifndef PRINTERCHAMBERWIDGET_H
#define PRINTERCHAMBERWIDGET_H

#include <QFrame>
#include <QtDAWidgets/qgaugewidget.h>
#include "pages/printer/widgets/temperature/temperaturewidget.h"

namespace Ui {
class PrinterChamberWidget;
}

class PrinterChamberWidget : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterChamberWidget(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~PrinterChamberWidget();

protected slots:
    void setIcons();

protected:
    virtual void changeEvent(QEvent *event) override;

private:
    Ui::PrinterChamberWidget *ui;

    PrinterTemperatureWidget *m_chamberTemperatureWidget = nullptr;
    QGaugeWidget *m_chamberTemperatureBar = nullptr;
};

#endif // PRINTERCHAMBERWIDGET_H
