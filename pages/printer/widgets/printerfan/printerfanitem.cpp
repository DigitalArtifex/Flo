#include "printerfanitem.h"
#include "system/settings.h"

PrinterFanItem::PrinterFanItem(QKlipperFan *fan, QWidget *parent)
    : QWidget{parent}
{
    m_fan = fan;

    setupUi();

    onFanNameChanged();
    onFanSpeedChanged();

    connect(m_fan, SIGNAL(nameChanged()), this, SLOT(onFanNameChanged()));
    connect(m_fan, SIGNAL(speedChanged()), this, SLOT(onFanSpeedChanged()));
}

void PrinterFanItem::onFanSpeedChanged()
{
    m_speedLabel->setText(QString("%1%").arg(QString::number(m_fan->speed() * 100, 'f', 0)));

    if(m_fan->speed() > 0)
        m_iconLabel->setPixmap(Settings::getThemeIcon("fan-on").pixmap(m_iconLabel->size()));
    else
        m_iconLabel->setPixmap(Settings::getThemeIcon("fan").pixmap(m_iconLabel->size()));
}

void PrinterFanItem::onFanNameChanged()
{
    QString formattedName = m_fan->name();

    if(formattedName.startsWith(QString("controller_fan ")))
    {
        formattedName = formattedName.remove(QString("controller_fan "));
        formattedName.replace(QString("_"), QString(" "));
    }

    if(formattedName.startsWith(QString("heater_fan ")))
    {
        formattedName = formattedName.remove(QString("heater_fan "));
        formattedName.replace(QString("_"), QString(" "));
    }

    QStringList parts = formattedName.split(' ', Qt::SkipEmptyParts);

    for (int i = 0; i < parts.size(); ++i)
        parts[i].replace(0, 1, parts[i][0].toUpper());

    formattedName = parts.join(' ') + QString(":");

    m_nameLabel->setText(formattedName);
}

void PrinterFanItem::setupUi()
{
    m_centralLayout = new QHBoxLayout(this);
    setLayout(m_centralLayout);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(16,16);
    m_centralLayout->addWidget(m_iconLabel);

    m_nameLabel = new QLabel(this);
    m_centralLayout->addWidget(m_nameLabel);

    m_speedLabel = new QLabel(this);
    m_centralLayout->addWidget(m_speedLabel);
}

void PrinterFanItem::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::StyleChange)
    {
        if(m_fan->speed() > 0)
            m_iconLabel->setPixmap(Settings::getThemeIcon("fan-on").pixmap(m_iconLabel->size()));
        else
            m_iconLabel->setPixmap(Settings::getThemeIcon("fan").pixmap(m_iconLabel->size()));
    }

    QWidget::changeEvent(event);
}
