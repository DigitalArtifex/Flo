/*
* QAnimatedEmptyListItem
*
* Provides an overlay for an empty animated list widget
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

#ifndef QANIMATEDEMPTYLISTITEM_H
#define QANIMATEDEMPTYLISTITEM_H

#include <QFrame>
#include <QLabel>
#include <QGridLayout>
#include <QSpacerItem>
#include <QObject>

class QAnimatedEmptyListItem : public QFrame
{
    Q_OBJECT
public:
    QAnimatedEmptyListItem(QWidget *parent = nullptr);
    ~QAnimatedEmptyListItem();

    void setupUi();

    virtual void setText(const QString &text);
    virtual void setIcon(const QPixmap &pixmap);
    virtual void setIcon(const QString &iconName);

private:

    QLabel *m_label = nullptr;
    QLabel *m_iconLabel = nullptr;

    QSpacerItem *m_topSpacer = nullptr;
    QSpacerItem *m_middleSpacer = nullptr;
    QSpacerItem *m_bottomSpacer = nullptr;
};

#endif // QANIMATEDEMPTYLISTITEM_H
