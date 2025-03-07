/*
* Flo :: MainWindow
*
* Main window of the application
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QSizePolicy>
#include <QGridLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QScreen>

#include <QMovie>
#include <QLabel>
#include <QTimer>
#include <QColorDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QTextEdit>

#include <QParallelAnimationGroup>

#include <QTcpSocket>

#include "3rdparty/QSourceHighlite/qsourcehighliter.h"
#include "3rdparty/SlidingStackedWidget/slidingstackedwidget.h"

#include <QKlipper/qklipper.h>
#include "flo/flo.h"

//UI elements
#include "pages/dashboard/dashboardpage.h"
#include "pages/printer/printerpage.h"
#include "pages/settings/settingspage.h"
#include "ui/MenuButton/menubutton.h"
#include <common/QAnimatedWidget/qanimatedwidget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class LoadingDialog;

using namespace QSourceHighlite;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changePage(QWidget *page, QString title);

signals:

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;

private slots:
    void online();
    void updateStyleSheet();

    void on_dashboardMenuButton_toggled(MenuButton* button);
    void on_printerMenuButton_toggled(MenuButton* button);
    void on_settingsMenuButton_toggled(MenuButton* button);

    void on_currentPage_animationOut_finished();
    void on_nextPage_animationIn_finished();
    void on_titleOpacityAnimation_finished();

    void on_emergencyStopButton_clicked();

    void on_restartAction_triggered(bool checked);
    void on_shutdownAction_triggered(bool checked);
    void on_closeAction_triggered(bool checked);
    void on_powerButton_clicked();
    void on_initAsync();

    void on_printerPoolPrinterAdded(QKlipperInstance* printer);
    void on_printerPoolPrinterRemoved(QKlipperInstance* printer);

    void onThemeUpdated();

private:
    void consoleSendCommand();
    void setupUiClasses();
    void showPopup();
    void setMenuEnabled(bool enabled);

private:
    Flo *m_flo = nullptr;

    Ui::MainWindow *ui;
    QAction *m_restartAction;
    QAction *m_shutdownAction;
    QAction *m_closeAction;

    //Pages
    QList<PrinterPage*> m_printerPages;
    SettingsPage *m_settingsPage = nullptr;
    DashboardPage *m_dashboardPage = nullptr;
    QAnimatedWidget *m_loadingPage = nullptr;

    QSize m_pageSize = QSize();
    QPoint m_pagePositionIn = QPoint();
    QPoint m_pagePositionOut = QPoint();

    //Menu Buttons
    MenuButton *m_dashboardButton = nullptr;
    QList<MenuButton*> m_printerButtons = QList<MenuButton*>();
    QKlipperInstanceList m_instances;
    MenuButton *m_settingsButton = nullptr;

    //Dialogs
    LoadingDialog *m_loading;

    //Loading animation
    QMovie *m_loadingGif = nullptr;
    QLabel *m_loadingLabel = nullptr;

    //Timers
    QTimer *m_loadTimer = nullptr;
    QTimer *m_initTimer = nullptr;

    QPropertyAnimation *m_titleOpacityAnimation = nullptr;
    QGraphicsOpacityEffect *m_titleOpacityEffect = nullptr;

    QString m_currentTitle = "Loading";
    QString m_nextTitle = "";

    //for faster ui rendering
    QGraphicsView *m_graphicsView = nullptr;
    QGraphicsScene *m_graphicsScene = nullptr;
    SlidingStackedWidget *m_pageStackWidget = nullptr;

    QKlipperInstance *m_currentInstance = nullptr;

    QQuickView *m_viewer = nullptr;
    QWidget *m_viewerWidget = nullptr;
};
#endif // MAINWINDOW_H
