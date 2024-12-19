#include "sensorcard.h"
#include "system/settings.h"

SensorCard::SensorCard(QKlipperSensor *sensor, QWidget *parent)
    : CardWidget{Widget, parent}
{
    m_sensor = sensor;
    setupUi();
    setTitle(m_sensor->friendlyName());
    setupIcons();
}

void SensorCard::setStyleSheet(const QString &styleSheet)
{
    setupIcons();

    CardWidget::setStyleSheet(styleSheet);
}

void SensorCard::setupUi()
{
    m_centralWidget = new QWidget(this);
    m_centralLayout = new QGridLayout(m_centralWidget);
    m_centralWidget->setLayout(m_centralLayout);

    QStringList keys = m_sensor->values().keys();

    for(const QString &key : keys)
    {
        QLabel *label = new QLabel(m_centralWidget);
        QString description("Unknown Parameter");
        QString unit;
        qreal value = 0.00;

        if(m_sensor->history().contains(key))
            description = m_sensor->history()[key].description();

        if(m_sensor->parameterMap().contains(key))
            unit = m_sensor->parameterMap().value(key);

        if(m_sensor->values().values(key).count() > 0)
            value = m_sensor->values().values(key).first().toFloat();

        QString text = QString("%1: %2%3").arg(
            description,
            QString::number(value),
            unit
        );

        label->setText(text);

        m_centralLayout->addWidget(label);
    }

    m_centralLayout->addItem(
        new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding),
        m_centralLayout->rowCount(),
        0,
        1,
        m_centralLayout->columnCount()
    );

    setCentralWidget(m_centralWidget);
}

void SensorCard::setupIcons()
{
    setIcon(Settings::getThemeIcon("sensor"));
}
