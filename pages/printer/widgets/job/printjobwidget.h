/*
* Flo :: PrintJobWidget
*
* Provides a list widget of queued print jobs
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

#ifndef PRINTJOBWIDGET_H
#define PRINTJOBWIDGET_H

#include <QScrollArea>
#include <QGridLayout>
#include <QSpacerItem>
#include <QWidget>

#include <QKlipper/qklipper.h>

#include "ui/list/qanimatedlistwidget.h"
#include "printjobitem.h"

class PrintJobWidget : public QAnimatedListWidget
{
    Q_OBJECT

public:
    PrintJobWidget(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~PrintJobWidget();

public slots:
    void addJob(QKlipperPrintJob *job);
    void removeJob(QKlipperPrintJob *job);

protected slots:
    void itemRemoveRequestEvent(PrintJobItem *item);

protected:
    void setupIcons();
    virtual void changeEvent(QEvent *event) override;

private:
};

#endif // PRINTJOBWIDGET_H
