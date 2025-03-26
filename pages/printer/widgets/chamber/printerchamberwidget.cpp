#include "printerchamberwidget.h"
#include "ui_printerchamberwidget.h"

#include "flo/settings.h"

PrinterChamberWidget::PrinterChamberWidget(QKlipperInstance *instance, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PrinterChamberWidget)
{
    ui->setupUi(this);

    ui->chamberTemperatureGauge->setFixedSize(150,150);
    m_chamberTemperatureWidget = new LineGraphWidget(ui->chamberTemperatureFrame);
    ui->chamberTemperatureFrame->layout()->addWidget(m_chamberTemperatureWidget);
    ui->chamberStatusWidget->setHidden(false);

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget"));
    ui->chamberStatusWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget"));

    QDateTime currentTime = QDateTime::currentDateTime();
    currentTime = currentTime.addSecs(currentTime.offsetFromUtc());

    m_chamberTemperatureWidget->data()->setGridMainColor("#666666");
    m_chamberTemperatureWidget->data()->setGridSubColor("#444444");
    m_chamberTemperatureWidget->data()->setAxisYMainColor("#ccccff");
    m_chamberTemperatureWidget->data()->setAxisYSubColor("#eeeeff");
    m_chamberTemperatureWidget->data()->setAxisXMainColor("#ccccff");
    m_chamberTemperatureWidget->data()->setAxisXSubColor("#eeeeff");
    m_chamberTemperatureWidget->data()->setDateMinimum(QDateTime::currentDateTime().addSecs(0).addSecs(currentTime.offsetFromUtc()));
    m_chamberTemperatureWidget->data()->setDateMaximum(QDateTime::currentDateTime().addSecs(10).addSecs(currentTime.offsetFromUtc()));

    m_chamber = instance->printer()->chamber();
    connect(m_chamber, SIGNAL(temperatureeratureChanged()), this, SLOT(onChamberCurrentTemperatureChanged()));
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

void PrinterChamberWidget::onChamberCurrentTemperatureChanged()
{
    m_chamberTemperatureBar->setValue(m_chamber->temperatureerature());

    QDateTime currentTime = QDateTime::currentDateTime();
    currentTime = currentTime.addSecs(currentTime.offsetFromUtc());

    qreal timeNow = QDateTime::currentDateTime().addSecs(currentTime.offsetFromUtc()).addSecs(-30).toSecsSinceEpoch();
    qreal timeDiff = m_chamberTemperatureWidget->dateMinimum().toSecsSinceEpoch() - timeNow;

    m_chamberTemperatureWidget->setDateMinimum(QDateTime::currentDateTime().addSecs(-30).addSecs(currentTime.offsetFromUtc()));

    m_chamberTemperatureWidget->data()->append(
        "extruder",
        QPointF(currentTime.toMSecsSinceEpoch(), m_chamber->temperatureerature())
        );
}

void PrinterChamberWidget::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setIcons();
}
