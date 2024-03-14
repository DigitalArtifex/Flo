#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    dashboardButton->setChecked(true);
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

    ui->dashboardBedLayout->addWidget(dashboardBedProgressBar);
    ui->horizontalLayout_12->addWidget(dashboardExtruderProgressBar);
    ui->dashboardChamberLayout->addWidget(dashboardChamberProgressBar);
    ui->dashboardExtruderLayout_2->addWidget(dashboardExtruder1ProgressBar);
    ui->dashboardExtruderLayout_3->addWidget(dashboardExtruder2ProgressBar);
    ui->dashboardExtruderLayout_4->addWidget(dashboardExtruder3ProgressBar);
    //ui->dashboardExtruderFanLayout->addWidget(dashboardExtruderFanProgressBar);
    //ui->dashboardPartsFanLayout->addWidget(dashboardPartsFanProgressBar);
    ui->dashboardSystemTemperatureLayout->addWidget(dashboardSystemFanProgressBar);
    ui->dashboardSystemCpuLoadLayout->addWidget(dashboardSystemCpuLoadProgressBar);
    ui->dashboardSystemMemoryLoadLayout->addWidget(dashboardSystemMemoryLoadProgressBar);

    QGridLayout *layout = (QGridLayout *)ui->temperatureWidgetContents->layout();
    layout->addWidget(dashboardTemperatureGraph,2,0,1,1);

    ui->errorMessageFrame->setMaximumHeight(0);

    showMaximized();

    Settings::load();
    console.loadPresets();

    connect(&console, SIGNAL(responseReceived(KlipperResponse)), this, SLOT(on_consoleResponse(KlipperResponse)));
    connect(&console, SIGNAL(directoryListReceived(QList<KlipperFile>)), this, SLOT(on_directoryListReceived(QList<KlipperFile>)));
    connect(&console, SIGNAL(fileListReceived(QList<KlipperFile>)), this, SLOT(on_fileListReceived(QList<KlipperFile>)));
    connect(&console, SIGNAL(systemUpdateReceived(KlipperResponse)), this, SLOT(on_consoleSystemUpdate(KlipperResponse)));
    connect(&console, SIGNAL(printerUpdateReceived(KlipperResponse)), this, SLOT(on_printerStatusUpdate(KlipperResponse)));
    connect(&console, SIGNAL(printerUpdate(Printer*)), this, SLOT(on_printerUpdate(Printer*)));
    connect(&console, SIGNAL(commandSent(QString)), this, SLOT(on_commandSent(QString)));
    connect(&console, SIGNAL(klipperConnected()), this, SLOT(on_klipperConnected()));
    connect(&console, SIGNAL(klipperDisconnected()), this, SLOT(on_klipperDisconnected()));
    connect(&console, SIGNAL(fileDirectoryChanged(QString)), this, SLOT(on_fileDirectoryChanged(QString)));

    console.connectKlipper();

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

    ui->settingsPageTitleBar->setHidden(true);
    ui->dashboardPageTitleBar->setHidden(true);
    ui->terminalPageTitleBar->setHidden(true);

    setupUiClasses();

    connect(this,SIGNAL(PrinterError(QString)),this,SLOT(on_printerError(QString)));

    QList<ConsolePreset> consolePresets = console.getPresetList();

    for(int i = 0; i < consolePresets.count(); i++)
    {
        if(consolePresets[i].type == QString("system"))
            continue;

        ui->consolePresetSelector->insertItem(i, consolePresets[i].name);
        ui->consolePresetSelector->setItemIcon(i, Settings::getThemeIcon(consolePresets[i].icon));
    }

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
    layout = (QGridLayout *)ui->filesWidgetContents->layout();
    layout->addWidget(dashboardFileBrowser,2,0,1,1);

    printerPage = new PrinterPage(this);
    ui->printerPage->layout()->addWidget(printerPage);

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

    _dashboardFilesWidgetAnimation = new DashboardAnimation(ui->filesWidget, DashboardAnimation::MinMaxHeight, this);
    _dashboardFilesWidgetAnimation->setHeightOut(50);
    _dashboardFilesWidgetAnimation->setHeightIn(445);

    _dashboardWebcamWidgetAnimation = new DashboardAnimation(ui->webcamWidget, DashboardAnimation::MinMaxHeight, this);
    _dashboardWebcamWidgetAnimation->setHeightOut(50);
    _dashboardWebcamWidgetAnimation->setHeightIn(445);

    _dashboardPrinterWidgetAnimation = new DashboardAnimation(ui->printerWidget, DashboardAnimation::MinMaxHeight, this);
    _dashboardPrinterWidgetAnimation->setHeightOut(50);
    _dashboardPrinterWidgetAnimation->setHeightIn(700);

    _dashboardSystemWidgetAnimation = new DashboardAnimation(ui->systemWidget, DashboardAnimation::MinMaxHeight, this);
    _dashboardSystemWidgetAnimation->setHeightOut(50);
    _dashboardSystemWidgetAnimation->setHeightIn(600);

    _dashboardTemperaturesWidgetAnimation = new DashboardAnimation(ui->temperatureWidget, DashboardAnimation::MinMaxHeight, this);
    _dashboardTemperaturesWidgetAnimation->setHeightOut(50);
    _dashboardTemperaturesWidgetAnimation->setHeightIn(600);

    _terminalResponseHighlighter = new QSourceHighliter(ui->consoleEditTerminal->document());
    _terminalResponseHighlighter->setCurrentLanguage(QSourceHighliter::CodeJSON);
    _terminalResponseHighlighter->setTheme(QSourceHighliter::System);
    _terminalDebugHighlighter = new QSourceHighliter(ui->sentCommands->document());
    _terminalDebugHighlighter->setCurrentLanguage(QSourceHighliter::CodeJSON);

    setupPowerActions();
    updateStyleSheet();

    ui->filesWidgetToggleButton->setIcon(Settings::getThemeIcon(QString("collapse-icon")));
    ui->webcamWidgetToggleButton->setIcon(Settings::getThemeIcon(QString("collapse-icon")));
    ui->systemWidgetToggleButton->setIcon(Settings::getThemeIcon(QString("collapse-icon")));
    ui->temperatureWidgetToggleButton->setIcon(Settings::getThemeIcon(QString("collapse-icon")));
    ui->printerWidgetToggleButton->setIcon(Settings::getThemeIcon(QString("collapse-icon")));

    startup = false;
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

        //Parse Server Info
        if(response["method"] == QString("server.connection.identify"))
        {
            QJsonObject result = response["result"].toObject();

            ui->dashboardMoonrakerConnectionStatus->setText("Connected");
            ui->dashboardMoonrakerConnectionStatus->setProperty("class", "MoonrakerStatus Connected ConnectionStatus");
        }
        else if(response["method"] == QString("server.info"))
        {
            QJsonObject result = response["result"].toObject();

            if(result.contains("moonraker_version"))
                ui->versionInfo->setText(result["moonraker_version"].toString());

            if(result["klippy_connected"].toBool())
            {
                ui->dashboardKlipperConnectionStatus->setText("Connected");

                if(result["klippy_state"].toString() == "ready")
                    ui->dashboardKlipperConnectionStatus->setProperty("class", "KlipperStatus Connected ConnectionStatus ReadyState");
                else if(result["klippy_state"].toString() == "error")
                    ui->dashboardKlipperConnectionStatus->setProperty("class", "KlipperStatus Connected ConnectionStatus ErrorState");
                else
                    ui->dashboardKlipperConnectionStatus->setProperty("class", "KlipperStatus Connected ConnectionStatus");

            }
            else
            {
                ui->dashboardKlipperConnectionStatus->setText("Disconnected");
                ui->dashboardKlipperConnectionStatus->setProperty("class", "KlipperStatus Disconnected ConnectionStatus");
            }
        }
        else if(response["method"] == QString("printer.info"))
        {
            QJsonObject result = response["result"].toObject();

            if(result["state"].toString() == QString("error"))
            {
                emit(PrinterError(result["state_message"].toString()));
            }
            else if(result["state"].toString() == QString("ready"))
            {
                ui->dashboardPrinterConnectionStatus->setProperty("class", "PrinterStatus Connected ConnectionStatus");
                ui->dashboardPrinterConnectionStatus->setText("Connected");
                ui->printerPage->setEnabled(true);
                ui->printerWidget->setEnabled(true);
            }

            ui->systemInfoList->clear();
            if(result.contains(QString("cpu_info")))
                ui->systemInfoList->addItem(result["cpu_info"].toString());
            if(result.contains(QString("hostname")))
                ui->hostnameStatus->setText(result["hostname"].toString());
            if(result.contains(QString("state_message")))
                ui->systemInfoList->addItem(QString("Status: ") + result["state_message"].toString());
        }
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

void MainWindow::on_consoleSystemUpdate(KlipperResponse response)
{
    //Parse heatbed status
    if(response["result"].toObject().contains("system_cpu_usage"))
    {
        QJsonObject system = response["result"].toObject()["system_cpu_usage"].toObject();
        qreal cpuAverage = 0.0;
        int cpuCount = 0;
        QJsonObject cpuLoadArray = system["system_cpu_usage"].toObject();

        QJsonObject::Iterator cpuIterator;

        for(cpuIterator = cpuLoadArray.begin(); cpuIterator != cpuLoadArray.end(); cpuIterator++)
        {
            cpuAverage += cpuIterator->toDouble();
            cpuCount++;
        }

        cpuAverage /= cpuCount;

        this->dashboardSystemCpuLoadProgressBar->setProgress((int)cpuAverage);
    }

    //Parse heatbed status
    if(response["result"].toObject().contains("system_memory"))
    {
        QJsonObject memoryLoadObject = response["result"].toObject()["system_memory"].toObject();
        this->dashboardSystemMemoryLoadProgressBar->setMaximum(memoryLoadObject["total"].toDouble());
        this->dashboardSystemMemoryLoadProgressBar->setProgress(memoryLoadObject["used"].toDouble());
    }
}

void MainWindow::on_consolePresetSelector_currentChanged(int index)
{
    if(startup)
        return;

    QString selectedPreset = ui->consolePresetSelector->itemText(index);
    console.sendPreset(selectedPreset, KlipperMessage::Console);
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
        console.sendCommand(command, KlipperMessage::User);
    }
}

void MainWindow::setupUiClasses()
{
    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Window"));
    ui->PageContainer->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContainer"));
    ui->emergencyStopButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "EmergencyStopButton"));
    ui->consolePage->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->moonrakerPage->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->settingsPage->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->dashboardMoonrakerConnectionStatus->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MoonrakerStatus" << "Disconnected" << "ConnectionStatus" ));
    ui->dashboardKlipperConnectionStatus->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "KlipperStatus" << "Disconnected" << "ConnectionStatus" ));
    ui->dashboardPrinterConnectionStatus->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PrinterStatus" << "Disconnected" << "ConnectionStatus" ));
    ui->menuBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuBar"));
    ui->errorMessageFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupFrame" << "ErrorFrame" ));
    ui->errorMessageLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ErrorText" ));
    ui->errorTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ErrorTitle" ));
    ui->pageTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageTitle" ));
    ui->dashboardActionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageActionBar" ));



    //Menu Buttons
    ui->menuFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Menu"));
    ui->PageContainer->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContainer"));
    ui->menuTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuTitleBar"));
    ui->applicationIcon->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ApplicationIcon"));
    dashboardButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuButton" << "DashboardMenuButton"));
    consoleButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuButton" << "TerminalMenuButton"));

    //Dashboard widgets
    ui->webcamWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget"));
    ui->filesWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget"));
    ui->systemWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget"));
    ui->printerWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget"));
    ui->temperatureWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget"));

    //Dashboard widget titles
    ui->webcamTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidgetTitle"));
    ui->filesTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidgetTitle"));
    ui->systemTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidgetTitle"));
    ui->printerTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidgetTitle"));
    ui->temperatureTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidgetTitle"));
    ui->webcamIcon->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidgetIcon"));
    ui->filesIcon->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidgetIcon"));
    ui->systemIcon->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidgetIcon"));
    ui->printerIcon->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidgetIcon"));
    ui->temperaturesIcon->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidgetIcon"));


    dashboardFileBrowser->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget"));
    ui->dashboardWebcamView->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget"));
    ui->noVideoFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget"));
    ui->cpuFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget"));
    ui->memoryFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget"));
    ui->temperatureFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget"));
    ui->statusFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget"));

    //Dashboard scroll area
    ui->scrollArea->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardScrollArea"));
    ui->dashboardContents->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardContents"));

    //Page Titles
    ui->terminalPageTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageTitle"));
    ui->terminalPageTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageTitleBar"));
    ui->dashboardPageTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageTitle"));
    ui->dashboardPageTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageTitleBar"));
    ui->terminalPageActionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageActionBar"));
    ui->settingsPageTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageTitle"));
    ui->settingsPageTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageTitleBar"));
    ui->settingsPageActionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageActionBar"));

    //Icons
    ui->systemIcon->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardIcon"));
    ui->powerButton->setIcon(Settings::getThemeIcon(QString("power-icon")));

    //Loading widgets
    ui->loadingKlipperFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget"));
    ui->loadingMoonrakerFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget"));
    ui->loadingPrinterFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget"));
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
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

    ui->settingsKlipperLocationEdit->clear();
    ui->settingsKlipperLocationEdit->setText(Settings::get("system.klipper.com_location").toString());
    ui->settingsPresetLocationEdit->clear();
    ui->settingsPresetLocationEdit->setText(Settings::get("system.preset_location").toString());

    QStringList themes = Settings::getThemeList();
    ui->themeSelector->clear();
    ui->themeSelector->addItems(themes);

    QString styleKey = Settings::get("system.theme").toString();
    ui->themeSelector->setCurrentText(styleKey);

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


void MainWindow::on_settingsApplyButton_clicked()
{
    QString styleKey = ui->themeSelector->currentText();
    Settings::set("system.theme", styleKey);
    QString style = Settings::getTheme(styleKey);
    Settings::save();

    this->setStyleSheet(style);
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
    QSize size(ui->temperaturesIcon->width(), ui->temperaturesIcon->height());
    QPixmap pixmap = Settings::getThemeIcon("temperature-icon").pixmap(size);
    ui->temperaturesIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("webcam-icon").pixmap(size);
    ui->webcamIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("files").pixmap(size);
    ui->filesIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("temperature-icon").pixmap(size);
    ui->temperaturesIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("printer").pixmap(size);
    ui->printerIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("temperature-icon").pixmap(size);
    ui->temperaturesIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("system-icon").pixmap(size);
    ui->systemIcon->setPixmap(pixmap);

    //pixmap = Settings::getThemeIcon("application-icon").pixmap(ui->applicationIcon->size());
    //ui->applicationIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("printer-error-icon").pixmap(ui->errorIcon->size());
    ui->errorIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("no-video-icon").pixmap(QSize(100,100));
    ui->noVideoIcon->setPixmap(pixmap);

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

    this->setStyleSheet(style);
    this->fileBrowser->setIcons();
    this->dashboardFileBrowser->setIcons();
    printerPage->setStyleSheet(style);
}

void MainWindow::on_directoryCreateRequested(KlipperFile directory)
{
    this->console.createDirectory(directory.fileLocation);
}

void MainWindow::on_directoryDeleteRequested(KlipperFile directory)
{
    this->console.deleteDirectory(directory.fileLocation);
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


void MainWindow::on_closeErrorButton_clicked()
{
    errorAnimationOpacity->setStartValue(1);
    errorAnimationOpacity->setEndValue(0);
    errorAnimationOpacity->start();
    errorAnimationOut->start();
}

void MainWindow::on_extrsuionFactorSlider_valueChanged(int value)
{
    QObject::disconnect(ui->extrusionFactorEdit, SIGNAL(textChanged(QString)), this, SLOT(on_extrusionFactorEdit_textChanged(QString)));
    double newValue = (double)value / 100;
    ui->extrusionFactorEdit->setText(QString::number(newValue, 'g'));
    QObject::connect(ui->extrusionFactorEdit, SIGNAL(textChanged(QString)), this, SLOT(on_extrusionFactorEdit_textChanged(QString)));
}


void MainWindow::on_extrusionFactorEdit_textChanged(const QString &arg1)
{
    QObject::disconnect(ui->extrsuionFactorSlider, SIGNAL(valueChanged(int)), this, SLOT(on_extrsuionFactorSlider_valueChanged(int)));
    double value = arg1.toDouble();
    ui->extrsuionFactorSlider->setValue(value * 100);
    QObject::connect(ui->extrsuionFactorSlider, SIGNAL(valueChanged(int)), this, SLOT(on_extrsuionFactorSlider_valueChanged(int)));
}

void MainWindow::on_extrsuionFactorSlider_2_valueChanged(int value)
{
    QObject::disconnect(ui->extrusionFactorEdit_2, SIGNAL(textChanged(QString)), this, SLOT(on_extrusionFactorEdit_textChanged(QString)));
    double newValue = (double)value / 100;
    ui->extrusionFactorEdit_2->setText(QString::number(newValue, 'g'));
    QObject::connect(ui->extrusionFactorEdit_2, SIGNAL(textChanged(QString)), this, SLOT(on_extrusionFactorEdit_textChanged(QString)));
}

void MainWindow::on_extrusionFactorEdit_2_textChanged(const QString &arg1)
{
    QObject::disconnect(ui->extrsuionFactorSlider_2, SIGNAL(valueChanged(int)), this, SLOT(on_extrsuionFactorSlider_valueChanged(int)));
    double value = arg1.toDouble();
    ui->extrsuionFactorSlider_2->setValue(value * 100);
    QObject::connect(ui->extrsuionFactorSlider_2, SIGNAL(valueChanged(int)), this, SLOT(on_extrsuionFactorSlider_valueChanged(int)));
}


/***
 * Parse printer status
 ***/
void MainWindow::on_printerError(QString message)
{
    //Disable all printer related stuff
    ui->printerPage->setEnabled(false);
    ui->printerWidgetContents->setEnabled(false);
    displayError(message);
}

void MainWindow::on_printerUpdate(Printer *printer)
{
    dashboardTemperatureGraph->addTemperature("Extruder", printer->extruder(0)->currentTemp());
    dashboardExtruderProgressBar->setProgress(printer->extruder(0)->currentTemp());
    ui->dashboardExtruderTargetTempLabel->setText(QString::number(printer->extruder(0)->targetTemp()) + QString("C"));

    ui->extruderPressureAdvanceEdit->setText(QString::number(printer->extruder(0)->pressureAdvance()));
    ui->extruderSmoothTimeEdit->setText(QString::number(printer->extruder(0)->smoothTime()));
    //ui->extruderPo->setText(QString::number(power));
    ui->materialWidget->setEnabled(printer->extruder(0)->canExtrude());

    dashboardTemperatureGraph->addTemperature("Bed Heater", printer->bed()->currentTemp());
    dashboardBedProgressBar->setProgress(printer->bed()->currentTemp());
    ui->bedTargetTempLabel->setText(QString::number(printer->bed()->targetTemp()) + QString("C"));
    ui->bedPowerLabel->setText(QString::number(printer->bed()->power()) + QString(""));

    ui->dashboardPartsFanLabel->setText(QString::number(printer->toolhead()->fan()->speed()));

    printerPage->update(printer);

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

void MainWindow::on_printerStatusUpdate(KlipperResponse response)
{
    if(response["method"] == QString("printer.objects.subscribe"))
        ui->consoleEditTerminal->append(QJsonDocument(response.rootObject).toJson());
}

void MainWindow::on_fileRefreshRequested(QString directory)
{
    this->console.getFileList(directory);
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
    this->console.deleteFile(file.fileLocation);
}


void MainWindow::on_emergencyStopButton_clicked()
{
    //this->console.emergencyStop();
}

void MainWindow::on_restartAction_triggered(bool checked)
{
    this->console.machineReboot();
}

void MainWindow::on_shutdownAction_triggered(bool checked)
{
    this->console.machineShutdown();
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


void MainWindow::on_filesWidgetToggleButton_toggled(bool checked)
{
    if(checked)
    {
        ui->filesWidgetToggleButton->setIcon(Settings::getThemeIcon(QString("expand-icon")));
        ui->filesWidgetContents->setHidden(true);
        _dashboardFilesWidgetAnimation->hide();
    }
    else
    {
        ui->filesWidgetToggleButton->setIcon(Settings::getThemeIcon(QString("collapse-icon")));
        ui->filesWidgetContents->setHidden(false);
        _dashboardFilesWidgetAnimation->show();
    }
}


void MainWindow::on_webcamWidgetToggleButton_toggled(bool checked)
{
    if(checked)
    {
        ui->webcamWidgetToggleButton->setIcon(Settings::getThemeIcon(QString("expand-icon")));
        ui->webcamWidgetContents->setHidden(true);
        _dashboardWebcamWidgetAnimation->hide();
    }
    else
    {
        ui->webcamWidgetToggleButton->setIcon(Settings::getThemeIcon(QString("collapse-icon")));
        ui->webcamWidgetContents->setHidden(false);
        _dashboardWebcamWidgetAnimation->show();
    }
}


void MainWindow::on_systemWidgetToggleButton_toggled(bool checked)
{
    if(checked)
    {
        ui->systemWidgetToggleButton->setIcon(Settings::getThemeIcon(QString("expand-icon")));
        ui->systemWidgetContents->setHidden(true);
        _dashboardSystemWidgetAnimation->hide();
    }
    else
    {
        ui->systemWidgetToggleButton->setIcon(Settings::getThemeIcon(QString("collapse-icon")));
        ui->systemWidgetContents->setHidden(false);
        _dashboardSystemWidgetAnimation->show();
    }
}


void MainWindow::on_temperatureWidgetToggleButton_toggled(bool checked)
{
    if(checked)
    {
        ui->temperatureWidgetToggleButton->setIcon(Settings::getThemeIcon(QString("expand-icon")));
        ui->temperatureWidgetContents->setHidden(true);
        _dashboardTemperaturesWidgetAnimation->hide();
    }
    else
    {
        ui->temperatureWidgetToggleButton->setIcon(Settings::getThemeIcon(QString("collapse-icon")));
        ui->temperatureWidgetContents->setHidden(false);
        _dashboardTemperaturesWidgetAnimation->show();
    }
}

void MainWindow::on_printerWidgetToggleButton_toggled(bool checked)
{
    if(checked)
    {
        ui->printerWidgetToggleButton->setIcon(Settings::getThemeIcon(QString("expand-icon")));
        ui->printerWidgetContents->setHidden(true);
        _dashboardPrinterWidgetAnimation->hide();
    }
    else
    {
        ui->printerWidgetToggleButton->setIcon(Settings::getThemeIcon(QString("collapse-icon")));
        ui->printerWidgetContents->setHidden(false);
        _dashboardPrinterWidgetAnimation->show();
    }
}


void MainWindow::on_klipperRestartButton_clicked()
{
    changeTabIndex(2, QString());
    console.restartKlipper();
}


void MainWindow::on_firmwareRestartButton_clicked()
{
    changeTabIndex(2, QString());
    console.restartFirmware();
}

