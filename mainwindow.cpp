#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "system/qklipperinstancepool.h"

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
    this->setWindowIcon(QIcon(":/images/flo_beta.png"));

    m_titleOpacityEffect = new QGraphicsOpacityEffect(this);
    ui->pageTitle->setGraphicsEffect(m_titleOpacityEffect);
    m_titleOpacityAnimation = new QPropertyAnimation(m_titleOpacityEffect, "opacity");
    m_titleOpacityAnimation->setDuration(250);

    Settings::load();

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();

    setFixedSize(screenGeometry.size());
    ui->windowWidget->setFixedSize(screenGeometry.size());
    ui->windowWidget->setEnabled(true);

    m_initTimer = new QTimer(this);
    m_initTimer->setInterval(50);
    m_initTimer->setSingleShot(true);

    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->setEnabled(true);

    if(Settings::get("ui-opengl").toBool())
    {
        m_graphicsScene = new QGraphicsScene(this);
        ui->windowWidget->setParent(0);

        QGraphicsProxyWidget *proxy = m_graphicsScene->addWidget(ui->windowWidget);
        proxy->setPos(0,0);
        proxy->setZValue(1);
        ui->graphicsView->setScene(m_graphicsScene);

        QOpenGLWidget *gl = new QOpenGLWidget();
        QSurfaceFormat format;

        format.setSwapBehavior(QSurfaceFormat::TripleBuffer);

#ifdef RASPBERRYPI
        format.setSamples(1);
#else
        format.setSamples(4);
#endif

        gl->setFormat(format);
        ui->graphicsView->setViewport(gl);
        ui->windowWidget->setEnabled(true);
    }
    else
    {
        ui->centralwidget->layout()->removeWidget(ui->graphicsView);
        ui->graphicsView->setFixedSize(0,0);
        ui->graphicsView->lower();
        ui->graphicsView->hide();
        ui->centralwidget->layout()->addWidget(ui->windowWidget);
    }


    ui->windowWidget->setStyleSheet(Settings::currentTheme());
    ui->menuBar->setStyleSheet(Settings::currentTheme());
    ui->windowWidget->setStyleSheet(Settings::currentTheme());
    ui->graphicsView->setStyleSheet(Settings::currentTheme());

    connect(m_initTimer, SIGNAL(timeout()), this, SLOT(on_initAsync()));
    m_initTimer->start();

    connect(Settings::instance(), SIGNAL(currentThemeChanged()), this, SLOT(onThemeUpdated()));
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

        //Page
        m_pageSize = ui->PageContainer->size();
        m_pagePositionIn = QPoint(0, 0);
        m_pagePositionOut = QPoint(0, m_pageSize.height());

        if(page)
        {
            int ypos = m_pageSize.height() * -1;
            ypos -= ui->menuBar->height();

            m_nextPage = page;

            if(Settings::isAnimationEffectsEnabled())
            {
                m_nextPage->setOpacityIn(1);
                m_nextPage->setOpacityOut(0);
            }

            m_nextPage->setDuration(Settings::animationDuration());
            m_nextPage->setGeometryIn(QRect(0,0,m_pageSize.width(),m_pageSize.height()));

            connect(m_nextPage, SIGNAL(animatedIn()), this, SLOT(on_nextPage_animationIn_finished()));
            m_nextPage->show();
            m_nextPage->lower();
            m_nextPage->animateIn();
        }

        if(m_currentPage)
        {
            connect(m_currentPage, SIGNAL(animatedOut()), this, SLOT(on_currentPage_animationOut_finished()));

            if(Settings::isAnimationEffectsEnabled())
            {
                m_currentPage->setOpacityIn(1);
                m_currentPage->setOpacityOut(0);
            }

            m_currentPage->setGeometry(0,0,m_pageSize.width(),m_pageSize.height());
            m_currentPage->setDuration(Settings::animationDuration());

            m_currentPage->animateOut();
        }
        else
        {
        }
    }
    else
    {
        m_nextTitle = title;
        m_nextPage = page;
        on_titleOpacityAnimation_finished();
        on_currentPage_animationOut_finished();
        on_nextPage_animationIn_finished();
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

    QKlipperInstanceList printers = QKlipperInstancePool::klipperInstances();
    //ui->menuButtonLayout->removeWidget(m_settingsButton);

    foreach(QKlipperInstance *definition, printers)
    {
        PrinterPage *printerPage = new PrinterPage(definition, this);

        QAnimatedWidget *animatedPage = new QAnimatedWidget(this);
        animatedPage->setWidget(printerPage);
        animatedPage->setHidden(true);

        MenuButton *printerButton = new MenuButton(m_printerPages.count(), this);
        printerButton->setIcon(QString("printer-icon"));
        printerButton->setText(definition->name());
        ui->menuButtonLayout->addWidget(printerButton);

        m_printerPages.append(animatedPage);
        m_printerButtons.append(printerButton);

        connect(printerButton, SIGNAL(clicked(MenuButton*)), this, SLOT(on_printerMenuButton_toggled(MenuButton*)));
    }

    if(!m_settingsButton)
    {
        m_settingsButton = new MenuButton(3, ui->menuFrame);
        m_settingsButton->setText(QString("Settings"));
        m_settingsButton->setIcon("settings-icon");
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
    ui->powerButton->setIcon(Settings::getThemeIcon(QString("power-icon")));
    ui->applicationIcon->setPixmap(QPixmap(":/images/flo_beta.png"));
    ui->applicationIcon->setScaledContents(true);
    ui->applicationIcon->setFixedSize(24,24);
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
        m_dashboardPage->setGeometry(0,0,m_pageSize.width(),m_pageSize.height());
        m_dashboardPage->show();
        m_dashboardPage->setFixedSize(m_pageSize);
        m_dashboardPage->setWidget(dashboard);
        m_dashboardPage->setFixedSize(m_pageSize);
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
        m_settingsPage->setGeometry(0,0,m_pageSize.width(),m_pageSize.height());
        m_settingsPage->show();
        m_settingsPage->setFixedSize(m_pageSize);
        m_settingsPage->setWidget(settings);
    }

    changePage(m_settingsPage, QString("Settings"));
}

void MainWindow::on_currentPage_animationOut_finished()
{
    if(Settings::isAnimationEnabled())
        disconnect(m_currentPage, SIGNAL(animatedOut()), this, SLOT(on_currentPage_animationOut_finished()));

    ui->PageContainer->layout()->removeWidget(m_currentPage);
}

void MainWindow::on_nextPage_animationIn_finished()
{
    if(Settings::isAnimationEnabled())
        disconnect(m_nextPage, SIGNAL(animatedIn()), this, SLOT(on_nextPage_animationIn_finished()));

    ui->PageContainer->layout()->addWidget(m_nextPage);
    m_nextPage->show();
    m_nextPage->raise();

    if(m_currentPage)
    {
        m_currentPage->lower();
        m_currentPage->hide();
    }

    m_currentPage = m_nextPage;
    m_nextPage = nullptr;

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

    changePage(m_printerPages[button->getId()], title);
}

void MainWindow::updateStyleSheet()
{
    QString style = Settings::currentTheme();

    m_dashboardButton->setIcon(QString("dashboard"));

    for(int i = 0; i < m_printerButtons.count(); i++)
        m_printerButtons[i]->setIcon(QString("printer"));

    m_settingsButton->setIcon(QString("settings-icon"));

    //Dashboard icons should all be the same size
    QPixmap pixmap;

    //pixmap = Settings::getThemeIcon("power-icon").pixmap(20,20);

    //pixmap = Settings::getThemeIcon("refresh-icon").pixmap(16,16);
    this->m_restartAction->setIcon(Settings::getThemeIcon("refresh-icon"));

    //pixmap = Settings::getThemeIcon("power-icon").pixmap(16,16);
    this->m_shutdownAction->setIcon(Settings::getThemeIcon("power-icon"));

    //pixmap = Settings::getThemeIcon("cancel-icon").pixmap(16,16);
    this->m_closeAction->setIcon(Settings::getThemeIcon("cancel-icon"));

    //Icons
    ui->powerButton->setIcon(Settings::getThemeIcon(QString("power-icon")));
    ui->applicationIcon->setPixmap(QPixmap(":/images/flo_beta.png"));
    ui->applicationIcon->setScaledContents(true);

    this->setStyleSheet(style);

    if(m_dashboardPage)
    {
        DashboardPage *dashboard = qobject_cast<DashboardPage*>(m_dashboardPage->widget());

        if(dashboard)
            dashboard->setStyleSheet(Settings::currentTheme());
    }

    if(m_settingsPage)
    {
        SettingsPage *dashboard = qobject_cast<SettingsPage*>(m_settingsPage->widget());

        if(dashboard)
            dashboard->setStyleSheet(Settings::currentTheme());
    }

    ui->windowWidget->setStyleSheet(Settings::currentTheme());
    ui->menuBar->setStyleSheet(Settings::currentTheme());
    ui->windowWidget->setStyleSheet(Settings::currentTheme());
    ui->graphicsView->setStyleSheet(Settings::currentTheme());

    for(QAnimatedWidget *page : m_printerPages)
    {
        PrinterPage *printerPage = qobject_cast<PrinterPage*>(page->widget());

        if(printerPage)
            printerPage->setStyleSheet(Settings::currentTheme());
    }
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
    Flo::instance()->start();
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

void MainWindow::on_printerPoolPrinterAdded(QKlipperInstance *printer)
{
    ui->menuButtonLayout->removeWidget(m_settingsButton);

    PrinterPage *printerPage = new PrinterPage(printer, this);

    QAnimatedWidget *animatedPage = new QAnimatedWidget(this);
    animatedPage->setWidget(printerPage);
    animatedPage->setHidden(true);

    MenuButton *printerButton = new MenuButton(m_printerPages.count(), this);
    printerButton->setIcon(QString("printer-icon"));
    printerButton->setText(printer->name());
    ui->menuButtonLayout->addWidget(printerButton);

    m_printerPages.append(animatedPage);
    m_printerButtons.append(printerButton);

    connect(printerButton, SIGNAL(clicked(MenuButton*)), this, SLOT(on_printerMenuButton_toggled(MenuButton*)));

    ui->menuButtonLayout->addWidget(m_settingsButton);
}

void MainWindow::on_printerPoolPrinterRemoved(QKlipperInstance* printer)
{
    foreach(QAnimatedWidget *widget, m_printerPages)
    {
        PrinterPage *page = qobject_cast<PrinterPage*>(widget->widget());

        if(page && page->printer()->id() == printer->id())
        {
            foreach(MenuButton *button, m_printerButtons)
            {
                if(button->getId() == m_printerPages.indexOf(widget))
                {
                    ui->menuButtonLayout->removeWidget(button);
                    m_printerButtons.removeAll(button);
                    button->deleteLater();
                    break;
                }
            }

            m_printerPages.removeAll(widget);
            widget->deleteLater();
            break;
        }
    }
}

void MainWindow::onThemeUpdated()
{
    //setStyleSheet(Settings::currentTheme());
    updateStyleSheet();
}

void MainWindow::on_loadingAnimation_finished()
{
    m_loadingGif->stop();
    m_loadingGif->deleteLater();
    m_loadingLabel->deleteLater();
    m_loadingAnimation->deleteLater();
    m_loadingLabel = nullptr;
    m_loadingGif = nullptr;
    m_loadingAnimation = nullptr;
}

