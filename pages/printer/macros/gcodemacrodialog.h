/*
* Flo :: GCodeMacroDialog
*
* Provides an list of supported GCode Macros
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

#ifndef GCODEMACRODIALOG_H
#define GCODEMACRODIALOG_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QResizeEvent>

#include <common/dialog/dialog.h>
#include <QKlipper/qklipper.h>

class GCodeMacroDialog : public Dialog
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit GCodeMacroDialog(QKlipperServer *server, QWidget *parent = nullptr);

    signals:

    protected slots:
        void onServerGcodeMacrosChanged();

    protected:
        void setupUi();
        virtual void resizeEvent(QResizeEvent *event) override;

    private:
        QGridLayout *m_layout = nullptr;
        QTableWidget *m_macroTable = nullptr;
        QKlipperServer *m_server = nullptr;
};

#endif // GCODEMACRODIALOG_H
