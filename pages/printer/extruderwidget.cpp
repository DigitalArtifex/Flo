#include "extruderwidget.h"
#include "ui_extruderwidget.h"

ExtruderWidget::ExtruderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtruderWidget)
{
    ui->setupUi(this);
    _temperatureProgressBar = new CircularProgressBar(this);
    ui->progressBarLayout->addWidget(_temperatureProgressBar);

    setUiClasses();
}

ExtruderWidget::~ExtruderWidget()
{
    delete ui;
}

void ExtruderWidget::setTargetTemp(qreal temp)
{
    ui->dashboardExtruderTargetTempLabel->setText(QString::number(temp));
}

void ExtruderWidget::setCurrentTemp(qreal temp)
{
    _temperatureProgressBar->setProgress(temp);
}

void ExtruderWidget::setPressureAdvance(qreal advance)
{
    ui->extruderPressureAdvanceEdit->setText(QString::number(advance));
}

void ExtruderWidget::setSmoothTime(qreal time)
{
    ui->extruderSmoothTimeEdit->setText(QString::number(time));
}

void ExtruderWidget::setExtruder(Extruder *extruder)
{
    _extruder = extruder;
}

void ExtruderWidget::update()
{
    ui->dashboardExtruderTargetTempLabel->setText(QString::number(_extruder->targetTemp()));
    ui->extruderPressureAdvanceEdit->setText(QString::number(_extruder->pressureAdvance()));
    ui->extruderSmoothTimeEdit->setText(QString::number(_extruder->smoothTime()));
    _temperatureProgressBar->setProgress(_extruder->currentTemp());
    ui->materialWidget->setEnabled(_extruder->canExtrude());
    QWidget::update();
}

void ExtruderWidget::setUiClasses()
{
    ui->statsWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));
}
