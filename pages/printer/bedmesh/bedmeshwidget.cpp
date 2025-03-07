#include "bedmeshwidget.h"
#include "qabstractaxis.h"
#include "flo/settings.h"

BedMeshWidget::BedMeshWidget(QKlipperPrintBed *bed, QWidget *parent) : Page(parent)
{
    m_printBed = bed;
    m_data = new BedMeshData(m_printBed, this);

    setupUi();
    setupViewer();
    setupSidebar();
    setupButtonBox();

    onToolheadHomedChanged();

    QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_printBed->parent());

    if(printer)
        connect(printer->toolhead(), SIGNAL(isHomedChanged()), this, SLOT(onToolheadHomedChanged()));
}

BedMeshWidget::~BedMeshWidget()
{
    if(m_viewer)
        delete m_viewer;

    if(m_viewerWidget)
    {
        m_layout->removeWidget(m_viewerWidget);
        delete m_viewerWidget;
    }

    if(m_adjustmentScrewFrame)
    {
        m_layout->removeWidget(m_adjustmentScrewFrame);
        delete m_adjustmentScrewFrame;
    }

    if(m_bedMeshFrame)
    {
        m_layout->removeWidget(m_bedMeshFrame);
        delete m_bedMeshFrame;
    }

    if(m_healthCard)
    {
        m_layout->removeWidget(m_healthCard);
        delete m_healthCard;
    }

    if(m_data)
        delete m_data;

    delete m_layout;
}

void BedMeshWidget::setStyleSheet(QString styleSheet)
{
    if(m_viewer)
    {
        QQmlContext* context = m_viewer->rootContext();
        context->setContextProperty("_theme_graphBackgroundColor", QColor::fromString(Settings::get("theme/graph-background-start").toString()));
        context->setContextProperty("_theme_graphPlotAreaBackgroundColor", QColor::fromString(Settings::get("theme/graph-plot-background-start").toString()));
        context->setContextProperty("_theme_meshVeryHighColor", QColor::fromString(Settings::get("theme/bedmesh-very-high-color").toString()));
        context->setContextProperty("_theme_meshHighColor", QColor::fromString(Settings::get("theme/bedmesh-high-color").toString()));
        context->setContextProperty("_theme_meshLowColor", QColor::fromString(Settings::get("theme/bedmesh-low-color").toString()));
        context->setContextProperty("_theme_meshVeryLowColor", QColor::fromString(Settings::get("theme/bedmesh-very-low-color").toString()));
        context->setContextProperty("_theme_meshColor", QColor::fromString(Settings::get("theme/bedmesh-color").toString()));
    }

    if(m_bedMeshFrame)
        m_bedMeshFrame->setStyleSheet(styleSheet);

    if(m_adjustmentScrewFrame)
        m_adjustmentScrewFrame->setStyleSheet(styleSheet);

    if(m_healthCard)
        m_healthCard->setStyleSheet(styleSheet);

    m_homeButton->setIcon(Settings::getThemeIcon(QString("home")));
    Page::setStyleSheet(styleSheet);
}

void BedMeshWidget::setupUi()
{
    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);

    m_centralWidget = new QWidget(this);
    m_centralLayout = new QGridLayout(m_centralWidget);
    m_centralWidget->setLayout(m_centralLayout);
    //m_centralWidget->setProperty("class", "Page");
    m_layout->addWidget(m_centralWidget, 1, 0);

    this->setLayout(m_layout);
}

void BedMeshWidget::setupViewer()
{
    m_viewer = new QQuickView();

// The following are needed to make examples run without having to install the
// module in desktop environments.
#ifdef Q_OS_WIN
    QString extraImportPath(QStringLiteral("%1/../../../../%2"));
#else
    QString extraImportPath(QStringLiteral("%1/../../../%2"));
#endif
    m_viewer->engine()->addImportPath(
        extraImportPath.arg(QGuiApplication::applicationDirPath(), QString::fromLatin1("qml")));

    QQmlContext* context = m_viewer->rootContext(); //view is the QDeclarativeView
    context->setContextProperty("BedMeshData", m_data);
    context->setContextProperty("_theme_graphBackgroundColor", QColor::fromString(Settings::get("theme/graph-background-start").toString()));
    context->setContextProperty("_theme_graphPlotAreaBackgroundColor", QColor::fromString(Settings::get("theme/graph-plot-background-start").toString()));
    context->setContextProperty("_theme_meshVeryHighColor", QColor::fromString(Settings::get("theme/bedmesh-very-high-color").toString()));
    context->setContextProperty("_theme_meshHighColor", QColor::fromString(Settings::get("theme/bedmesh-high-color").toString()));
    context->setContextProperty("_theme_meshLowColor", QColor::fromString(Settings::get("theme/bedmesh-low-color").toString()));
    context->setContextProperty("_theme_meshVeryLowColor", QColor::fromString(Settings::get("theme/bedmesh-very-low-color").toString()));
    context->setContextProperty("_theme_meshColor", QColor::fromString(Settings::get("theme/bedmesh-color").toString()));

    m_viewer->setTitle(QStringLiteral("Flo Bed Mesh Viewer"));

    m_viewer->setSource(QUrl("qrc:/pages/printer/bedmesh/BedMeshViewer.qml"));
    m_viewer->setResizeMode(QQuickView::SizeRootObjectToView);
    m_viewer->setColor(QColor("#262626"));

    m_viewerWidget = QWidget::createWindowContainer(m_viewer, this);
    m_bedMeshCard = new CardWidget(CardWidget::CardType::Widget, this);
    m_bedMeshCard->setTitle("Bed Mesh");
    m_bedMeshCard->setIcon(Settings::getThemeIcon("bed-mesh"));
    m_bedMeshCard->setCentralWidget(m_viewerWidget);

    m_centralLayout->addWidget(m_bedMeshCard, 0, 0);

    m_viewer->show();
}

void BedMeshWidget::setupSidebar()
{
    m_sideBarWidget = new QWidget(m_centralWidget);
    m_sideBarWidget->setFixedWidth(420);
    m_centralLayout->addWidget(m_sideBarWidget, 0, 1, 1, 1);

    m_sidebarLayout = new QGridLayout(m_sideBarWidget);
    m_sidebarLayout->setContentsMargins(6, 0, 4, 0);

    m_healthCard = new BedMeshHealthCard(m_data, m_centralWidget);
    m_sidebarLayout->addWidget(m_healthCard, 0, 0, 1, 1);

    m_bedMeshFrame = new ProbedMeshFrame(m_printBed, m_sideBarWidget);
    m_sidebarLayout->addWidget(m_bedMeshFrame, 1, 0, 1, 1);

    m_adjustmentScrewFrame = new AdjustmentScrewFrame(m_printBed, m_centralWidget);
    m_sidebarLayout->addWidget(m_adjustmentScrewFrame, 2, 0, 1, 1);

    m_sidebarLayout->addItem(new QSpacerItem(0, 40, QSizePolicy::Expanding, QSizePolicy::Expanding), 3, 0, 1, 1);
    m_sideBarWidget->setLayout(m_sidebarLayout);
}

void BedMeshWidget::setupButtonBox()
{
    m_buttonBoxWidget = new QWidget(m_centralWidget);
    m_buttonBoxWidget->setProperty("class", QStringList { "PageActionBar" } + m_buttonBoxWidget->property("class").toStringList());
    m_buttonBoxLayout = new QHBoxLayout(m_buttonBoxWidget);
    m_buttonBoxLayout->setContentsMargins(4,4,4,4);
    m_buttonBoxWidget->setLayout(m_buttonBoxLayout);

    m_homeButton = new QIconButton(m_buttonBoxWidget);
    m_homeButton->setIcon(Settings::getThemeIcon(QString("home")));
    m_homeButton->setText("Home Toolhead");
    m_homeButton->setFixedHeight(50);
    m_homeButton->setTextMargins(QMargins(34,0,0,0));
    m_homeButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    m_buttonBoxLayout->addWidget(m_homeButton);

    connect(m_homeButton, SIGNAL(clicked()), this, SLOT(onHomeButtonClicked()));

    m_calibrateMeshButton = new QIconButton(m_buttonBoxWidget);
    m_calibrateMeshButton->setIcon(Settings::getThemeIcon(QString("mesh-calibrate")));
    m_calibrateMeshButton->setText("Calibrate Bed Mesh");
    m_calibrateMeshButton->setFixedHeight(50);
    m_calibrateMeshButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_buttonBoxLayout->addWidget(m_calibrateMeshButton);

    connect(m_calibrateMeshButton, SIGNAL(clicked()), this, SLOT(onCalibrateMeshButtonClicked()));

    m_calibrateScrewsButton = new QIconButton(m_buttonBoxWidget);
    m_calibrateScrewsButton->setIcon(Settings::getThemeIcon(QString("adjustment-screws-calibrate")));
    m_calibrateScrewsButton->setText("Calibrate Adjustment Screws");
    m_calibrateScrewsButton->setFixedHeight(50);
    m_calibrateScrewsButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_buttonBoxLayout->addWidget(m_calibrateScrewsButton);

    m_closeButton = new QIconButton(m_buttonBoxWidget);
    m_closeButton->setIcon(Settings::getThemeIcon(QString("multiply")));
    m_closeButton->setFixedSize(50,50);
    m_closeButton->setTextMargins(QMargins(34,0,0,0));
    m_closeButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    m_buttonBoxLayout->addWidget(m_closeButton);

    connect(m_calibrateScrewsButton, SIGNAL(clicked()), this, SLOT(onCalibrateScrewsButtonClicked()));

    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(close()));

    m_layout->addWidget(m_buttonBoxWidget, 0, 0, 1, 1);
}

void BedMeshWidget::onHomeButtonClicked()
{
    QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_printBed->parent());

    if(printer && printer->status() == QKlipperPrinter::Ready)
    {
        QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_printBed->parent());

        if(printer)
            printer->toolhead()->home();
    }
}

void BedMeshWidget::onCalibrateMeshButtonClicked()
{
    QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_printBed->parent());

    if(printer && printer->status() == QKlipperPrinter::Ready)
    {
        m_printBed->calibrateBedMesh();
    }
}

void BedMeshWidget::onCalibrateScrewsButtonClicked()
{
    QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_printBed->parent());

    if(printer && printer->status() == QKlipperPrinter::Ready)
    {
        m_printBed->calibrateAdjustmentScrews();
    }
}

void BedMeshWidget::onToolheadHomedChanged()
{
    QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_printBed->parent());

    if(!printer) //invalid cast
        return;

    m_calibrateMeshButton->setEnabled(printer->toolhead()->isHomed());
    m_calibrateScrewsButton->setEnabled(printer->toolhead()->isHomed());
    m_homeButton->setEnabled(!printer->toolhead()->isHomed());
}
