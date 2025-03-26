#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flo/qklipperinstancepool.h"

//Pages
#include "flo/settings.h"
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

    if(Settings::get("ui/kiosk-mode", true).toBool())
        this->setWindowFlag(Qt::FramelessWindowHint);
    else
        ui->menuBar->setFixedHeight(0);

    this->setWindowIcon(QIcon(":/images/flo_beta.png"));

    QThread::currentThread()->setPriority(QThread::LowestPriority);

    m_titleOpacityEffect = new QGraphicsOpacityEffect(this);
    ui->pageTitle->setGraphicsEffect(m_titleOpacityEffect);
    m_titleOpacityAnimation = new QPropertyAnimation(m_titleOpacityEffect, "opacity");
    m_titleOpacityAnimation->setDuration(250);

    Settings::load();

    // QScreen *screen = QGuiApplication::primaryScreen();
    // QRect  screenGeometry = screen->geometry();

    showMaximized();
    //setFixedSize(screenGeometry.size());
    setFixedSize(QSize(1920,1080));

    m_initTimer = new QTimer(this);
    m_initTimer->setInterval(50);
    m_initTimer->setSingleShot(true);


    //initializing asynchronously avoids an ugly resizing on launch
    connect(m_initTimer, SIGNAL(timeout()), this, SLOT(on_initAsync()));
    m_initTimer->start();

    connect(Settings::instance(), SIGNAL(currentThemeChanged()), this, SLOT(onThemeUpdated()));

    m_viewer = new QQuickView();
    m_viewerWidget = QWidget::createWindowContainer(m_viewer, this);
    m_viewerWidget->setFixedSize(0,0);
    ui->PageContainer->layout()->addWidget(m_viewerWidget);
    m_viewer->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changePage(QWidget *page, QString title)
{
    setWindowTitle(QString("FLO - ") + title);

    if(Settings::isAnimationEnabled())
    {
        if(Settings::isAnimationEffectsEnabled())
        {
            if(m_titleOpacityAnimation)
                m_titleOpacityAnimation->deleteLater();

            if(Settings::animationEffectOutStyle() == Settings::Opacity)
                m_titleOpacityAnimation = new QPropertyAnimation(m_titleOpacityEffect, "opacity");
            else if(Settings::animationEffectOutStyle() == Settings::Blur)
                m_titleOpacityAnimation = new QPropertyAnimation(m_titleOpacityEffect, "blur");

            m_titleOpacityAnimation->setDuration(Settings::animationDuration() / 2);

            connect(m_titleOpacityAnimation, SIGNAL(finished()), this, SLOT(on_titleOpacityAnimation_finished()));

            m_nextTitle = title;
            m_titleOpacityAnimation->setStartValue(1);
            m_titleOpacityAnimation->setEndValue(0);
            ui->pageTitle->setGraphicsEffect(m_titleOpacityEffect);

            m_titleOpacityAnimation->start();
        }

        connect(m_pageStackWidget, SIGNAL(animationFinished()), this, SLOT(on_nextPage_animationIn_finished()));
        m_pageStackWidget->slideInWgt(page);
    }
    else
    {
        m_pageStackWidget->setCurrentWidget(page);
        ui->pageTitle->setText(title);
        on_nextPage_animationIn_finished();
    }
}

void MainWindow::online()
{
    setEnabled(true);

    m_pageStackWidget = new SlidingStackedWidget(ui->PageContainer);
    ui->PageContainer->layout()->addWidget(m_pageStackWidget);

    if(!m_dashboardButton)
    {
        m_dashboardButton = new MenuButton(0, ui->menuFrame);
        m_dashboardButton->setText(QString("Dashboard"));
        m_dashboardButton->setIcon(Settings::getThemeIcon("dashboard"));
        m_dashboardButton->setChecked(true);
        ui->menuButtonLayout->addWidget(m_dashboardButton);
        connect(m_dashboardButton, SIGNAL(clicked(MenuButton*)), this, SLOT(on_dashboardMenuButton_toggled(MenuButton*)));
    }

    m_settingsPage = new SettingsPage(m_pageStackWidget);
    m_dashboardPage = new DashboardPage(m_pageStackWidget);
    m_pageStackWidget->addWidget(m_dashboardPage);

    m_titleOpacityEffect = new QGraphicsOpacityEffect(this);

    QKlipperInstanceList printers = QKlipperInstancePool::klipperInstances();

    for(QKlipperInstance *definition : printers)
    {
        PrinterPage *printerPage = new PrinterPage(definition, m_pageStackWidget);

        MenuButton *printerButton = new MenuButton(m_printerPages.count(), this);
        printerButton->setIcon(Settings::getThemeIcon("printer", QColor::fromString(definition->profileColor())));
        printerButton->setText(definition->name());
        ui->menuButtonLayout->addWidget(printerButton);

        m_pageStackWidget->addWidget(printerPage);

        m_printerPages.append(printerPage);
        m_printerButtons.append(printerButton);
        m_instances.append(definition);

        connect(printerButton, SIGNAL(clicked(MenuButton*)), this, SLOT(on_printerMenuButton_toggled(MenuButton*)));
    }

    m_pageStackWidget->addWidget(m_settingsPage);

    if(!m_settingsButton)
    {
        m_settingsButton = new MenuButton(3, ui->menuFrame);
        m_settingsButton->setText(QString("Settings"));
        m_settingsButton->setIcon(Settings::getThemeIcon("settings"));
        m_settingsButton->setChecked(false);
        ui->menuButtonLayout->addWidget(m_settingsButton);
        connect(m_settingsButton, SIGNAL(clicked(MenuButton*)), this, SLOT(on_settingsMenuButton_toggled(MenuButton*)));
        ui->menuButtonLayout->addWidget(m_settingsButton);
    }

    setupUiClasses();
    updateStyleSheet();

    on_dashboardMenuButton_toggled(m_dashboardButton);
    //on_settingsMenuButton_toggled(m_settingsButton);

    connect(QKlipperInstancePool::pool(), SIGNAL(instanceAdded(QKlipperInstance*)), this, SLOT(on_printerPoolPrinterAdded(QKlipperInstance*)));
    connect(QKlipperInstancePool::pool(), SIGNAL(instanceRemoved(QKlipperInstance*)), this, SLOT(on_printerPoolPrinterRemoved(QKlipperInstance*)));
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
    ui->powerButton->setIcon(Settings::getThemeIcon(QString("power")));
    ui->applicationIcon->setPixmap(QPixmap(":/images/flo_beta.png"));
    ui->applicationIcon->setScaledContents(true);
    ui->applicationIcon->setFixedSize(24,24);
}

void MainWindow::on_dashboardMenuButton_toggled(MenuButton* button)
{
    Q_UNUSED(button)

    m_dashboardButton->setChecked(true);

    for(int i = 0; i < m_printerButtons.count(); i++)
        m_printerButtons[i]->setChecked(false);

    m_settingsButton->setChecked(false);

    m_currentInstance = nullptr;

    changePage(m_dashboardPage, QString("Dashboard"));
}

void MainWindow::on_settingsMenuButton_toggled(MenuButton* button)
{
    Q_UNUSED(button)

    m_dashboardButton->setChecked(false);

    for(int i = 0; i < m_printerButtons.count(); i++)
        m_printerButtons[i]->setChecked(false);

    m_settingsButton->setChecked(true);

    m_currentInstance = nullptr;

    changePage(m_settingsPage, QString("Settings"));
}

void MainWindow::on_currentPage_animationOut_finished()
{
}

void MainWindow::on_nextPage_animationIn_finished()
{
    disconnect(m_pageStackWidget, SIGNAL(animationFinished()), this, SLOT(on_nextPage_animationIn_finished()));

    //Enable Buttons
    if(m_dashboardButton)
        m_dashboardButton->setEnabled(true);

    if(m_settingsButton)
        m_settingsButton->setEnabled(true);

    for(int i = 0; i < m_printerButtons.count(); i++)
        m_printerButtons[i]->setEnabled(true);

    //style()->polish(this);
}

void MainWindow::on_titleOpacityAnimation_finished()
{
    if(Settings::isAnimationEnabled() && Settings::isAnimationEffectsEnabled())
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
    else
        ui->pageTitle->setText(m_currentTitle);
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

    PrinterPage *printerPage = qobject_cast<PrinterPage*>(m_printerPages[button->getId()]);

    if(printerPage)
    {
        qDebug() << "Setting active printer to " << title;

        QKlipperInstance *parentInstance = qobject_cast<QKlipperInstance*>(printerPage->printer()->parent());

        if(parentInstance)
            m_currentInstance = parentInstance;
    }

    changePage(m_printerPages[button->getId()], title);
}

void MainWindow::updateStyleSheet()
{
    QString style = Settings::currentTheme();

    m_dashboardButton->setIcon(Settings::getThemeIcon("dashboard"));

    for(int i = 0; i < m_printerButtons.count(); i++)
    {
        if(i < m_instances.count())
        {
            qDebug() << "Updating MenuButton";
            m_printerButtons[i]->setIcon(Settings::getThemeIcon("printer", QColor::fromString(m_instances[i]->profileColor())));
        }

        m_printerButtons[i]->setStyleSheet(Settings::currentTheme());
    }

    m_settingsButton->setIcon(Settings::getThemeIcon("settings"));

    //Dashboard icons should all be the same size
    QPixmap pixmap;
    // this->m_restartAction->setIcon(Settings::getThemeIcon("refresh"));
    // this->m_shutdownAction->setIcon(Settings::getThemeIcon("power"));
    // this->m_closeAction->setIcon(Settings::getThemeIcon("cancel"));

    //Icons
    ui->powerButton->setIcon(Settings::getThemeIcon(QString("power")));
    ui->applicationIcon->setPixmap(QPixmap(":/images/flo_beta.png"));
    ui->applicationIcon->setScaledContents(true);

    this->setStyleSheet(style);

    if(m_dashboardPage)
    {
        DashboardPage *dashboard = qobject_cast<DashboardPage*>(m_dashboardPage);

        if(dashboard)
            dashboard->setStyleSheet(Settings::currentTheme());
    }

    if(m_settingsPage)
    {
        SettingsPage *dashboard = qobject_cast<SettingsPage*>(m_settingsPage);

        if(dashboard)
            dashboard->setStyleSheet(Settings::currentTheme());
    }

    ui->windowWidget->setStyleSheet(Settings::currentTheme());
    ui->menuBar->setStyleSheet(Settings::currentTheme());
    ui->windowWidget->setStyleSheet(Settings::currentTheme());

    for(PrinterPage *page : m_printerPages)
    {
        if(page)
            page->setStyleSheet(Settings::currentTheme());
    }

    for(MenuButton *button : m_printerButtons)
        button->setStyleSheet(Settings::currentTheme());
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

void MainWindow::on_initAsync()
{
    connect(Flo::instance(), SIGNAL(loadingFinished()), this, SLOT(online()));
    Flo::instance()->start();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Settings::save();
    event->accept();
}

void MainWindow::on_emergencyStopButton_clicked()
{
    m_currentInstance->console()->printerEmergencyStop();
}

void MainWindow::on_restartAction_triggered(bool checked)
{
    Q_UNUSED(checked)

    if(m_currentInstance)
        m_currentInstance->system()->restart();
}

void MainWindow::on_shutdownAction_triggered(bool checked)
{
    Q_UNUSED(checked)

    if(m_currentInstance)
        m_currentInstance->system()->shutdown();
}

void MainWindow::on_closeAction_triggered(bool checked)
{
    Q_UNUSED(checked)

    this->close();
}

void MainWindow::on_powerButton_clicked()
{
    on_closeAction_triggered(true);
}

void MainWindow::on_printerPoolPrinterAdded(QKlipperInstance *printer)
{
    ui->menuButtonLayout->removeWidget(m_settingsButton);

    PrinterPage *printerPage = new PrinterPage(printer, m_pageStackWidget);

    MenuButton *printerButton = new MenuButton(m_printerPages.count(), this);
    printerButton->setIcon(Settings::getThemeIcon("printer", QColor::fromString(printer->profileColor())));
    printerButton->setText(printer->name());
    ui->menuButtonLayout->addWidget(printerButton);

    m_printerPages.append(printerPage);
    m_printerButtons.append(printerButton);
    m_instances.append(printer);

    connect(printerButton, SIGNAL(clicked(MenuButton*)), this, SLOT(on_printerMenuButton_toggled(MenuButton*)));

    ui->menuButtonLayout->addWidget(m_settingsButton);
}

void MainWindow::on_printerPoolPrinterRemoved(QKlipperInstance* printer)
{
    for(PrinterPage *page : m_printerPages)
    {
        if(page && page->printer()->id() == printer->id())
        {
            for(MenuButton *button : m_printerButtons)
            {
                if(button->getId() == m_printerPages.indexOf(page))
                {
                    ui->menuButtonLayout->removeWidget(button);
                    m_printerButtons.removeAll(button);
                    button->deleteLater();
                    break;
                }
            }

            m_printerPages.removeAll(page);
            page->deleteLater();
            break;
        }
    }
}

void MainWindow::onThemeUpdated()
{
    updateStyleSheet();
}

