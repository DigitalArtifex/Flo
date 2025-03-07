/*
* Flo :: PrinterTerminalWidget
*
* Provides a widget to hold the terminal and user input
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

#ifndef PRINTERTERMINALWIDGET_H
#define PRINTERTERMINALWIDGET_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QPair>

#include "../../../ui/list/qanimatedlistwidget.h"
#include <QKlipper/qklipper.h>

#include "printerterminalitem.h"

class PrinterTerminalWidget : public QAnimatedListWidget
{
    Q_OBJECT
public:
    PrinterTerminalWidget(QWidget *parent = nullptr);

    void addMessage(QKlipperMessage *message);
    void addMessage(QString title, QString message);
    void addErrorMessage(QString title, QString message);
    void addGcodeResponse(QString &message);

protected:

private:
    QMap<qint64, PrinterTerminalItem*> m_itemMap;

    const static inline QRegularExpression s_gcodeErrorResponseCleanup = QRegularExpression("(\\!\\! )|\n");
    const static inline QRegularExpression s_gcodeResponseCleanup = QRegularExpression("(\\/\\/ )|\n");

};

#endif // PRINTERTERMINALWIDGET_H
