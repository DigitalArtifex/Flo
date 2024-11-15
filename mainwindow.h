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
#include <QOpenGLWidget>

#include <QChart>
#include <QChartView>
#include <QMovie>
#include <QLabel>
#include <QTimer>
#include <QColorDialog>

#include <QParallelAnimationGroup>

#include <QCamera>

#include <QTcpSocket>

#include "QSourceHighlite/qsourcehighliter.h"

#include <QKlipper/qklipper.h>
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

protected slots:
    virtual void resizeEvent(QResizeEvent *event);

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

    void on_loadingAnimation_finished();
    void on_initAsync();

    void on_printerPoolPrinterAdded(QKlipperInstance* printer);
    void on_printerPoolPrinterRemoved(QKlipperInstance* printer);

    void onThemeUpdated();

private:
    void consoleSendCommand();
    void setupUiClasses();
    void showPopup();
    void setMenuEnabled(bool enabled);
    void setupPowerActions();

private:
    Flo *m_flo = nullptr;

    Ui::MainWindow *ui;
    QAction *m_restartAction;
    QAction *m_shutdownAction;
    QAction *m_closeAction;

    //Pages
    QList<QAnimatedWidget*> m_printerPages = QList<QAnimatedWidget*>();
    QAnimatedWidget *m_settingsPage = nullptr;
    QAnimatedWidget *m_dashboardPage = nullptr;
    QAnimatedWidget *m_loadingPage = nullptr;

    QSize m_pageSize = QSize();
    QPoint m_pagePositionIn = QPoint();
    QPoint m_pagePositionOut = QPoint();

    //Menu Buttons
    MenuButton *m_dashboardButton = nullptr;
    QList<MenuButton*> m_printerButtons = QList<MenuButton*>();
    MenuButton *m_settingsButton = nullptr;

    //Dialogs
    LoadingDialog *m_loading;

    //Loading animation
    QMovie *m_loadingGif = nullptr;
    QLabel *m_loadingLabel = nullptr;

    WidgetAnimation *m_loadingAnimation = nullptr;

    //Timers
    QTimer *m_loadTimer = nullptr;
    QTimer *m_initTimer = nullptr;

    QPropertyAnimation *m_titleOpacityAnimation = nullptr;
    QGraphicsOpacityEffect *m_titleOpacityEffect = nullptr;

    QString m_currentTitle = "Loading";
    QString m_nextTitle = "";

    QAnimatedWidget *m_currentPage = nullptr;
    QAnimatedWidget *m_nextPage = nullptr;
    QParallelAnimationGroup *m_pageAnimationGroup;

    //for faster ui rendering
    QGraphicsView *m_graphicsView = nullptr;
    QGraphicsScene *m_graphicsScene = nullptr;
};
#endif // MAINWINDOW_H
