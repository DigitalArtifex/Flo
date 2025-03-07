/*
* Flo :: PrinterUserEditor
*
* Provides a way to create and edit system users
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

#ifndef PRINTERUSEREDITOR_H
#define PRINTERUSEREDITOR_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QSpacerItem>

#include "common/dialog/dialog.h"
#include "ui/QIconButton/qiconbutton.h"

#include <QKlipper/qklipper.h>

class PrinterUserEditor : public Dialog
{
    Q_OBJECT
public:
    explicit PrinterUserEditor(QWidget *parent = nullptr);
    ~PrinterUserEditor();

    QKlipperUser user();
    QString password();
    QString username();

signals:

protected slots:
    void setupUi();
    void acceptButtonClicked();
    void cancelButtonClicked();
    void validatePasswords(QString arg1);

private:
    QVBoxLayout *m_centralLayout = nullptr;
    QHBoxLayout *m_buttonLayout = nullptr;

    QLabel *m_iconLabel = nullptr;
    QLabel *m_titleLabel = nullptr;

    QLineEdit *m_userNameEdit = nullptr;
    QLineEdit *m_userPasswordEdit = nullptr;
    QLineEdit *m_userPasswordVerifyEdit = nullptr;

    QIconButton *m_cancelButton = nullptr;
    QIconButton *m_acceptButton = nullptr;
};

#endif // PRINTERUSEREDITOR_H
