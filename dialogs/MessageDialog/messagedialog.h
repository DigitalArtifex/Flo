/*
* Flo :: MessageDialog
*
* Provides a means of displaying a message, warning or error to the user
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

#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "common/dialog/dialog.h"
#include "ui/QIconButton/qiconbutton.h"

class MessageDialog : public Dialog
{
    Q_OBJECT
public:
    explicit MessageDialog(QWidget *parent = nullptr);
    ~MessageDialog();

    QIcon icon() const;

    QString text() const;

    QString informativeText() const;

public slots:
    void setIcon(const QIcon &icon);
    void setText(const QString &text);
    void setRejectEnabled(bool enabled);

    void setInformativeText(const QString &informativeText);

signals:

protected slots:
    void setupUi();

private:
    QVBoxLayout *m_centralLayout = nullptr;
    QHBoxLayout *m_informationLayout = nullptr;
    QHBoxLayout *m_buttonLayout = nullptr;

    QIcon m_icon;
    QString m_text;
    QString m_informativeText;

    QLabel *m_textLabel = nullptr;
    QLabel *m_informativeTextLabel = nullptr;
    QLabel *m_iconLabel = nullptr;

    QIconButton *m_acceptButton = nullptr;
    QIconButton *m_rejectButton = nullptr;
};

#endif // MESSAGEDIALOG_H
