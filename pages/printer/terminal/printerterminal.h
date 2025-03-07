/*
* Flo :: PrinterTerminal
*
* Provides a terminal connection to a Klipper Socket
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

#ifndef PRINTERTERMINAL_H
#define PRINTERTERMINAL_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>

#include <QKlipper/qklipper.h>
#include "3rdparty/QSourceHighlite/qsourcehighliter.h"
#include "common/Page/page.h"
#include "printerterminalwidget.h"
#include <qquickview.h>
#include <qquickwidget.h>

#include "common/dialog/dialog.h"
#include "ui/QIconButton/qiconbutton.h"

class PrinterTerminal : public Page
{
    Q_OBJECT
public:
    PrinterTerminal(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~PrinterTerminal();

protected slots:
    void on_console_message(QKlipperMessage *message);

    void on_commandEdit_returnPressed();
    void on_commandEdit_textChanged();
    void on_commandSendButton_clicked();

    void onConsoleGcodeResponse(QString &message);

protected:
    virtual void setupUi();
    virtual void sendCommand();
    virtual void showEvent(QShowEvent *event);

private:
    QGridLayout *m_layout = nullptr;
    PrinterTerminalWidget *m_terminal = nullptr;

    QFrame *m_commandFrame = nullptr;
    QHBoxLayout *m_commandLayout = nullptr;
    QTextEdit *m_commandEdit = nullptr;
    QPushButton *m_commandSendButton = nullptr;

    QKlipperInstance *m_instance = nullptr;
    QRegularExpression m_gcodeExpression;

    QSourceHighlite::QSourceHighliter *m_highlighter = nullptr;
    QWidget *m_viewerWidget = nullptr;
    QQuickView *m_viewer = nullptr;

    QGridLayout *m_actionBarLayout = nullptr;
    QWidget *m_actionBar = nullptr;
    QIconButton *m_closeButton = nullptr;
};

#endif // PRINTERTERMINAL_H
