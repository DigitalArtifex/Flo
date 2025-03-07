/*
* Flo :: PrinterUserCard
*
* Provides a display for a system user
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

#ifndef PRINTERUSERCARD_H
#define PRINTERUSERCARD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "common/CardWidget/cardwidget.h"

#include <QKlipper/qklipper.h>

class PrinterUserCard : public CardWidget
{
    Q_OBJECT
public:
    explicit PrinterUserCard(QKlipperUser user, QWidget *parent = nullptr);
    ~PrinterUserCard();

    QKlipperUser user() const;

    virtual void setStyleSheet(const QString &styleSheet);

public slots:
    void setUser(const QKlipperUser &user);

signals:
    void userDeleteRequest(QKlipperUser user);

protected slots:
    void setupUi();
    void editButtonClickEvent(bool checked);
    void removeButtonClickEvent(bool checked);

private:
    QKlipperUser m_user;

    QVBoxLayout *m_centralLayout = nullptr;

    QLabel *m_iconLabel = nullptr;
    QLabel *m_userNameLabel = nullptr;
    QLabel *m_userSourceLabel = nullptr;
    QLabel *m_userCreatedLabel = nullptr;

    QWidget *m_centralWidget = nullptr;

    QToolButton *m_editButton = nullptr;
    QToolButton *m_deleteButton = nullptr;
};

#endif // PRINTERUSERCARD_H
