#include "printerchamberwidget.h"
#include "ui_printerchamberwidget.h"

#include "flo/settings.h"

PrinterChamberWidget::PrinterChamberWidget(QKlipperInstance *instance, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PrinterChamberWidget)
{
    ui->setupUi(this);

    ui->chamberTemperatureGauge->setFixedSize(150,150);
    m_chamberTemperatureWidget = new PrinterTemperatureWidget(instance, ui->chamberTemperatureFrame);
    ui->chamberTemperatureFrame->layout()->addWidget(m_chamberTemperatureWidget);
    ui->chamberStatusWidget->setHidden(false);

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget"));
    ui->chamberStatusWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget"));
}

PrinterChamberWidget::~PrinterChamberWidget()
{
    delete ui;
}

void PrinterChamberWidget::setIcons()
{
    ui->chamberTemperatureIconLabel->setPixmap(Settings::getThemeIcon("temperature").pixmap(20,20));
    ui->chamberTemperatureGauge->setIcon(
        Settings::getThemeIcon(QString("temperature"))
        );
}

void PrinterChamberWidget::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setIcons();
}
