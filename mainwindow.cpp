#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "system/printerpool.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    startup = true;

    dashboardExtruderProgressBar = new CircularProgressBar();
    dashboardExtruder1ProgressBar = new CircularProgressBar();
    dashboardExtruder2ProgressBar = new CircularProgressBar();
    dashboardExtruder3ProgressBar = new CircularProgressBar();
    dashboardBedProgressBar = new CircularProgressBar();
    dashboardChamberProgressBar = new CircularProgressBar();
    dashboardExtruderFanProgressBar = new CircularProgressBar();
    dashboardPartsFanProgressBar = new CircularProgressBar();
    dashboardSystemFanProgressBar = new CircularProgressBar();
    dashboardSystemCpuLoadProgressBar = new CircularProgressBar();
    dashboardSystemMemoryLoadProgressBar = new CircularProgressBar();

    dashboardTemperatureGraph = new TemperatureGraph(this);
    dashboardFileBrowser = new FileBrowserPage();

    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowIcon(QIcon(":/images/application-icon"));

    dashboardButton = new MenuButton(0, ui->menuFrame);
    dashboardButton->setText(QString("Dashboard"));
    dashboardButton->setIcon("dashboard");
    //dashboardButton->setChecked(true);
    ui->menuButtonLayout->addWidget(dashboardButton);
    connect(dashboardButton, SIGNAL(clicked(MenuButton*)), this, SLOT(on_dashboardMenuButton_toggled(MenuButton*)));

    consoleButton = new MenuButton(1, ui->menuFrame);
    consoleButton->setText(QString("Terminal"));
    consoleButton->setIcon("moonraker");
    consoleButton->setChecked(false);
    ui->menuButtonLayout->addWidget(consoleButton);
    connect(consoleButton, SIGNAL(clicked(MenuButton*)), this, SLOT(on_gcodeMenuButton_toggled(MenuButton*)));

    gcodeFilesButton = new MenuButton(4, ui->menuFrame);
    gcodeFilesButton->setText(QString("GCode Files"));
    gcodeFilesButton->setIcon("files");
    gcodeFilesButton->setChecked(false);
    ui->menuButtonLayout->addWidget(gcodeFilesButton);
    connect(gcodeFilesButton, SIGNAL(clicked(MenuButton*)), this, SLOT(on_gcodeFilesMenuButton_toggled(MenuButton*)));

    printerButton = new MenuButton(5, ui->menuFrame);
    printerButton->setText(QString("Printer"));
    printerButton->setIcon("dashboard");
    printerButton->setChecked(false);
    ui->menuButtonLayout->addWidget(printerButton);
    connect(printerButton, SIGNAL(clicked(MenuButton*)), this, SLOT(on_printerMenuButton_toggled(MenuButton*)));

    settingsButton = new MenuButton(3, ui->menuFrame);
    settingsButton->setText(QString("Settings"));
    settingsButton->setIcon("dashboard");
    settingsButton->setChecked(false);
    ui->menuButtonLayout->addWidget(settingsButton);
    connect(settingsButton, SIGNAL(clicked(MenuButton*)), this, SLOT(on_settingsMenuButton_toggled(MenuButton*)));

    ui->errorMessageFrame->setMaximumHeight(0);

    showMaximized();

    Settings::load();

    connect(ui->consolePresetSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(on_consolePresetSelector_currentChanged(int)));

    _titleOpacityEffect = new QGraphicsOpacityEffect(this);
    menuOpacityEffect = new QGraphicsOpacityEffect(this);
    menuAnimationIn = new QPropertyAnimation(ui->pageStack, "pos", this);
    menuAnimationOut = new QPropertyAnimation(ui->pageStack, "pos", this);
    menuAnimationOpacity = new QPropertyAnimation(menuOpacityEffect, "opacity", this);

    errorOpacityEffect = new QGraphicsOpacityEffect(this);
    errorAnimationIn = new QPropertyAnimation(ui->errorMessageFrame, "maximumHeight", this);
    errorAnimationOut = new QPropertyAnimation(ui->errorMessageFrame, "maximumHeight", this);
    errorAnimationOpacity = new QPropertyAnimation(errorOpacityEffect, "opacity", this);

    connect(menuAnimationIn, SIGNAL(finished()), this, SLOT(on_menuAnimationIn_finished()));
    connect(menuAnimationOut, SIGNAL(finished()), this, SLOT(on_menuAnimationOut_finished()));


    menuAnimationOpacity->setStartValue(0);
    menuAnimationOpacity->setEndValue(1);
    menuAnimationOpacity->setDuration(200);

    errorAnimationOpacity->setStartValue(0);
    errorAnimationOpacity->setEndValue(1);
    errorAnimationOpacity->setDuration(200);

    errorAnimationIn->setStartValue(0);
    errorAnimationIn->setEndValue(200);
    errorAnimationIn->setDuration(250);

    errorAnimationOut->setStartValue(200);
    errorAnimationOut->setEndValue(0);
    errorAnimationOut->setDuration(250);

    ui->terminalPageTitleBar->setHidden(true);

    connect(this,SIGNAL(PrinterError(QString)),this,SLOT(on_printerError(QString)));

    fileBrowser = new FileBrowserPage();
    connect(fileBrowser, SIGNAL(refreshRequested(QString)), this, SLOT(on_fileRefreshRequested(QString)));
    connect(fileBrowser, SIGNAL(printRequested(KlipperFile)), this, SLOT(on_filePrintRequested(KlipperFile)));
    connect(fileBrowser, SIGNAL(createDirectory(KlipperFile)), this, SLOT(on_directoryCreateRequested(KlipperFile)));
    connect(fileBrowser, SIGNAL(deleteRequested(KlipperFile)), this, SLOT(on_fileDeleteRequested(KlipperFile)));
    connect(fileBrowser, SIGNAL(deleteDirectory(KlipperFile)), this, SLOT(on_directoryDeleteRequested(KlipperFile)));
    connect(dashboardFileBrowser, SIGNAL(refreshRequested(QString)), this, SLOT(on_fileRefreshRequested(QString)));
    connect(dashboardFileBrowser, SIGNAL(printRequested(KlipperFile)), this, SLOT(on_filePrintRequested(KlipperFile)));
    connect(dashboardFileBrowser, SIGNAL(createDirectory(KlipperFile)), this, SLOT(on_directoryCreateRequested(KlipperFile)));
    connect(dashboardFileBrowser, SIGNAL(deleteRequested(KlipperFile)), this, SLOT(on_fileDeleteRequested(KlipperFile)));
    connect(dashboardFileBrowser, SIGNAL(deleteDirectory(KlipperFile)), this, SLOT(on_directoryDeleteRequested(KlipperFile)));
    ui->gcodeFilesPage->layout()->addWidget(fileBrowser);

    printerPage = new PrinterPage(this);
    ui->printerPage->layout()->addWidget(printerPage);

    _settingsPage = new SettingsPage(this);
    connect(_settingsPage, SIGNAL(printerAdded(PrinterDefinition)), this, SLOT(on_settingsPage_printerAdded(PrinterDefinition)));
    ui->settingsPageLayout->layout()->addWidget(_settingsPage);

    _terminalDebugGeometryIn = ui->sentCommands->geometry();
    _terminalDebugGeometryOut = _terminalDebugGeometryIn;
    _terminalDebugGeometryOut.setWidth(0);

    _terminalDebugAnimationIn = new QPropertyAnimation(ui->sentCommands, "maximumWidth", this);
    _terminalDebugAnimationIn->setStartValue(0);
    _terminalDebugAnimationIn->setEndValue(400);
    _terminalDebugAnimationIn->setDuration(250);

    _terminalDebugAnimationOut = new QPropertyAnimation(ui->sentCommands, "maximumWidth", this);
    _terminalDebugAnimationOut->setStartValue(400);
    _terminalDebugAnimationOut->setEndValue(0);
    _terminalDebugAnimationOut->setDuration(250);

    _terminalResponseHighlighter = new QSourceHighliter(ui->consoleEditTerminal->document());
    _terminalResponseHighlighter->setCurrentLanguage(QSourceHighliter::CodeJSON);
    _terminalResponseHighlighter->setTheme(QSourceHighliter::System);
    _terminalDebugHighlighter = new QSourceHighliter(ui->sentCommands->document());
    _terminalDebugHighlighter->setCurrentLanguage(QSourceHighliter::CodeJSON);

    setupPowerActions();

    //_printer->setMoonrakerLocation(QString("/home/parametheus/printer_data/comms/moonraker.sock"));
    //_printer->connectMoonraker();
    //_printer->console()->connectKlipper();
    PrinterPool::loadPrinters();
    _printer = PrinterPool::getPrinterById(Settings::printers()[0].id);
    connect(_printer->console(), SIGNAL(responseReceived(KlipperResponse)), this, SLOT(on_consoleResponse(KlipperResponse)));
    connect(_printer->console(), SIGNAL(printerUpdateReceived(KlipperResponse)), this, SLOT(on_printerStatusUpdate(KlipperResponse)));

    _dashboardPage = new DashboardPage(this);
    ui->dashboardPageLayout->layout()->addWidget(_dashboardPage);


    startup = false;

    setupUiClasses();
    updateStyleSheet();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete menuAnimationIn;
    delete menuAnimationOut;
}

void MainWindow::changeTabIndex(int index, QString title)
{
    this->updateStyleSheet();
    this->setMenuEnabled(false);
    tabIndexNext = index;

    ui->pageStack->setGraphicsEffect(menuOpacityEffect);

    menuAnimationStart.setX(ui->pageStack->x());
    menuAnimationStart.setY(ui->pageStack->y());
    menuAnimationEnd.setX(this->width());
    menuAnimationEnd.setY(ui->pageStack->y());

    menuAnimationOut->setStartValue(menuAnimationStart);
    menuAnimationOut->setEndValue(menuAnimationEnd);
    menuAnimationOut->setDuration(250);

    menuAnimationIn->setStartValue(menuAnimationEnd);
    menuAnimationIn->setEndValue(menuAnimationStart);
    menuAnimationIn->setDuration(250);

    menuAnimationOpacity->setStartValue(1);
    menuAnimationOpacity->setEndValue(0);
    menuAnimationOpacity->setDuration(200);

    _titleOpacityAnimation = new QPropertyAnimation(_titleOpacityEffect, "opacity", this);
    _titleOpacityAnimation->setStartValue(1);
    _titleOpacityAnimation->setEndValue(0);
    _titleOpacityAnimation->setDuration(250);
    ui->pageTitle->setGraphicsEffect(_titleOpacityEffect);
    connect(_titleOpacityAnimation,SIGNAL(finished()),this,SLOT(on_titleOpacityAnimation_finished()));
    _changingTitle = title;

    _titleOpacityAnimation->start();
    menuAnimationOut->start();
    menuAnimationOpacity->start();
}

void MainWindow::on_consoleEditCommand_textChanged(const QString &arg1)
{
    if(arg1.length() > 0)
        ui->consoleButtonSend->setEnabled(true);
    else
        ui->consoleButtonSend->setEnabled(false);
}

void MainWindow::on_consoleEditCommand_returnPressed()
{
    consoleSendCommand();
}

void MainWindow::on_consoleButtonSend_clicked()
{
    consoleSendCommand();
}

void MainWindow::on_consoleResponse(KlipperResponse response)
{
    if(response.isOkay())
    {
        //if(response.origin != KlipperResponse::System)
            ui->consoleEditTerminal->append(QJsonDocument(response.rootObject).toJson());
    }
    else
    {
        //ui->consoleEditTerminal->append(QJsonDocument(response.rootObject).toJson());
        QString errorMessage = "Error: ";
        QJsonObject errorObject = response["error"].toObject();
        errorMessage += errorObject["message"].toString();
        errorMessage += QString(" (") + QString::number(errorObject["code"].toInt() * -1) + QString(")");

        ui->consoleEditTerminal->append("");
        ui->consoleEditTerminal->append(errorMessage);
    }

    ui->consoleEditCommand->setEnabled(true);
    updateStyleSheet();
}

void MainWindow::on_consolePresetSelector_currentChanged(int index)
{
    if(startup)
        return;

    QString selectedPreset = ui->consolePresetSelector->itemText(index);
    _printer->console()->sendPreset(selectedPreset, KlipperMessage::Console);
}

void MainWindow::on_commandSent(QString data)
{
    ui->sentCommands->append(data);
}

void MainWindow::consoleSendCommand()
{
    QString command = ui->consoleEditCommand->text();

    if(command.length() > 0)
    {
        ui->consoleButtonSend->setEnabled(false);
        ui->consoleEditCommand->setEnabled(false);
        ui->consoleEditCommand->clear();
        ui->consoleEditTerminal->append(command);
        //command.append("\r\n");
        _printer->console()->sendCommand(command, KlipperMessage::User);
    }
}

void MainWindow::setupUiClasses()
{
    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Window"));
    ui->PageContainer->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContainer"));
    ui->emergencyStopButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "EmergencyStopButton"));
    ui->consolePage->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->moonrakerPage->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    _settingsPage->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));

    ui->menuBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuBar"));
    ui->errorMessageFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupFrame" << "ErrorFrame" ));
    ui->errorMessageLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ErrorText" ));
    ui->errorTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ErrorTitle" ));
    ui->pageTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageTitle" ));

    //Menu Buttons
    ui->menuFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Menu"));
    ui->PageContainer->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContainer"));
    ui->menuTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuTitleBar"));
    ui->applicationIcon->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ApplicationIcon"));
    dashboardButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuButton" << "DashboardMenuButton"));
    consoleButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuButton" << "TerminalMenuButton"));

    //Dashboard widget titles


    dashboardFileBrowser->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget"));
    //ui->statusFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget"));


    //Page Titles
    ui->terminalPageTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageTitle"));
    ui->terminalPageTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageTitleBar"));
    ui->terminalPageActionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageActionBar"));

    //Icons
    ui->powerButton->setIcon(Settings::getThemeIcon(QString("power-icon")));

    //Loading widgets
    ui->loadingKlipperFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget"));
    ui->loadingMoonrakerFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget"));
    ui->loadingPrinterFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget"));
}

void MainWindow::on_dashboardMenuButton_toggled(MenuButton* button)
{
    dashboardButton->setChecked(true);
    consoleButton->setChecked(false);
    gcodeFilesButton->setChecked(false);
    printerButton->setChecked(false);
    settingsButton->setChecked(false);
    changeTabIndex(button->getId(), QString("Dashboard"));
}


void MainWindow::on_moonrakerMenuButton_toggled(MenuButton* button)
{
    changeTabIndex(button->getId(), QString("Terminal"));
}


void MainWindow::on_gcodeMenuButton_toggled(MenuButton* button)
{
    dashboardButton->setChecked(false);
    consoleButton->setChecked(true);
    gcodeFilesButton->setChecked(false);
    printerButton->setChecked(false);
    settingsButton->setChecked(false);
    changeTabIndex(button->getId(), QString("Terminal"));
}


void MainWindow::on_settingsMenuButton_toggled(MenuButton* button)
{
    dashboardButton->setChecked(false);
    consoleButton->setChecked(false);
    gcodeFilesButton->setChecked(false);
    printerButton->setChecked(false);
    settingsButton->setChecked(true);

    changeTabIndex(button->getId(), QString("Settings"));
}

void MainWindow::on_menuAnimationIn_finished()
{
    tabIndexCurrent = tabIndexNext;
    tabIndexNext = -1;

    this->setMenuEnabled(true);
    //this->updateStyleSheet();
}

void MainWindow::on_menuAnimationOut_finished()
{
    ui->pageStack->setCurrentIndex(tabIndexNext);

    menuAnimationOpacity->setStartValue(0);
    menuAnimationOpacity->setEndValue(1);
    menuAnimationOpacity->setDuration(200);

    menuAnimationIn->start();
    menuAnimationOpacity->start();
}

void MainWindow::on_titleOpacityAnimation_finished()
{
    if(_changingTitle.isEmpty())
        delete _titleOpacityAnimation;
    else
    {
        _currentTitle = this->_changingTitle;
        ui->pageTitle->setText(_currentTitle);
        _changingTitle = "";
        _titleOpacityAnimation->setStartValue(0);
        _titleOpacityAnimation->setEndValue(1);
        _titleOpacityAnimation->start();
    }
}

void MainWindow::on_gcodeFilesMenuButton_toggled(MenuButton* button)
{
    dashboardButton->setChecked(false);
    consoleButton->setChecked(false);
    gcodeFilesButton->setChecked(true);
    printerButton->setChecked(false);
    settingsButton->setChecked(false);
    changeTabIndex(button->getId(), QString("G-Code Files"));
}


void MainWindow::on_printerMenuButton_toggled(MenuButton* button)
{
    dashboardButton->setChecked(false);
    consoleButton->setChecked(false);
    gcodeFilesButton->setChecked(false);
    printerButton->setChecked(true);
    settingsButton->setChecked(false);
    changeTabIndex(button->getId(), QString("Printer Control"));
}

void MainWindow::updateStyleSheet()
{
    qDebug() << "Updating Theme";
    QString styleKey = Settings::get("system.theme").toString();
    QString style = Settings::getTheme(styleKey);
    _terminalResponseHighlighter->setTheme(QSourceHighliter::System);
    _terminalDebugHighlighter->setTheme(QSourceHighliter::Monokai);

    dashboardButton->setIcon(QString("dashboard"));
    consoleButton->setIcon(QString("console"));
    gcodeFilesButton->setIcon(QString("files"));
    printerButton->setIcon(QString("printer"));
    settingsButton->setIcon(QString("settings"));

    dashboardTemperatureGraph->setStyleSheet(style);
    dashboardTemperatureGraph->updateStyleSheet();

    //Dashboard icons should all be the same size
    QPixmap pixmap;

    //pixmap = Settings::getThemeIcon("application-icon").pixmap(ui->applicationIcon->size());
    //ui->applicationIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("printer-error-icon").pixmap(ui->errorIcon->size());
    ui->errorIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("power-icon").pixmap(20,20);
    ui->powerButton->setIcon(pixmap);

    pixmap = Settings::getThemeIcon("loading-moonraker-icon").pixmap(100,100);
    ui->loadingMoonrakerIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("loading-klipper-icon").pixmap(100,100);
    ui->loadingKlipperIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("loading-printer-icon").pixmap(100,100);
    ui->LoadingPrinterIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("refresh-icon").pixmap(16,16);
    this->_restartAction->setIcon(pixmap);

    pixmap = Settings::getThemeIcon("power-icon").pixmap(16,16);
    this->_shutdownAction->setIcon(pixmap);

    pixmap = Settings::getThemeIcon("cancel-icon").pixmap(16,16);
    this->_closeAction->setIcon(pixmap);

    ui->applicationIcon->setPixmap(QPixmap(":/images/application-icon"));
    ui->applicationIcon->setScaledContents(true);

    ui->loadingApplicationIcon->setPixmap(QPixmap(":/images/application-icon"));
    ui->loadingApplicationIcon->setScaledContents(true);

    this->setStyleSheet(style);
    this->fileBrowser->setIcons();
    this->dashboardFileBrowser->setIcons();
    printerPage->setStyleSheet(style);
    _dashboardPage->setStyleSheet(style);
    _settingsPage->setStyleSheet(style);
}

void MainWindow::on_directoryCreateRequested(KlipperFile directory)
{
    this->_printer->console()->createDirectory(directory.fileLocation);
}

void MainWindow::on_directoryDeleteRequested(KlipperFile directory)
{
    this->_printer->console()->deleteDirectory(directory.fileLocation);
}

void MainWindow::displayError(QString message)
{
    if(ui->errorMessageFrame->graphicsEffect() == NULL)
        ui->errorMessageFrame->setGraphicsEffect(errorOpacityEffect);

    ui->errorMessageLabel->setText(message);
    errorAnimationOpacity->setStartValue(0);
    errorAnimationOpacity->setEndValue(1);
    errorAnimationOpacity->start();
    errorAnimationIn->start();
}

void MainWindow::showPopup()
{
    //this->popup->setGeometry(QRect(0,0,this->height(),this->width()));
}

void MainWindow::setMenuEnabled(bool enabled)
{
    this->dashboardButton->setEnabled(enabled);
    this->consoleButton->setEnabled(enabled);
    this->gcodeFilesButton->setEnabled(enabled);
    this->printerButton->setEnabled(enabled);
    this->settingsButton->setEnabled(enabled);
}

void MainWindow::setupPowerActions()
{
    //Restart Action
    this->_restartAction = new QAction(this);
    this->_restartAction->setText(QString("Restart System"));
    connect(_restartAction, SIGNAL(triggered(bool)), this, SLOT(on_restartAction_triggered(bool)));
    ui->powerButton->addAction(_restartAction);

    //Shutdown Action
    this->_shutdownAction = new QAction(this);
    this->_shutdownAction->setText(QString("Shutdown System"));
    connect(_shutdownAction, SIGNAL(triggered(bool)), this, SLOT(on_shutdownAction_triggered(bool)));
    ui->powerButton->addAction(_shutdownAction);

    QAction *separator = new QAction(this);
    separator->setSeparator(true);
    ui->powerButton->addAction(separator);

    //Close Action
    this->_closeAction = new QAction(this);
    this->_closeAction->setText(QString("Close Application"));
    connect(_closeAction, SIGNAL(triggered(bool)), this, SLOT(on_closeAction_triggered(bool)));
    ui->powerButton->addAction(_closeAction);
}

void MainWindow::setPrinter(Printer *printer)
{
    if(_printer != nullptr)
    {
        disconnect(_printer->console(), SIGNAL(responseReceived(KlipperResponse)), this, SLOT(on_consoleResponse(KlipperResponse)));
        disconnect(_printer->console(), SIGNAL(directoryListReceived(QList<KlipperFile>)), this, SLOT(on_directoryListReceived(QList<KlipperFile>)));
        disconnect(_printer->console(), SIGNAL(fileListReceived(QList<KlipperFile>)), this, SLOT(on_fileListReceived(QList<KlipperFile>)));
        disconnect(_printer->console(), SIGNAL(systemUpdateReceived(KlipperResponse)), this, SLOT(on_consoleSystemUpdate(KlipperResponse)));
        disconnect(_printer->console(), SIGNAL(printerUpdateReceived(KlipperResponse)), this, SLOT(on_printerStatusUpdate(KlipperResponse)));
        disconnect(_printer->console(), SIGNAL(commandSent(QString)), this, SLOT(on_commandSent(QString)));
        disconnect(_printer->console(), SIGNAL(fileDirectoryChanged(QString)), this, SLOT(on_fileDirectoryChanged(QString)));
    }

    _printer = printer;
    connect(_printer->console(), SIGNAL(responseReceived(KlipperResponse)), this, SLOT(on_consoleResponse(KlipperResponse)));
    connect(_printer->console(), SIGNAL(directoryListReceived(QList<KlipperFile>)), this, SLOT(on_directoryListReceived(QList<KlipperFile>)));
    connect(_printer->console(), SIGNAL(fileListReceived(QList<KlipperFile>)), this, SLOT(on_fileListReceived(QList<KlipperFile>)));
    connect(_printer->console(), SIGNAL(systemUpdateReceived(KlipperResponse)), this, SLOT(on_consoleSystemUpdate(KlipperResponse)));
    connect(_printer->console(), SIGNAL(printerUpdateReceived(KlipperResponse)), this, SLOT(on_printerStatusUpdate(KlipperResponse)));
    connect(_printer->console(), SIGNAL(commandSent(QString)), this, SLOT(on_commandSent(QString)));
    connect(_printer->console(), SIGNAL(fileDirectoryChanged(QString)), this, SLOT(on_fileDirectoryChanged(QString)));
}


void MainWindow::on_closeErrorButton_clicked()
{
    errorAnimationOpacity->setStartValue(1);
    errorAnimationOpacity->setEndValue(0);
    errorAnimationOpacity->start();
    errorAnimationOut->start();
}


/***
 * Parse printer status
 ***/
void MainWindow::on_printerError(QString message)
{
    //Disable all printer related stuff
    ui->printerPage->setEnabled(false);
    displayError(message);
}

void MainWindow::on_printerUpdate(Printer *printer)
{
    if(printer->id() == _printer->id())
    {
        dashboardTemperatureGraph->addTemperature("Extruder", printer->extruder(0)->currentTemp());
        dashboardExtruderProgressBar->setProgress(printer->extruder(0)->currentTemp());
        //ui->extruderPo->setText(QString::number(power));

        dashboardTemperatureGraph->addTemperature("Bed Heater", printer->bed()->currentTemp());
        dashboardBedProgressBar->setProgress(printer->bed()->currentTemp());
        printerPage->update(printer);
    }

/*
    //Parse toolhead status
    if(response["result"].toObject().contains("fan"))
    {
        QJsonObject fan = response["result"].toObject()["toolhead"].toObject();
        if(fan.contains("speed"))
        {
            //dashboardExtruderProgressBar->setProgress(extruder["temperature"].toDouble());
        }
        if(fan.contains("rpm"))
        {
            //dashboardExtruderProgressBar->setProgress(extruder["temperature"].toDouble());
        }
    }

    //Parse toolhead status
    if(response["result"].toObject().contains("toolhead"))
    {
        QJsonObject toolhead = response["result"].toObject()["toolhead"].toObject();
        if(toolhead.contains("temperature"))
        {
            //dashboardExtruderProgressBar->setProgress(extruder["temperature"].toDouble());
        }
    }
*/
}

void MainWindow::on_klipperConnected()
{
    on_dashboardMenuButton_toggled(dashboardButton);
    //ui->pageStack->setEnabled(true);
}

void MainWindow::on_klipperDisconnected()
{
    changeTabIndex(2, QString());
    //ui->pageStack->setEnabled(false);
}

void MainWindow::on_printerFound(Printer *printer)
{
    dashboardButton->setChecked(true);
    on_dashboardMenuButton_toggled(dashboardButton);
}

void MainWindow::on_printerStatusUpdate(KlipperResponse response)
{
    if(response["method"] == QString("printer.objects.subscribe"))
        ui->consoleEditTerminal->append(QJsonDocument(response.rootObject).toJson());
}

void MainWindow::on_fileRefreshRequested(QString directory)
{
    this->_printer->console()->getFileList(directory);
}

void MainWindow::on_fileListReceived(QList<KlipperFile> files)
{
    this->fileBrowser->setFileList(files);
    this->dashboardFileBrowser->setFileList(files);
}

void MainWindow::on_directoryListReceived(QList<KlipperFile> directories)
{
    this->fileBrowser->setFileList(directories);
}

void MainWindow::on_fileDirectoryChanged(QString directory)
{
    dashboardFileBrowser->setCurrentDirectory(directory);
    fileBrowser->setCurrentDirectory(directory);
}

void MainWindow::on_filePrintRequested(KlipperFile file)
{
    showPopup();
}

void MainWindow::on_fileDeleteRequested(KlipperFile file)
{
    this->_printer->console()->deleteFile(file.fileLocation);
}


void MainWindow::on_emergencyStopButton_clicked()
{
    //this->_printer->console()->emergencyStop();
}

void MainWindow::on_restartAction_triggered(bool checked)
{
    this->_printer->console()->machineReboot();
}

void MainWindow::on_shutdownAction_triggered(bool checked)
{
    this->_printer->console()->machineShutdown();
}

void MainWindow::on_closeAction_triggered(bool checked)
{
    this->close();
}


void MainWindow::on_debugTerminalButton_toggled(bool checked)
{
    if(_terminalDebugAnimationIn->state() == QPropertyAnimation::Running)
        _terminalDebugAnimationIn->stop();
    else if(_terminalDebugAnimationOut->state() == QPropertyAnimation::Running)
        _terminalDebugAnimationOut->stop();

    if(checked)
        _terminalDebugAnimationIn->start();
    else
        _terminalDebugAnimationOut->start();
}


void MainWindow::on_klipperRestartButton_clicked()
{
    changeTabIndex(2, QString());
    _printer->console()->restartKlipper();
}


void MainWindow::on_firmwareRestartButton_clicked()
{
    changeTabIndex(2, QString());
    _printer->console()->restartFirmware();
}


void MainWindow::on_powerButton_clicked()
{
    on_closeAction_triggered(true);
}

void MainWindow::on_settingsPage_printerAdded(PrinterDefinition definition)
{
    _dashboardPage->loadPrinters();
}

