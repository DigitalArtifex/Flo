#include "bedmeshwidget.h"
#include "qabstractaxis.h"
#include "system/settings.h"

BedMeshWidget::BedMeshWidget(QKlipperPrintBed *bed, QWidget *parent) : QWidget(parent)
{
    m_printBed = bed;
    m_data = new BedMeshData(m_printBed, this);

    setupUi();
    setupViewer();
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
}

void BedMeshWidget::setupUi()
{
    m_layout = new QGridLayout(this);
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
    context->setContextProperty( "BedMeshData", m_data);
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

    m_layout->addWidget(m_viewerWidget);

    m_viewer->show();
}
