/*
* Flo :: PrinterListItem
*
* Provides a list item for a configured printer
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

#ifndef PRINTERLISTITEM_H
#define PRINTERLISTITEM_H

#include <QFrame>
#include <QListWidgetItem>
#include <QTimer>
#include <QMouseEvent>
#include <QKlipper/qklipper.h>

namespace Ui {
class PrinterListItem;
}

class PrinterListItem : public QFrame, public QListWidgetItem
{
    Q_OBJECT

public:
    explicit PrinterListItem(QWidget *parent = nullptr);
    ~PrinterListItem();

    void setInstance(QKlipperInstance *instance);
    void setUiClasses();
    void setSelected(bool selected);
    bool selected();

    QKlipperInstance *instance();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

signals:
    void clicked(PrinterListItem *item);
    void longPressed(PrinterListItem *item);

private slots:
    virtual void clickTimeout();

    void onInstanceNameChanged();
    void onAddressChanged();
    void onPortChanged();
    void onInstanceThumbnailChanged();


private:
    Ui::PrinterListItem *ui;
    QKlipperInstance *m_definition = nullptr;
    bool m_pressed = false;
    bool m_longPress = false;
    bool m_rightClick = false;
    QTimer *m_clickTimer = NULL;
};

#endif // PRINTERLISTITEM_H
