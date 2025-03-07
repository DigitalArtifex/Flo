/*
* Flo :: PrinterOfflineScreen
*
* Provides an overlay when the printer is offline
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

#ifndef PRINTEROFFLINESCREEN_H
#define PRINTEROFFLINESCREEN_H

#include <QFrame>
#include <QKlipper/qklipper.h>
#include "ui/QIconButton/qiconbutton.h"

namespace Ui {
class PrinterOfflineScreen;
}

class PrinterOfflineScreen : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterOfflineScreen(QKlipperInstance *printer, QWidget *parent = nullptr);
    ~PrinterOfflineScreen();

    virtual void setStyleSheet(QString &styleSheet);
    void setText(const QString &text);
    void setIcon(const QIcon &icon);

protected slots:
    void printerConnectingEvent();
    void printerConnectingProgressChanged();
    void printerConnectingTextChanged();
    void onConnectPrinterButtonPressed();

private:
    Ui::PrinterOfflineScreen *ui;

    QIconButton *m_connectButton = nullptr;
    QKlipperInstance *m_instance = nullptr;
    QIcon m_icon;
};

#endif // PRINTEROFFLINESCREEN_H
