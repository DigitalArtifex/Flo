#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QSizePolicy>
#include <QGridLayout>

#include <QChart>
#include <QChartView>

#include <QCamera>

#include <QTcpSocket>

#include "QSourceHighlite/qsourcehighliter.h"

#include "klipperconsole.h"
#include "system/settings.h"

//UI elements
#include "widgets/temperature/temperaturegraph.h"
#include "ui/circularprogressbar.h"
#include "ui/menubutton.h"
#include "ui/popup.h"
#include "ui/widgetanimation.h"

//Pages
#include "pages/filebrowser/filebrowserpage.h"
#include "pages/settings/settingspage.h"
#include "pages/printer/printerpage.h"
#include "pages/dashboard/dashboardpage.h"
#include "types/klipperfile.h"
#include "types/printer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace QSourceHighlite;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    //Menu Buttons
    MenuButton *dashboardButton;
    MenuButton *consoleButton;
    MenuButton *gcodeFilesButton;
    MenuButton *printerButton;
    MenuButton *settingsButton;

    Popup *popup;

    //Pages
    FileBrowserPage *fileBrowser;
    PrinterPage *printerPage;
    FileBrowserPage *dashboardFileBrowser;

    CircularProgressBar *dashboardExtruderProgressBar;
    CircularProgressBar *dashboardExtruder1ProgressBar;
    CircularProgressBar *dashboardExtruder2ProgressBar;
    CircularProgressBar *dashboardExtruder3ProgressBar;
    CircularProgressBar *dashboardBedProgressBar;
    CircularProgressBar *dashboardChamberProgressBar;
    CircularProgressBar *dashboardExtruderFanProgressBar;
    CircularProgressBar *dashboardPartsFanProgressBar;
    CircularProgressBar *dashboardSystemFanProgressBar;

    CircularProgressBar *dashboardSystemCpuLoadProgressBar;
    CircularProgressBar *dashboardSystemMemoryLoadProgressBar;

    QRect errorGeometryIn;
    QRect errorGeometryOut;

    QCamera *dashboardWebcam;

    TemperatureGraph *dashboardTemperatureGraph;

    bool startup = false;

    //Animation variables
    QPropertyAnimation *menuAnimationOut = nullptr;
    QPropertyAnimation *menuAnimationIn = nullptr;
    QPropertyAnimation *menuAnimationOpacity = nullptr;
    QGraphicsOpacityEffect *menuOpacityEffect = nullptr;
    QPropertyAnimation *errorAnimationOut = nullptr;
    QPropertyAnimation *errorAnimationIn = nullptr;
    QPropertyAnimation *errorAnimationOpacity = nullptr;
    QGraphicsOpacityEffect *errorOpacityEffect = nullptr;

    QPropertyAnimation *_titleOpacityAnimation = nullptr;
    QGraphicsOpacityEffect *_titleOpacityEffect = nullptr;

    //Camera stream
    QTcpSocket *webcamSocket;

    QPoint menuAnimationStart;
    QPoint menuAnimationEnd;

    int tabIndexCurrent = 0;
    int tabIndexNext = 0;

    QString _currentTitle = "Dashboard";
    QString _changingTitle = "";

    //Terminal Page
    QRect _terminalDebugGeometryIn;
    QRect _terminalDebugGeometryOut;
    QPropertyAnimation *_terminalDebugAnimationIn = nullptr;
    QPropertyAnimation *_terminalDebugAnimationOut = nullptr;
    QSourceHighliter *_terminalResponseHighlighter = nullptr;
    QSourceHighliter *_terminalDebugHighlighter = nullptr;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeTabIndex(int index, QString title);

signals:
    void PrinterError(QString message);
    void PrinterOnline();
    void PrinterShutdown();

private slots:
    void on_consoleEditCommand_textChanged(const QString &arg1);

    void on_consoleEditCommand_returnPressed();

    void on_consoleButtonSend_clicked();

    void on_consoleResponse(KlipperResponse response);
    void on_consolePresetSelector_currentChanged(int index);
    void on_commandSent(QString data);


    void on_dashboardMenuButton_toggled(MenuButton* button);
    void on_moonrakerMenuButton_toggled(MenuButton* button);
    void on_gcodeMenuButton_toggled(MenuButton* button);
    void on_settingsMenuButton_toggled(MenuButton* button);

    void on_menuAnimationIn_finished();
    void on_menuAnimationOut_finished();
    void on_titleOpacityAnimation_finished();

    void on_gcodeFilesMenuButton_toggled(MenuButton* button);
    void on_printerMenuButton_toggled(MenuButton* button);
    void on_printerError(QString message);

    void updateStyleSheet();

    void on_directoryCreateRequested(KlipperFile directory);
    void on_directoryDeleteRequested(KlipperFile directory);

    void on_closeErrorButton_clicked();
    void on_printerStatusUpdate(KlipperResponse response);
    void on_fileRefreshRequested(QString directory);
    void on_fileListReceived(QList<KlipperFile> files);
    void on_directoryListReceived(QList<KlipperFile> directories);
    void on_fileDirectoryChanged(QString directory);
    void on_filePrintRequested(KlipperFile file);
    void on_fileDeleteRequested(KlipperFile file);
    void on_emergencyStopButton_clicked();

    void on_restartAction_triggered(bool checked);
    void on_shutdownAction_triggered(bool checked);
    void on_closeAction_triggered(bool checked);

    void on_debugTerminalButton_toggled(bool checked);

    void on_printerUpdate(Printer *printer);

    void on_klipperConnected();
    void on_klipperDisconnected();
    void on_printerFound(Printer *printer);

    void on_klipperRestartButton_clicked();

    void on_firmwareRestartButton_clicked();

    void on_powerButton_clicked();

    //Redo
    void on_settingsPage_printerAdded(PrinterDefinition definition);


private:
    Ui::MainWindow *ui;
    QAction *_restartAction;
    QAction *_shutdownAction;
    QAction *_closeAction;
    Printer *_printer = nullptr;
    PrinterList _printers;

    SettingsPage *_settingsPage = nullptr;
    DashboardPage *_dashboardPage = nullptr;


    void consoleSendCommand();
    void setupUiClasses();
    void displayError(QString message);
    void showPopup();
    void setMenuEnabled(bool enabled);
    void setupPowerActions();

    void setPrinter(Printer *printer);

};
#endif // MAINWINDOW_H
