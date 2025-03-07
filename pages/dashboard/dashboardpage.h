/*
* Flo :: DashboardPage
*
* Provides an overview of all connected printers
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

#ifndef DASHBOARDPAGE_H
#define DASHBOARDPAGE_H

#include <QFrame>

#include <QKlipper/qklipper.h>
#include <flo/qklipperinstancepool.h>
#include <qquickview.h>

#include "widgets/printer/printerwidget.h"
#include "widgets/system/systemwidget.h"
#include "widgets/status/statuswidget.h"
#include "../../ui/layouts/qflowlayout.h"

namespace Ui {
class DashboardPage;
}

class DashboardPage : public QFrame
{
    Q_OBJECT

public:
    explicit DashboardPage(QWidget *parent = nullptr);
    ~DashboardPage();
    void loadPrinters();
    void setUiClasses();

    void updateStyleSheet(QString stylesheet);

    virtual void setStyleSheet(QString styleSheet);

    virtual void resizeEvent(QResizeEvent *event);

protected slots:
    //Printer Pool
    void onInstanceAdded(QKlipperInstance *instance);
    void onInstanceRemoved(QKlipperInstance *instance);

private:
    Ui::DashboardPage *ui;
    QList<PrinterWidget*> m_printerWidgets;
    PrinterWidget *m_selectedWidget = nullptr;
    SystemWidget *m_systemWidget = nullptr;
    StatusWidget *m_statusWidget = nullptr;
    QFlowLayout *m_layout = nullptr;
    QTimer *m_initTimer = nullptr;
    QHBoxLayout *m_topLayout = nullptr;

    QQuickView *m_viewer = nullptr;
    QWidget *m_viewerWidget = nullptr;
};

#endif // DASHBOARDPAGE_H
