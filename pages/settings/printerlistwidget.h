/*
* Flo :: PrinterListWidget
*
* Provides a list widget for configured printers
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

#ifndef PRINTERLISTWIDGET_H
#define PRINTERLISTWIDGET_H

#include <QFrame>
#include <QSpacerItem>
#include <QMouseEvent>
#include <QKlipper/qklipper.h>

#include "printerlistitem.h"

namespace Ui {
class PrinterListWidget;
}

class PrinterListWidget : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterListWidget(QWidget *parent = nullptr);
    ~PrinterListWidget();

    void addItem(QKlipperInstance *definition);
    void removeItem(QKlipperInstance *instance);
    PrinterListItem *selectedItem();

signals:
    void itemSelected(PrinterListItem *item);

private slots:
    void on_itemClicked(PrinterListItem *item);

    void onInstanceRemoved(QKlipperInstance *instance);
    void onInstanceAdded(QKlipperInstance *instance);

    virtual void mousePressEvent(QMouseEvent *event);

private:
    Ui::PrinterListWidget *ui;
    QList<PrinterListItem*> m_items;
    QSpacerItem *m_spacer = nullptr;
    PrinterListItem *m_selectedItem = nullptr;
};

#endif // PRINTERLISTWIDGET_H
