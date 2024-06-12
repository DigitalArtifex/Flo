#include "bedmeshitemframe.h"
#include "ui_bedmeshitemframe.h"

BedMeshItemFrame::BedMeshItemFrame(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::BedMeshItemFrame)
{
    ui->setupUi(this);

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "BedMeshItem"));
}

BedMeshItemFrame::~BedMeshItemFrame()
{
    delete ui;
}

qreal BedMeshItemFrame::value() const
{
    return _value;
}

void BedMeshItemFrame::setValue(qreal value)
{
    _value = value;

    if(_value <= _thresholdLow)
    {
        if(_value <= (_thresholdLow - (_thresholdLow * 0.1)))
            setProperty("level_very_low", true);
        else
        {
            setProperty("level_very_low", false);
            setProperty("level_low", true);
        }
    }
    else if(_value >= _thresholdHigh)
    {
        if(_value <= (_thresholdHigh - (_thresholdHigh * 0.1)))
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
