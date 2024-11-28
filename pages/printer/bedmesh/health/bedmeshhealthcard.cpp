#include "bedmeshhealthcard.h"

BedMeshHealthCard::BedMeshHealthCard(BedMeshData *data, QWidget *parent)
    : CardWidget(Widget, parent)
{
    m_meshData = data;
    setupUi();
    setIcons();

    connect(m_meshData, SIGNAL(dataChanged()), this, SLOT(onBedMeshUpdated()));
}

void BedMeshHealthCard::setStyleSheet(const QString &stylesheet)
{
    setIcons();

    CardWidget::setStyleSheet(stylesheet);
}

void BedMeshHealthCard::setupUi()
{
    setTitle("Mesh Health");

    m_centralWidget = new QWidget(this);
    m_centralLayout = new QGridLayout(m_centralWidget);
    m_centralWidget->setLayout(m_centralLayout);

    m_minLabel = new QLabel(m_centralWidget);
    m_minLabel->setText("Minimum: ");
    m_centralLayout->addWidget(m_minLabel, 0, 0, 1, 1);

    m_maxLabel = new QLabel(m_centralWidget);
    m_maxLabel->setText("Maximum: ");
    m_centralLayout->addWidget(m_maxLabel, 1, 0, 1, 1);

    m_varianceLabel = new QLabel(m_centralWidget);
    m_varianceLabel->setText("Variance: ");
    m_centralLayout->addWidget(m_varianceLabel, 2, 0, 1, 1);

    m_centralLayout->addItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Preferred), 3, 0, 1, 1);

    m_statusIconLabel = new QLabel(m_centralWidget);
    m_statusIconLabel->setFixedSize(100,100);
    m_centralLayout->addWidget(m_statusIconLabel, 0, 1, 4, 1, Qt::AlignTop);

    m_bedHealth = new QProgressBar(m_centralWidget);
    m_bedHealth->setFormat("Health: %p\%");
    m_bedHealth->setFixedHeight(35);
    m_centralLayout->addWidget(m_bedHealth, 4, 0, 1, 2);

    setCentralWidget(m_centralWidget);
}

void BedMeshHealthCard::setIcons()
{
    setIcon(Settings::getThemeIcon("health-icon"));
}

void BedMeshHealthCard::onBedMeshUpdated()
{
    m_minLabel->setText(QString("Minimum: %1mm").arg(QString::number(m_meshData->minimum(), 'f', 2)));
    m_maxLabel->setText(QString("Maximum: %1mm").arg(QString::number(m_meshData->maximum(), 'f', 2)));

    qreal variance = m_meshData->maximum() - m_meshData->minimum();
    m_varianceLabel->setText(QString("Variance: %1mm").arg(QString::number(variance, 'f', 2)));

    qreal health = (1 - (variance / 0.3000)) * 100;
    m_bedHealth->setValue(health);

    if(health > 50.0)
    {
        m_statusIconLabel->setPixmap(Settings::getThemeIcon("thumbs-up-icon").pixmap(100,100));
    }
    else
        m_statusIconLabel->setPixmap(Settings::getThemeIcon("thumbs-down-icon").pixmap(100,100));
}
