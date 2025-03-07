/*
* Flo :: PrinterTerminalItem
*
* Provides a terminal message item
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

#ifndef PRINTERTERMINALITEM_H
#define PRINTERTERMINALITEM_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>

#include <QKlipper/qklipper.h>
#include "../../../ui/list/qanimatedlistitem.h"

class PrinterTerminalItem : public QAnimatedListItem
{
    Q_OBJECT
public:
    PrinterTerminalItem(QWidget *parent = nullptr);
    ~PrinterTerminalItem();

    QKlipperMessage *message() const;
    void setMessage(QKlipperMessage *message);
    void setMessage(QString title, QString message);

    QJsonValue response() const;

    void setErrorMessage(QString title, QString message);

    bool isErrorMessage() const;
    void setIsErrorMessage(bool isErrorMessage);

protected slots:
    void setupUi();
    void onMessageResponseChanged();
    void onMessageErrorChanged();

private:
    QKlipperMessage *m_message = nullptr;

    //UI
    QWidget *m_centralWidget = nullptr;
    QGridLayout *m_layout = nullptr;

    QLabel *m_messageTimestampLabel = nullptr;
    QLabel *m_messageMethodLabel = nullptr;
    QLabel *m_responseMessageLabel = nullptr;

    QDateTime m_timestamp;

    bool m_isErrorMessage = false;
};

#endif // PRINTERTERMINALITEM_H
