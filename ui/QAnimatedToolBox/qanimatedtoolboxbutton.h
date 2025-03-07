/*
* QAnimatedToolBoxButton
*
* Provides a header button for QAnimatedToolBox
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

#ifndef QANIMATEDTOOLBOXBUTTON_H
#define QANIMATEDTOOLBOXBUTTON_H

#include <QPushButton>
#include <QObject>
#include <QWidget>

#include "ui/QIconButton/qiconbutton.h"

class QAnimatedToolBoxButton : public QIconButton
{
    Q_OBJECT
public:
    QAnimatedToolBoxButton(QWidget *parent = nullptr);
    QAnimatedToolBoxButton(QString text, QWidget *parent = nullptr);
    QAnimatedToolBoxButton(QIcon icon, QString text, QWidget *parent = nullptr);

signals:
    void clicked(QAnimatedToolBoxButton*);

protected slots:
    void onClicked();
};

Q_DECLARE_METATYPE(QAnimatedToolBoxButton)

#endif // QANIMATEDTOOLBOXBUTTON_H
