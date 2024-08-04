#include "extruderwidget.h"
#include "ui_extruderwidget.h"

#include "../../../../system/settings.h"

ExtruderWidget::ExtruderWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ExtruderWidget)
{
    ui->setupUi(this);
    m_temperatureProgressBar = new CircularProgressBar(this, CircularProgressBar::Temperature);
    ui->progressBarLayout->addWidget(m_temperatureProgressBar);

    setUiClasses();
    setIcons();
}

ExtruderWidget::~ExtruderWidget()
{
    delete ui;
}

void ExtruderWidget::setExtruder(Extruder *extruder)
{
    m_extruder = extruder;
    connect(m_extruder->printer()->console(), SIGNAL(extrudersUpdate()), this, SLOT(on_console_extrudersUpdate()));
}

void ExtruderWidget::setUiClasses()
{
    ui->statsWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));
    ui->materialWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));
    ui->extruderWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));

    ui->titleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));
    ui->titleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    ui->materialTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidgetTitleBar"));
    ui->materialTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    ui->settingsTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidgetTitleBar"));
    ui->settingsTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget"));

    style()->polish(this);
}

void ExtruderWidget::setStyleSheet(QString &styleSheet)
{
    QFrame::setStyleSheet(styleSheet);

    setIcons();

    style()->polish(this);
}

void ExtruderWidget::setIcons()
{
    QPixmap pixmap = Settings::getThemeIcon("extruder-icon").pixmap(28,28);
    ui->extruderIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("temperature-icon").pixmap(18,18);
    ui->targetTemperatureIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("pressure-advance-icon").pixmap(18,18);
    ui->pressureAdvanceIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("smooth-time-icon").pixmap(18,18);
    ui->smoothTimeIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("extrusion-factor-icon").pixmap(18,18);
    ui->extrusionFactorIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("material-icon").pixmap(18,18);
    ui->materialFrameIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("settings-icon").pixmap(18,18);
    ui->settingsFrameIcon->setPixmap(pixmap);

    style()->polish(this);
}

void ExtruderWidget::on_extrsuionFactorSlider_valueChanged(int value)
{
    //disconnect event to prevent looping
    disconnect(ui->extrusionFactorSpinBox, SIGNAL(valueChanged(double)), this, SLOT(on_extrusionFactorSpinBox_valueChanged(double)));

    //change value of spin box
    ui->extrusionFactorSpinBox->setValue((double)value / 100);

    if(!m_updating)
    {
        ui->resetButton->setEnabled(true);
        ui->applyButton->setEnabled(true);

        m_extrusionFactorEdited = true;
    }

    //reconnect event
    connect(ui->extrusionFactorSpinBox, SIGNAL(valueChanged(double)), this, SLOT(on_extrusionFactorSpinBox_valueChanged(double)));
}

void ExtruderWidget::on_extrusionFactorSpinBox_valueChanged(double value)
{
    //disconnect event to prevent looping
    disconnect(ui->extrsuionFactorSlider, SIGNAL(valueChanged(int)), this, SLOT(on_extrsuionFactorSlider_valueChanged(int)));

    //change value of slider
    ui->extrsuionFactorSlider->setValue(value * 100);

    if(!m_updating)
    {
        ui->resetButton->setEnabled(true);
        ui->applyButton->setEnabled(true);

        m_extrusionFactorEdited = true;
    }

    //reconnect event
    connect(ui->extrsuionFactorSlider, SIGNAL(valueChanged(int)), this, SLOT(on_extrsuionFactorSlider_valueChanged(int)));
}

void ExtruderWidget::on_console_extrudersUpdate()
{
    //set updating flag to prevent this from registering as a change event
    m_updating = true;

    //make sure it has not been or is currently being edited
    if(!ui->targetTempSpinBox->hasFocus() && !m_targetTempEdited)
        ui->targetTempSpinBox->setValue(m_extruder->targetTemp());

    //make sure it has not been or is currently being edited
    if(!ui->pressureAdvanceSpinBox->hasFocus() && !m_pressureAdvanceEdited)
        ui->pressureAdvanceSpinBox->setValue(m_extruder->pressureAdvance());

    //make sure it has not been or is currently being edited
    if(!ui->smoothTimeSpinBox->hasFocus() && !m_smoothTimeEdited)
        ui->smoothTimeSpinBox->setValue(m_extruder->smoothTime());

    //make sure it has not been or is currently being edited
    if(!ui->extrusionFactorSpinBox->hasFocus() && !m_extrusionFactorEdited)
        ui->extrusionFactorSpinBox->setValue(m_extruder->extrusionFactor());

    ui->dashboardExtruderTargetTempLabel->setText(QString::number(m_extruder->targetTemp()) + QString("°"));
    m_temperatureProgressBar->setProgress(m_extruder->currentTemp());
    m_temperatureProgressBar->setMaximum(m_extruder->maxTemp());
    ui->materialWidget->setEnabled(m_extruder->canExtrude());

    //set fan labels
    ui->extruderFanValueLabel->setText(QString::number(m_extruder->fan()->speed() * 100) + QString("%"));
    ui->partsFanValueLabel->setText(QString::number(m_extruder->printer()->toolhead()->fan()->speed() * 100) + QString("%"));


    //unset updating flag to resume change events
    m_updating = false;
}


void ExtruderWidget::on_targetTempSpinBox_valueChanged(double arg1)
{
    if(!m_updating)
    {
        ui->resetButton->setEnabled(true);
        ui->applyButton->setEnabled(true);

        m_targetTempEdited = true;
    }
}


void ExtruderWidget::on_pressureAdvanceSpinBox_valueChanged(double arg1)
{
    if(!m_updating)
    {
        ui->resetButton->setEnabled(true);
        ui->applyButton->setEnabled(true);

        m_pressureAdvanceEdited = true;
    }
}


void ExtruderWidget::on_smoothTimeSpinBox_valueChanged(double arg1)
{
    if(!m_updating)
    {
        ui->resetButton->setEnabled(true);
        ui->applyButton->setEnabled(true);

        m_smoothTimeEdited = true;
    }
}


void ExtruderWidget::on_applyButton_clicked()
{
    ui->resetButton->setEnabled(false);
    ui->applyButton->setEnabled(false);

    //check for changes in target temp
    if(m_extruder->targetTemp() != ui->targetTempSpinBox->value())
        m_extruder->setTargetTemp(ui->targetTempSpinBox->value());

    //check for changes in smooth time or pressure advance
    if (m_extruder->pressureAdvance() != ui->pressureAdvanceSpinBox->value() ||
        m_extruder->smoothTime() != ui->smoothTimeSpinBox->value())
    {
        m_extruder->setPressureAdvance(ui->pressureAdvanceSpinBox->value(), ui->smoothTimeSpinBox->value());
    }

    //check for changes in extrusion factor
    if(m_extruder->extrusionFactor() != ui->extrusionFactorSpinBox->value())
        m_extruder->setExtrusionFactor(ui->extrusionFactorSpinBox->value());

    m_targetTempEdited = false;
    m_smoothTimeEdited = false;
    m_pressureAdvanceEdited = false;
    m_extrusionFactorEdited = false;

    on_console_extrudersUpdate();
}


void ExtruderWidget::on_resetButton_clicked()
{
    ui->resetButton->setEnabled(false);
    ui->applyButton->setEnabled(false);

    m_targetTempEdited = false;
    m_smoothTimeEdited = false;
    m_pressureAdvanceEdited = false;
    m_extrusionFactorEdited = false;

    on_console_extrudersUpdate();
}


void ExtruderWidget::on_extrudeButton_clicked()
{
    qreal amount = ui->materialLengthSpinBox->value();
    qreal rate = ui->materialFeedRateSpinBox->value();

    m_extruder->extrude(amount, rate);
}


void ExtruderWidget::on_retractButton_clicked()
{
    qreal amount = ui->materialLengthSpinBox->value();
    qreal rate = ui->materialFeedRateSpinBox->value();

    m_extruder->retract(amount, rate);
}

