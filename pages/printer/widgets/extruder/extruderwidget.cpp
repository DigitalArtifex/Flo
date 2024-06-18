#include "extruderwidget.h"
#include "ui_extruderwidget.h"

#include "../../../../system/settings.h"

ExtruderWidget::ExtruderWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ExtruderWidget)
{
    ui->setupUi(this);
    _temperatureProgressBar = new CircularProgressBar(this, CircularProgressBar::Temperature);
    ui->progressBarLayout->addWidget(_temperatureProgressBar);

    setUiClasses();
    setIcons();
}

ExtruderWidget::~ExtruderWidget()
{
    delete ui;
}

void ExtruderWidget::setExtruder(Extruder *extruder)
{
    _extruder = extruder;
    connect(_extruder->printer()->console(), SIGNAL(extrudersUpdate()), this, SLOT(on_console_extrudersUpdate()));
}

void ExtruderWidget::update()
{
    QWidget::update();
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

    if(!_updating)
    {
        ui->resetButton->setEnabled(true);
        ui->applyButton->setEnabled(true);

        _extrusionFactorEdited = true;
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

    if(!_updating)
    {
        ui->resetButton->setEnabled(true);
        ui->applyButton->setEnabled(true);

        _extrusionFactorEdited = true;
    }

    //reconnect event
    connect(ui->extrsuionFactorSlider, SIGNAL(valueChanged(int)), this, SLOT(on_extrsuionFactorSlider_valueChanged(int)));
}

void ExtruderWidget::on_console_extrudersUpdate()
{
    //set updating flag to prevent this from registering as a change event
    _updating = true;

    //make sure it has not been or is currently being edited
    if(!ui->targetTempSpinBox->hasFocus() && !_targetTempEdited)
        ui->targetTempSpinBox->setValue(_extruder->targetTemp());

    //make sure it has not been or is currently being edited
    if(!ui->pressureAdvanceSpinBox->hasFocus() && !_pressureAdvanceEdited)
        ui->pressureAdvanceSpinBox->setValue(_extruder->pressureAdvance());

    //make sure it has not been or is currently being edited
    if(!ui->smoothTimeSpinBox->hasFocus() && !_smoothTimeEdited)
        ui->smoothTimeSpinBox->setValue(_extruder->smoothTime());

    //make sure it has not been or is currently being edited
    if(!ui->extrusionFactorSpinBox->hasFocus() && !_extrusionFactorEdited)
        ui->extrusionFactorSpinBox->setValue(_extruder->extrusionFactor());

    ui->dashboardExtruderTargetTempLabel->setText(QString::number(_extruder->targetTemp()) + QString("°"));
    _temperatureProgressBar->setProgress(_extruder->currentTemp());
    _temperatureProgressBar->setMaximum(_extruder->maxTemp());
    ui->materialWidget->setEnabled(_extruder->canExtrude());

    //set fan labels
    ui->extruderFanValueLabel->setText(QString::number(_extruder->fan()->speed() * 100) + QString("%"));
    ui->partsFanValueLabel->setText(QString::number(_extruder->printer()->toolhead()->fan()->speed() * 100) + QString("%"));


    //unset updating flag to resume change events
    _updating = false;
}


void ExtruderWidget::on_targetTempSpinBox_valueChanged(double arg1)
{
    if(!_updating)
    {
        ui->resetButton->setEnabled(true);
        ui->applyButton->setEnabled(true);

        _targetTempEdited = true;
    }
}


void ExtruderWidget::on_pressureAdvanceSpinBox_valueChanged(double arg1)
{
    if(!_updating)
    {
        ui->resetButton->setEnabled(true);
        ui->applyButton->setEnabled(true);

        _pressureAdvanceEdited = true;
    }
}


void ExtruderWidget::on_smoothTimeSpinBox_valueChanged(double arg1)
{
    if(!_updating)
    {
        ui->resetButton->setEnabled(true);
        ui->applyButton->setEnabled(true);

        _smoothTimeEdited = true;
    }
}


void ExtruderWidget::on_applyButton_clicked()
{
    ui->resetButton->setEnabled(false);
    ui->applyButton->setEnabled(false);

    //check for changes in target temp
    if(_extruder->targetTemp() != ui->targetTempSpinBox->value())
        _extruder->setTargetTemp(ui->targetTempSpinBox->value());

    //check for changes in smooth time or pressure advance
    if (_extruder->pressureAdvance() != ui->pressureAdvanceSpinBox->value() ||
        _extruder->smoothTime() != ui->smoothTimeSpinBox->value())
    {
        _extruder->setPressureAdvance(ui->pressureAdvanceSpinBox->value(), ui->smoothTimeSpinBox->value());
    }

    //check for changes in extrusion factor
    if(_extruder->extrusionFactor() != ui->extrusionFactorSpinBox->value())
        _extruder->setExtrusionFactor(ui->extrusionFactorSpinBox->value());

    _targetTempEdited = false;
    _smoothTimeEdited = false;
    _pressureAdvanceEdited = false;
    _extrusionFactorEdited = false;

    on_console_extrudersUpdate();
}


void ExtruderWidget::on_resetButton_clicked()
{
    ui->resetButton->setEnabled(false);
    ui->applyButton->setEnabled(false);

    _targetTempEdited = false;
    _smoothTimeEdited = false;
    _pressureAdvanceEdited = false;
    _extrusionFactorEdited = false;

    on_console_extrudersUpdate();
}


void ExtruderWidget::on_extrudeButton_clicked()
{
    qreal amount = ui->materialLengthSpinBox->value();
    qreal rate = ui->materialFeedRateSpinBox->value();

    _extruder->extrude(amount, rate);
}


void ExtruderWidget::on_retractButton_clicked()
{
    qreal amount = ui->materialLengthSpinBox->value();
    qreal rate = ui->materialFeedRateSpinBox->value();

    _extruder->retract(amount, rate);
}

