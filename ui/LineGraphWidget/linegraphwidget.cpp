#include "linegraphwidget.h"

LineGraphWidget::LineGraphWidget(QWidget *parent)
    : QFrame{parent}
{
    m_data = new LineGraphData(this);
    setupViewer();
}

LineGraphWidget::~LineGraphWidget()
{
    delete m_viewer;
    delete m_data;
}

void LineGraphWidget::setupViewer()
{
    m_centralLayout = new QGridLayout(this);
    setLayout(m_centralLayout);

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
    context->setContextProperty("LineGraphData", m_data);

    m_viewer->setTitle(QStringLiteral("Flo Bed Mesh Viewer"));

    m_viewer->setSource(QUrl("qrc:/ui/LineGraphWidget/LineGraphWidget.qml"));
    m_viewer->setResizeMode(QQuickView::SizeRootObjectToView);
    m_viewer->setColor(QColor("#262626"));

    m_viewerWidget = QWidget::createWindowContainer(m_viewer, this);
    m_centralLayout->addWidget(m_viewerWidget, 0, 0);

    m_viewer->show();
}

QString LineGraphWidget::dateLabelFormat() const
{
    return m_data->dateLabelFormat();
}

void LineGraphWidget::setDateLabelFormat(const QString &dateLabelFormat)
{
    m_data->setDateLabelFormat(dateLabelFormat);
}

QString LineGraphWidget::valueLabelFormat() const
{
    return m_data->valueLabelFormat();
}

void LineGraphWidget::setValueLabelFormat(const QString &valueLabelFormat)
{
    m_data->setValueLabelFormat(valueLabelFormat);
}

QString LineGraphWidget::axisXSubColor() const
{
    return m_data->axisXSubColor();
}

qreal LineGraphWidget::valueMinimum() const
{
    return m_data->valueMinimum();
}

qreal LineGraphWidget::valueMaximum() const
{
    return m_data->valueMaximum();
}

QDateTime LineGraphWidget::dateMaximum() const
{
    return m_data->dateMaximum();
}

QDateTime LineGraphWidget::dateMinimum() const
{
    return m_data->dateMinimum();
}

void LineGraphWidget::setAxisXSubColor(const QString &axisXSubColor)
{
    m_data->setAxisXSubColor(axisXSubColor);
}

void LineGraphWidget::setValueMaximum(const qreal &maximum)
{
    m_data->setValueMaximum(maximum);
}

void LineGraphWidget::setValueMinimum(const qreal &minimum)
{
   m_data->setValueMinimum(minimum);
}

void LineGraphWidget::setDateMaximum(const QDateTime &maximum)
{
    m_data->setDateMaximum(maximum);
}

void LineGraphWidget::setDateMinimum(const QDateTime &minimum)
{
    m_data->setDateMinimum(minimum);
}

QString LineGraphWidget::axisXMainColor() const
{
    return m_data->axisXMainColor();
}

void LineGraphWidget::setAxisXMainColor(const QString &axisXMainColor)
{
    m_data->setAxisXMainColor(axisXMainColor);
}

QString LineGraphWidget::axisYSubColor() const
{
    return m_data->axisYSubColor();
}

void LineGraphWidget::setAxisYSubColor(const QString &axisYSubColor)
{
    m_data->setAxisYSubColor(axisYSubColor);
}

QString LineGraphWidget::axisYMainColor() const
{
    return m_data->axisYMainColor();
}

void LineGraphWidget::setAxisYMainColor(const QString &axisYMainColor)
{
    m_data->setAxisYMainColor(axisYMainColor);
}

QString LineGraphWidget::gridSubColor() const
{
    return m_data->gridSubColor();
}

void LineGraphWidget::setGridSubColor(const QString &gridSubColor)
{
    m_data->setGridSubColor(gridSubColor);
}

QString LineGraphWidget::gridMainColor() const
{
    return m_data->gridMainColor();
}

void LineGraphWidget::setGridMainColor(const QString &gridMainColor)
{
    m_data->setGridMainColor(gridMainColor);
}

LineGraphData *LineGraphWidget::data() const
{
    return m_data;
}
