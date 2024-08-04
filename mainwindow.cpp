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

    m_titleOpacityEffect = new QGraphicsOpacityEffect(this);
    ui->pageTitle->setGraphicsEffect(m_titleOpacityEffect);
    m_titleOpacityAnimation = new QPropertyAnimation(m_titleOpacityEffect, "opacity");
    m_titleOpacityAnimation->setDuration(500);

    Settings::load();

    m_graphicsScene = new QGraphicsScene(this);
    ui->windowWidget->setParent(0);

    QGraphicsProxyWidget *proxy = m_graphicsScene->addWidget(ui->windowWidget);
    proxy->setPos(0,0);
    proxy->setZValue(1);
    ui->graphicsView->setScene(m_graphicsScene);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();

    setFixedSize(screenGeometry.size());
    ui->windowWidget->setFixedSize(screenGeometry.size());
    ui->windowWidget->setEnabled(true);

    m_initTimer = new QTimer(this);
    m_initTimer->setInterval(50);
    m_initTimer->setSingleShot(true);

    ui->windowWidget->setStyleSheet(Settings::currentTheme());

    connect(m_initTimer, SIGNAL(timeout()), this, SLOT(on_initAsync()));
    m_initTimer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changePage(QAnimatedWidget *page, QString title)
{
    if(page == m_currentPage)
        return;

    qDebug() << "Changing page to " << title;

    //Disable Buttons
    if(m_dashboardButton)
        m_dashboardButton->setEnabled(false);

    if(m_settingsButton)
        m_settingsButton->setEnabled(false);

    for(int i = 0; i < m_printerButtons.count(); i++)
        m_printerButtons[i]->setEnabled(false);

    //Title
    if(m_titleOpacityAnimation)
        delete m_titleOpacityAnimation;

    m_titleOpacityAnimation = new QPropertyAnimation(m_titleOpacityEffect, "opacity");
    m_titleOpacityAnimation->setDuration(500);

    connect(m_titleOpacityAnimation, SIGNAL(finished()), this, SLOT(on_titleOpacityAnimation_finished()));

    m_nextTitle = title;
    m_titleOpacityAnimation->setStartValue(1);
    m_titleOpacityAnimation->setEndValue(0);
    ui->pageTitle->setGraphicsEffect(m_titleOpacityEffect);

    m_titleOpacityAnimation->start();

    //Page
    qint32 width = this->width() - ui->menuFrame->width();
    qint32 height = this->height() - ui->menuBar->height();

    m_pageSize = QSize(width, height);
    m_pagePositionIn = QPoint(0, 0);
    m_pagePositionOut = QPoint(0, m_pageSize.height());

    if(page)
    {
        int ypos = m_pageSize.height() * -1;
        ypos -= ui->menuBar->height();

        m_nextPage = page;
        m_nextPage->setOpacityIn(1);
        m_nextPage->setOpacityOut(0);
        m_nextPage->setPositionIn(m_pagePositionIn);
        m_nextPage->setPositionOut(QPoint(0, ypos));
        m_nextPage->setDuration(500);

        connect(m_nextPage, SIGNAL(animatedIn()), this, SLOT(on_nextPage_animationIn_finished()));
        m_nextPage->setHidden(false);
        m_nextPage->animateIn();
    }

    if(m_currentPage)
    {
        connect(m_currentPage, SIGNAL(animatedOut()), this, SLOT(on_currentPage_animationOut_finished()));

        m_currentPage->setOpacityIn(1);
        m_currentPage->setOpacityOut(0);
        m_currentPage->setPositionIn(m_pagePositionIn);
        m_currentPage->setPositionOut(QPoint(0, m_pageSize.height()));
        m_currentPage->setDuration(500);

        ui->PageContainer->layout()->removeWidget(m_currentPage);

        m_currentPage->animateOut();
    }
    else
    {
    }
}

void MainWindow::init()
{
}

void MainWindow::online()
{
    setEnabled(true);

    if(!m_dashboardButton)
    {
        m_dashboardButton = new MenuButton(0, ui->menuFrame);
        m_dashboardButton->setText(QString("Dashboard"));
        m_dashboardButton->setIcon("dashboard");
        m_dashboardButton->setChecked(true);
        ui->menuButtonLayout->addWidget(m_dashboardButton);
        connect(m_dashboardButton, SIGNAL(clicked(MenuButton*)), this, SLOT(on_dashboardMenuButton_toggled(MenuButton*)));
    }

    m_titleOpacityEffect = new QGraphicsOpacityEffect(this);

    PrinterDefinitionList printers = Flo::settings()->printers();
    ui->menuButtonLayout->removeWidget(m_settingsButton);

    foreach(PrinterDefinition definition, printers)
    {
        PrinterPage *printerPage = new PrinterPage(Flo::printerPool()->getPrinterById(definition.id), this);

        QAnimatedWidget *animatedPage = new QAnimatedWidget(this);
        animatedPage->setWidget(printerPage);
        animatedPage->setHidden(true);
        ui->PageContainer->layout()->addWidget(animatedPage);

        MenuButton *printerButton = new MenuButton(m_printerPages.count(), this);
        printerButton->setIcon(QString("printer-icon"));
        printerButton->setText(definition.name);
        ui->menuButtonLayout->addWidget(printerButton);

        m_printerPages.append(animatedPage);
        m_printerButtons.append(printerButton);

        connect(printerButton, SIGNAL(clicked(MenuButton*)), this, SLOT(on_printerMenuButton_toggled(MenuButton*)));
    }

    if(!m_settingsButton)
    {
        m_settingsButton = new MenuButton(3, ui->menuFrame);
        m_settingsButton->setText(QString("Settings"));
        m_settingsButton->setIcon("setting");
        m_settingsButton->setChecked(false);
        ui->menuButtonLayout->addWidget(m_settingsButton);
        connect(m_settingsButton, SIGNAL(clicked(MenuButton*)), this, SLOT(on_settingsMenuButton_toggled(MenuButton*)));
        ui->menuButtonLayout->addWidget(m_settingsButton);
    }

    for(int i = 0; i < m_printerPages.count(); i++)
        m_printerPages[i]->setFixedSize(m_pageSize);

    setupPowerActions();

    setupUiClasses();
    updateStyleSheet();

    on_dashboardMenuButton_toggled(m_dashboardButton);
    //on_settingsMenuButton_toggled(m_settingsButton);
}

void MainWindow::setupUiClasses()
{
    ui->windowWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Window"));
    ui->PageContainer->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContainer"));
    //ui->emergencyStopButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "EmergencyStopButton"));
    //_settingsPage->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));

    ui->menuBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuBar"));
    ui->pageTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageTitle" ));

    //Menu Buttons
    ui->menuFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Menu"));
    ui->PageContainer->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContainer"));
    ui->menuTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuTitleBar"));
    ui->applicationIcon->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ApplicationIcon"));
    m_dashboardButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuButton" << "DashboardMenuButton"));
    m_settingsButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "MenuButton" << "DashboardMenuButton"));


    //Icons
    ui->powerButton->setIcon(Settings::getThemeIcon(QString("power-icon")));
}

void MainWindow::on_dashboardMenuButton_toggled(MenuButton* button)
{
    m_dashboardButton->setChecked(true);

    for(int i = 0; i < m_printerButtons.count(); i++)
        m_printerButtons[i]->setChecked(false);

    m_settingsButton->setChecked(false);

    if(!m_dashboardPage)
    {
        DashboardPage *dashboard = new DashboardPage();
        m_dashboardPage = new QAnimatedWidget(ui->PageContainer);
        m_dashboardPage->setWidget(dashboard);
        m_dashboardPage->setFixedSize(m_pageSize);
        m_dashboardPage->setHidden(true);
    }

    changePage(m_dashboardPage, QString("Dashboard"));
}

void MainWindow::on_settingsMenuButton_toggled(MenuButton* button)
{
    m_dashboardButton->setChecked(false);

    for(int i = 0; i < m_printerButtons.count(); i++)
        m_printerButtons[i]->setChecked(false);

    m_settingsButton->setChecked(true);

    if(!m_settingsPage)
    {
        SettingsPage *settings = new SettingsPage();
        m_settingsPage = new QAnimatedWidget(ui->PageContainer);
        m_settingsPage->setWidget(settings);
        m_settingsPage->setHidden(true);
        m_settingsPage->setFixedSize(m_pageSize);
        connect(m_settingsPage, SIGNAL(printerAdded(PrinterDefinition)), this, SLOT(on_settingsPage_printerAdded(PrinterDefinition)));
    }

    changePage(m_settingsPage, QString("Settings"));
}

void MainWindow::on_currentPage_animationOut_finished()
{
    disconnect(m_currentPage, SIGNAL(animatedOut()), this, SLOT(on_currentPage_animationOut_finished()));
}

void MainWindow::on_nextPage_animationIn_finished()
{
    disconnect(m_nextPage, SIGNAL(animatedIn()), this, SLOT(on_nextPage_animationIn_finished()));
    ui->PageContainer->layout()->addWidget(m_nextPage);

    m_currentPage = m_nextPage;
    m_nextPage = nullptr;

    //Enable Buttons
    if(m_dashboardButton)
        m_dashboardButton->setEnabled(true);

    if(m_settingsButton)
        m_settingsButton->setEnabled(true);

    for(int i = 0; i < m_printerButtons.count(); i++)
        m_printerButtons[i]->setEnabled(true);

    style()->polish(this);
}

void MainWindow::on_titleOpacityAnimation_finished()
{
    disconnect(m_titleOpacityAnimation, SIGNAL(finished()), this, SLOT(on_titleOpacityAnimation_finished()));

    m_currentTitle = this->m_nextTitle;
    ui->pageTitle->setText(m_currentTitle);
    ui->pageTitle->setGraphicsEffect(m_titleOpacityEffect);
    m_nextTitle = "";
    m_titleOpacityAnimation->setStartValue(0);
    m_titleOpacityAnimation->setEndValue(1);
    m_titleOpacityAnimation->start();
}

void MainWindow::on_printerMenuButton_toggled(MenuButton* button)
{
    m_dashboardButton->setChecked(false);
    m_settingsButton->setChecked(false);

    QString title;

    for(int i = 0; i < m_printerPages.count(); i++)
    {
        if(button->getId() == i)
        {
            title = button->getText();
            m_printerButtons[i]->setChecked(true);
        }
        else
            m_printerButtons[i]->setChecked(false);
    }

    changePage(m_printerPages[button->getId()], title);
}

void MainWindow::updateStyleSheet()
{
    QString style = Settings::currentTheme();

    m_dashboardButton->setIcon(QString("dashboard"));

    for(int i = 0; i < m_printerButtons.count(); i++)
        m_printerButtons[i]->setIcon(QString("printer"));

    m_settingsButton->setIcon(QString("settings"));

    //Dashboard icons should all be the same size
    QPixmap pixmap;

    pixmap = Settings::getThemeIcon("power-icon").pixmap(20,20);
    ui->powerButton->setIcon(pixmap);

    pixmap = Settings::getThemeIcon("refresh-icon").pixmap(16,16);
    this->m_restartAction->setIcon(pixmap);

    pixmap = Settings::getThemeIcon("power-icon").pixmap(16,16);
    this->m_shutdownAction->setIcon(pixmap);

    pixmap = Settings::getThemeIcon("cancel-icon").pixmap(16,16);
    this->m_closeAction->setIcon(pixmap);

    ui->applicationIcon->setPixmap(QPixmap(":/images/application-icon"));
    ui->applicationIcon->setScaledContents(true);

    this->setStyleSheet(style);

    for(int i = 0; i < m_printerPages.count(); i++)
        m_printerPages[i]->setStyleSheet(style);

    if(m_dashboardPage != nullptr)
        m_dashboardPage->setStyleSheet(style);

    if(m_settingsPage != nullptr)
        m_settingsPage->setStyleSheet(style);
}

void MainWindow::showPopup()
{
    //this->popup->setGeometry(QRect(0,0,this->height(),this->width()));
}

void MainWindow::setMenuEnabled(bool enabled)
{
    m_dashboardButton->setEnabled(enabled);

    for(int i = 0; i < m_printerButtons.count(); i++)
        m_printerButtons[i]->setEnabled(true);

    m_settingsButton->setEnabled(enabled);
}

void MainWindow::setupPowerActions()
{
    //Restart Action
    this->m_restartAction = new QAction(this);
    this->m_restartAction->setText(QString("Restart System"));
    connect(m_restartAction, SIGNAL(triggered(bool)), this, SLOT(on_restartAction_triggered(bool)));
    ui->powerButton->addAction(m_restartAction);

    //Shutdown Action
    this->m_shutdownAction = new QAction(this);
    this->m_shutdownAction->setText(QString("Shutdown System"));
    connect(m_shutdownAction, SIGNAL(triggered(bool)), this, SLOT(on_shutdownAction_triggered(bool)));
    ui->powerButton->addAction(m_shutdownAction);

    QAction *separator = new QAction(this);
    separator->setSeparator(true);
    ui->powerButton->addAction(separator);

    //Close Action
    this->m_closeAction = new QAction(this);
    this->m_closeAction->setText(QString("Close Application"));
    connect(m_closeAction, SIGNAL(triggered(bool)), this, SLOT(on_closeAction_triggered(bool)));
    ui->powerButton->addAction(m_closeAction);
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

    m_pageSize = QSize(width, height);
    m_pagePositionIn = QPoint(ui->menuFrame->width(), ui->menuBar->height());
    m_pagePositionOut = QPoint(this->width(), ui->menuBar->height());

    if(m_dashboardPage)
        m_dashboardPage->setFixedSize(m_pageSize);

    if(m_settingsPage)
        m_settingsPage->setFixedSize(m_pageSize);

    for(int i = 0; i < m_printerPages.count(); i++)
        m_printerPages[i]->setFixedSize(m_pageSize);
}


void MainWindow::on_emergencyStopButton_clicked()
{
    //this->m_printer->console()->emergencyStop();
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
    m_loadingGif->stop();
    delete m_loadingGif;
    delete m_loadingLabel;
    delete m_loadingAnimation;
    m_loadingLabel = nullptr;
    m_loadingGif = nullptr;
    m_loadingAnimation = nullptr;
}

