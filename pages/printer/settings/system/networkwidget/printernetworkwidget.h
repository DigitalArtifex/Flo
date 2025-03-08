/*
* PrinterNetworkWidget
*
* Provides a widget for monitoring network stats of the printer's system
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

#ifndef PRINTERNETWORKWIDGET_H
#define PRINTERNETWORKWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>

#include <QKlipper/qklipper.h>
#include "common/CardWidget/cardwidget.h"
#include "ui/LineGraphWidget/linegraphwidget.h"

class PrinterNetworkWidget : public CardWidget
{
    Q_OBJECT
public:
    explicit PrinterNetworkWidget(QKlipperSystem *system, QWidget *parent = nullptr);

    virtual void setStyleSheet(const QString &styleSheet);

signals:

protected slots:
    void systemNetworkUpdate();

protected:
    void setupUi();

private:
    LineGraphWidget *m_temperatureGraph = nullptr;

    QKlipperSystem *m_system = nullptr;
    QVBoxLayout *m_centralLayout = nullptr;
    QWidget *m_centralWidget = nullptr;
};

#endif // PRINTERNETWORKWIDGET_H
