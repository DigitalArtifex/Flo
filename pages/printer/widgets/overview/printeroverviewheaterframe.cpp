#include "printeroverviewheaterframe.h"
#include "ui_printeroverviewheaterframe.h"

PrinterOverviewHeaterFrame::PrinterOverviewHeaterFrame(QKlipperHeater *heater, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PrinterOverviewHeaterFrame)
{
    ui->setupUi(this);

    m_heater = heater;

    QString name = m_heater->name();
    name.replace(0, 1, name.at(0).toUpper());

    ui->label->setText(name);
    onHeaterPowerChanged();
    connect(m_heater, SIGNAL(powerChanged()), this, SLOT(onHeaterPowerChanged()));
}

PrinterOverviewHeaterFrame::~PrinterOverviewHeaterFrame()
{
    delete ui;
}

void PrinterOverviewHeaterFrame::onHeaterPowerChanged()
{
    QIndicatorWidget::State state = QIndicatorWidget::State::Off;

    if(m_heater->power() > 0)
        state = QIndicatorWidget::State::On;

    ui->indicatorWidget->setState(state);
}
