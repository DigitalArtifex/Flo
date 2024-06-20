#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QSizePolicy>
#include <QGridLayout>

#include <QChart>
#include <QChartView>
#include <QMovie>
#include <QLabel>
#include <QTimer>

#include <QParallelAnimationGroup>

#include <QCamera>

#include <QTcpSocket>

#include "QSourceHighlite/qsourcehighliter.h"

#include "types/console/qabstractklipperconsole.h"
#include "system/flo.h"

//UI elements
#include "ui/menubutton.h"
#include "ui/widgetanimation.h"
#include "ui/qanimatedwidget.h"

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

    void changePage(QAnimatedWidget *page, QString title);

    virtual void init();

signals:

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

    void on_settingsPage_printerAdded(PrinterDefinition definition);
    void on_loadingAnimation_finished();
    void on_initAsync();

    virtual void resizeEvent(QResizeEvent *event);

private:
    void consoleSendCommand();
    void setupUiClasses();
    void showPopup();
    void setMenuEnabled(bool enabled);
    void setupPowerActions();

private:
    Flo *_flo = nullptr;

    Ui::MainWindow *ui;
    QAction *_restartAction;
    QAction *_shutdownAction;
    QAction *_closeAction;

    //Pages
    QList<QAnimatedWidget*> _printerPages = QList<QAnimatedWidget*>();
    QAnimatedWidget *_settingsPage = nullptr;
    QAnimatedWidget *_dashboardPage = nullptr;
    QAnimatedWidget *_loadingPage = nullptr;

    QSize _pageSize = QSize();
    QPoint _pagePositionIn = QPoint();
    QPoint _pagePositionOut = QPoint();

    //Menu Buttons
    MenuButton *_dashboardButton;
    QList<MenuButton*> _printerButtons = QList<MenuButton*>();
    MenuButton *_settingsButton;

    //Dialogs
    LoadingDialog *_loading;

    //Loading animation
    QMovie *_loadingGif = nullptr;
    QLabel *_loadingLabel = nullptr;

    WidgetAnimation *_loadingAnimation = nullptr;

    //Timers
    QTimer *_loadTimer = nullptr;
    QTimer *_initTimer = nullptr;

    QPropertyAnimation *_titleOpacityAnimation = nullptr;
    QGraphicsOpacityEffect *_titleOpacityEffect = nullptr;

    QString _currentTitle = "Loading";
    QString _nextTitle = "";

    QAnimatedWidget *_currentPage = nullptr;
    QAnimatedWidget *_nextPage = nullptr;
    QParallelAnimationGroup *_pageAnimationGroup;

};
#endif // MAINWINDOW_H
