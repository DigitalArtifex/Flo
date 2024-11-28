#include "bedmeshitemframe.h"
#include "ui_bedmeshitemframe.h"

BedMeshItemFrame::BedMeshItemFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::BedMeshItemFrame)
{
    ui->setupUi(this);

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "BedMeshItem"));
    setFixedSize(75, 75);
}

BedMeshItemFrame::~BedMeshItemFrame()
{
    delete ui;
}

qreal BedMeshItemFrame::value() const
{
    return m_value;
}

void BedMeshItemFrame::setValue(qreal value)
{
    m_value = value;

    if(m_value <= m_thresholdLow)
    {
        if(m_value <= (m_thresholdLow - (m_thresholdLow * 0.1)))
            setProperty("level_very_low", true);
        else
        {
            setProperty("level_very_low", false);
            setProperty("level_low", true);
        }
    }
    else if(m_value >= m_thresholdHigh)
    {
        if(m_value <= (m_thresholdHigh - (m_thresholdHigh * 0.1)))
            setProperty("level_very_high", true);
        else
        {
            setProperty("level_very_high", false);
            setProperty("level_high", true);
        }
    }
    else
    {
        setProperty("level_low", false);
        setProperty("level_high", false);
        setProperty("level_very_low", false);
        setProperty("level_very_high", false);
    }

    ui->valueLabel->setText(QString::number(value));

    style()->polish(this);
}
