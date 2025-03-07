/*
* Flo :: PrinterUsersView
*
* Provides an overview of the system's users
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

#ifndef PRINTERUSERSVIEW_H
#define PRINTERUSERSVIEW_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QToolButton>
#include <QSpacerItem>

#include "editor/printerusereditor.h"
#include "printerusercard.h"

#include "common/CardWidget/cardwidget.h"
#include "ui/QIconButton/qiconbutton.h"

#include <QKlipper/qklipper.h>
#include <qwizard.h>

class PrinterUsersView : public CardWidget
{
    Q_OBJECT
public:
    explicit PrinterUsersView(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~PrinterUsersView();

signals:
    void dialogRequested(QDialog *);
    void wizardRequested(QWizard *);

protected slots:
    void setupUi();
    void userListChangedEvent();
    void addUserButtonClickedEvent(bool checked);

    void on_userDeleteRequest(QKlipperUser user);
    void onUserEditorFinished(int returnCode);

protected:
    void setIcons();
    virtual void changeEvent(QEvent *event) override;

private:
    PrinterUserEditor *m_editor = nullptr;
    QKlipperInstance *m_instnace = nullptr;
    QMap<QString, PrinterUserCard*> m_userCards;

    QHBoxLayout *m_centralLayout = nullptr;
    QWidget *m_centralWidget = nullptr;
    QSpacerItem *m_spacer = nullptr;

    QToolButton *m_addUserButton = nullptr;
};

#endif // PRINTERUSERSVIEW_H
