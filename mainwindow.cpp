#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "system/printerpool.h"

//Pages
#include "system/settings.h"
#include "pages/settings/settingspage.h"
#include "pages/printer/printerpage.h"
#include "pages/dashboard/dashboardpage.h"
#include "pages/loading/loadingpage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setEnabled(false);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowIcon(QIcon(":/images/application-icon"));

    showMaximized();

    _titleOpacityEffect = new QGraphicsOpacityEffect(this);
    ui->pageTitle->setGraphicsEffect(_titleOpacityEffect);
    _titleOpacityAnimation = new QPropertyAnimation(_titleOpacityEffect, "opacity");
    _titleOpacityAnimation->setDuration(500);

    Settings::load();
    setStyleSheet(Settings::currentTheme());

    LoadingPage *page = new LoadingPage(this);
    _loadingPage = new QAnimatedWidget(this);
    _loadingPage->setWidget(page);
    _loadingPage->setHidden(true);
    ui->PageContainer->layout()->addWidget(_loadingPage);

    _currentPage = _loadingPage;
    _currentPage->setOpacityIn(1);
    _currentPage->setOpacityOut(0);
    _currentPage->setPositionIn(_pagePositionIn);
    _currentPage->setPositionOut(QPoint(_pageSize.width(), 0));
    _currentPage->setDuration(500);
    _currentPage->animateIn();

    _initTimer = new QTimer(this);
    _initTimer->setInterval(1000);
    _initTimer->setSingleShot(true);

    connect(_initTimer, SIGNAL(timeout()), this, SLOT(on_initAsync()));
    _initTimer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changePage(QAnimatedWidget *page, QString title)
{
    //Disable Buttons
    if(_dashboardButton)
        _dashboardButton->setEnabled(false);

    if(_settingsButton)
        _settingsButton->setEnabled(false);

    for(int i = 0; i < _printerButtons.count(); i++)
        _printerButtons[i]->setEnabled(false);

    //Title
    connect(_titleOpacityAnimation, SIGNAL(finished()), this, SLOT(on_titleOpacityAnimation_finished()));
    _nextTitle = title;
    _titleOpacityAnimation->setStartValue(1);
    _titleOpacityAnimation->setEndValue(0);
    ui->pageTitle->setGraphicsEffect(_titleOpacityEffect);

    _titleOpacityAnimation->start();

    //Page
    qint32 width = this->width() - ui->menuFrame->width();
    qint32 height = this->height() - ui->menuBar->height();

    _pageSize = QSize(width, height);
    _pagePositionIn = QPoint(0, 0);
    _pagePositionOut = QPoint(_pageSize.width(), _pageSize.height());

    if(page)
    {
        _nextPage = page;
        _nextPage->setOpacityIn(1);
        _nextPage->setOpacityOut(0);
        _nextPage->setPositionIn(_pagePositionIn);
        _nextPage->setPositionOut(QPoint(_pageSize.width(), 0));
        _nextPage->setDuration(500);
    }

    if(_currentPage)
    {
        connect(_currentPage, SIGNAL(animatedOut()), this, SLOT(on_currentPage_animationOut_finished()));

        _currentPage->setOpacityIn(1);
        _currentPage->setOpacityOut(0);
        _currentPage->setPositionIn(_pagePositionIn);
        _currentPage->setPositionOut(QPoint(0, _pageSize.height()));
        _currentPage->setDuration(250);

        _currentPage->animateOut();
    }
    else
    {
        connect(_nextPage, SIGNAL(animatedIn()), this, SLOT(on_nextPage_animationIn_finished()));
        _nextPage->setHidden(false);
        _nextPage->animateIn();
    }
}

void MainWindow::init()
{
}

void MainWindow::online()
{
    setEnabled(true);

    _dashboardButton = new MenuButton(0, ui->menuFrame);
    _dashboardButton->setText(QString("Dashboard"));
    _dashboardButton->setIcon("dashboard");
    _dashboardButton->setChecked(true);
    ui->menuButtonLayout->addWidget(_dashboardButton);
    connect(_dashboardButton, SIGNAL(clicked(MenuButton*)), this, SLOT(on_dashboardMenuButton_toggled(MenuButton*)));

    _settingsButton = new MenuButton(3, ui->menuFrame);
    _settingsButton->setText(QString("Settings"));
    _settingsButton->setIcon("setting");
    _settingsButton->setChecked(false);
    ui->menuButtonLayout->addWidget(_settingsButton);
    connect(_settingsButton, SIGNAL(clicked(MenuButton*)), this, SLOT(on_settingsMenuButton_toggled(MenuButton*)));

    _titleOpacityEffect = new QGraphicsOpacityEffect(this);

    PrinterDefinitionList printers = Flo::settings()->printers();
    ui->menuButtonLayout->removeWidget(_settingsButton);

    foreach(PrinterDefinition definition, printers)
    {
        PrinterPage *printerPage = new PrinterPage(this);
        printerPage->setPrinter(Flo::printerPool()->getPrinterById(definition.id));

        QAnimatedWidget *animatedPage = new QAnimatedWidget(this);
        animatedPage->setWidget(printerPage);
        animatedPage->setHidden(true);
        ui->PageContainer->layout()->addWidget(animatedPage);

        MenuButton *printerButton = new MenuButton(_printerPages.count(), this);
        printerButton->setIcon(QString("printer-icon"));
        printerButton->setText(definition.name);
        ui->menuButtonLayout->addWidget(printerButton);

        _printerPages.append(animatedPage);
        _printerButtons.append(printerButton);

        connect(printerButton, SIGNAL(clicked(MenuButton*)), this, SLOT(on_printerMenuButton_toggled(MenuButton*)));
    }

    ui->menuButtonLayout->addWidget(_settingsButton);

    for(int i = 0; i < _printerPages.count(); i++)
        _printerPages[i]->resize(_pageSize);

    setupPowerActions();

    setupUiClasses();
    updateStyleSheet();

    on_dashboardMenuButton_toggled(_dashboardButton);
}

void MainWindow::setupUiClasses()
{
    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Window"));
    ui->PageContainer->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContainer"));
    ui->emergencyStopButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "EmergencyStopButton"));
    //_settingsPage->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));

    ui->menuBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuBar"));
    ui->pageTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageTitle" ));

    //Menu Buttons
    ui->menuFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Menu"));
    ui->PageContainer->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContainer"));
    ui->menuTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuTitleBar"));
    ui->applicationIcon->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ApplicationIcon"));
    _dashboardButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuButton" << "DashboardMenuButton"));
    _settingsButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuButton" << "DashboardMenuButton"));


    //Icons
    ui->powerButton->setIcon(Settings::getThemeIcon(QString("power-icon")));
}

void MainWindow::on_dashboardMenuButton_toggled(MenuButton* button)
{
    _dashboardButton->setChecked(true);

    for(int i = 0; i < _printerButtons.count(); i++)
        _printerButtons[i]->setChecked(false);

    _settingsButton->setChecked(false);

    if(!_dashboardPage)
    {
        DashboardPage *dashboard = new DashboardPage();
        _dashboardPage = new QAnimatedWidget(ui->PageContainer);
        _dashboardPage->setWidget(dashboard);
        _dashboardPage->resize(_pageSize);
        _dashboardPage->setHidden(true);
    }

    changePage(_dashboardPage, QString("Dashboard"));
}

void MainWindow::on_settingsMenuButton_toggled(MenuButton* button)
{
    _dashboardButton->setChecked(false);

    for(int i = 0; i < _printerButtons.count(); i++)
        _printerButtons[i]->setChecked(false);

    _settingsButton->setChecked(true);

    if(!_settingsPage)
    {
        SettingsPage *settings = new SettingsPage();
        _settingsPage = new QAnimatedWidget(ui->PageContainer);
        _settingsPage->setWidget(settings);
        _settingsPage->setHidden(true);
        _settingsPage->resize(_pageSize);
        connect(_settingsPage, SIGNAL(printerAdded(PrinterDefinition)), this, SLOT(on_settingsPage_printerAdded(PrinterDefinition)));
    }

    changePage(_settingsPage, QString("Settings"));
}

void MainWindow::on_currentPage_animationOut_finished()
{
    disconnect(_currentPage, SIGNAL(animatedOut()), this, SLOT(on_currentPage_animationOut_finished()));
    connect(_nextPage, SIGNAL(animatedIn()), this, SLOT(on_nextPage_animationIn_finished()));
    ui->PageContainer->layout()->removeWidget(_currentPage);
    ui->PageContainer->layout()->addWidget(_nextPage);

    _nextPage->setHidden(false);
    _nextPage->animateIn();
}

void MainWindow::on_nextPage_animationIn_finished()
{
    disconnect(_nextPage, SIGNAL(animatedIn()), this, SLOT(on_nextPage_animationIn_finished()));

    _currentPage = _nextPage;
    _nextPage = nullptr;

    //Enable Buttons
    if(_dashboardButton)
        _dashboardButton->setEnabled(true);

    if(_settingsButton)
        _settingsButton->setEnabled(true);

    for(int i = 0; i < _printerButtons.count(); i++)
        _printerButtons[i]->setEnabled(true);
}

void MainWindow::on_titleOpacityAnimation_finished()
{
    disconnect(_titleOpacityAnimation, SIGNAL(finished()), this, SLOT(on_titleOpacityAnimation_finished()));

    _currentTitle = this->_nextTitle;
    ui->pageTitle->setText(_currentTitle);
    ui->pageTitle->setGraphicsEffect(_titleOpacityEffect);
    _nextTitle = "";
    _titleOpacityAnimation->setStartValue(0);
    _titleOpacityAnimation->setEndValue(1);
    _titleOpacityAnimation->start();
}

void MainWindow::on_printerMenuButton_toggled(MenuButton* button)
{
    _dashboardButton->setChecked(false);
    _settingsButton->setChecked(false);

    QString title;

    for(int i = 0; i < _printerPages.count(); i++)
    {
        if(button->getId() == i)
        {
            title = button->getText();
            _printerButtons[i]->setChecked(true);
        }
        else
            _printerButtons[i]->setChecked(false);
    }

    changePage(_printerPages[button->getId()], title);
}

void MainWindow::updateStyleSheet()
{
    qDebug() << "Updating Theme";
    QString styleKey = Settings::get("system.theme").toString();
    QString style = Settings::getTheme(styleKey);

    _dashboardButton->setIcon(QString("dashboard"));

    for(int i = 0; i < _printerButtons.count(); i++)
        _printerButtons[i]->setIcon(QString("printer"));

    _settingsButton->setIcon(QString("settings"));

    //Dashboard icons should all be the same size
    QPixmap pixmap;

    pixmap = Settings::getThemeIcon("power-icon").pixmap(20,20);
    ui->powerButton->setIcon(pixmap);

    pixmap = Settings::getThemeIcon("refresh-icon").pixmap(16,16);
    this->_restartAction->setIcon(pixmap);

    pixmap = Settings::getThemeIcon("power-icon").pixmap(16,16);
    this->_shutdownAction->setIcon(pixmap);

    pixmap = Settings::getThemeIcon("cancel-icon").pixmap(16,16);
    this->_closeAction->setIcon(pixmap);

    ui->applicationIcon->setPixmap(QPixmap(":/images/application-icon"));
    ui->applicationIcon->setScaledContents(true);

    this->setStyleSheet(style);

    for(int i = 0; i < _printerButtons.count(); i++)
        _printerButtons[i]->setIcon(QString("printer"));

    if(_dashboardPage != nullptr)
        _dashboardPage->setStyleSheet(style);

    if(_settingsPage != nullptr)
        _settingsPage->setStyleSheet(style);
}

void MainWindow::showPopup()
{
    //this->popup->setGeometry(QRect(0,0,this->height(),this->width()));
}

void MainWindow::setMenuEnabled(bool enabled)
{
    _dashboardButton->setEnabled(enabled);

    for(int i = 0; i < _printerButtons.count(); i++)
        _printerButtons[i]->setEnabled(true);

    _settingsButton->setEnabled(enabled);
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

void MainWindow::on_initAsync()
{
    connect(Flo::instance(), SIGNAL(loadingFinished()), this, SLOT(online()));
    Flo::instance()->start(this);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    qint32 width = this->width() - ui->menuFrame->width();
    qint32 height = this->height() - ui->menuBar->height();

    _pageSize = QSize(width, height);
    _pagePositionIn = QPoint(ui->menuFrame->width(), ui->menuBar->height());
    _pagePositionOut = QPoint(this->width(), ui->menuBar->height());

    if(_dashboardPage)
        _dashboardPage->resize(_pageSize);

    if(_settingsPage)
        _settingsPage->resize(_pageSize);

    for(int i = 0; i < _printerPages.count(); i++)
        _printerPages[i]->resize(_pageSize);
}


void MainWindow::on_emergencyStopButton_clicked()
{
    //this->_printer->console()->emergencyStop();
}

void MainWindow::on_restartAction_triggered(bool checked)
{
}

void MainWindow::on_shutdownAction_triggered(bool checked)
{
}

void MainWindow::on_closeAction_triggered(bool checked)
{
    this->close();
}


void MainWindow::on_powerButton_clicked()
{
    on_closeAction_triggered(true);
}

void MainWindow::on_settingsPage_printerAdded(PrinterDefinition definition)
{
}

void MainWindow::on_loadingAnimation_finished()
{
    _loadingGif->stop();
    delete _loadingGif;
    delete _loadingLabel;
    delete _loadingAnimation;
    _loadingLabel = nullptr;
    _loadingGif = nullptr;
    _loadingAnimation = nullptr;
}

