#include "extruderwidget.h"
#include "ui_extruderwidget.h"

#include "flo/settings.h"

ExtruderWidget::ExtruderWidget(QKlipperExtruder *extruder, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ExtruderWidget)
{
    ui->setupUi(this);
    QStringList buttonClass { "Button", "PrinterActionButton" };

    ui->pidButton->setText("PID Tune");
    ui->preheatButton->setText("Preheat");
    ui->retractButton->setText("Retract");
    ui->extrudeButton->setText("Extrude");

    QDateTime currentTime = QDateTime::currentDateTime();

    m_temperatureGraph = new LineGraphWidget(this);
    m_temperatureGraph->data()->setGridMainColor("#666666");
    m_temperatureGraph->data()->setGridSubColor("#444444");
    m_temperatureGraph->data()->setAxisYMainColor("#ccccff");
    m_temperatureGraph->data()->setAxisYSubColor("#eeeeff");
    m_temperatureGraph->data()->setAxisXMainColor("#ccccff");
    m_temperatureGraph->data()->setAxisXSubColor("#eeeeff");
    m_temperatureGraph->data()->setDateMinimum(QDateTime::currentDateTime().addSecs(0).addSecs(currentTime.offsetFromUtc()));
    m_temperatureGraph->data()->setDateMaximum(QDateTime::currentDateTime().addSecs(10).addSecs(currentTime.offsetFromUtc()));
    ui->graphWidget->layout()->addWidget(m_temperatureGraph);

    ui->graphCard->setTitle("Thermals");
    ui->graphCard->setCentralWidget(ui->graphWidget);

    ui->statusCard->setTitle("Status");
    ui->statusCard->setCentralWidget(ui->statusContentsWidget);

    ui->settingsCard->setTitle("Settings");
    ui->settingsCard->setCentralWidget(ui->settingsContentWidget);

    ui->detailsCard->setTitle("Details");
    ui->detailsCard->setCentralWidget(ui->detailsContentsWidget);

    ui->spoolmanCard->setTitle("Spoolman");
    ui->spoolmanCard->setCentralWidget(ui->spoolmanContentsWidget);

    setUiClasses();
    setIcons();
    setExtruder(extruder);
}

ExtruderWidget::~ExtruderWidget()
{
    delete ui;
}

void ExtruderWidget::setExtruder(QKlipperExtruder *extruder)
{
    m_extruder = extruder;
    connect(m_extruder, SIGNAL(canExtrudeChanged()), this, SLOT(onExtruderCanExtrudeChanged()));
    connect(m_extruder, SIGNAL(temperatureChanged()), this, SLOT(onExtruderCurrentTempChanged()));
    connect(m_extruder, SIGNAL(extrusionFactorChanged()), this, SLOT(onExtruderExtrusionFactorChanged()));
    connect(m_extruder, SIGNAL(maximumTemperatureChanged()), this, SLOT(onExtruderMaxTempChanged()));
    connect(m_extruder, SIGNAL(minimumTemperatureChanged()), this, SLOT(onExtruderMinTempChanged()));
    connect(m_extruder, SIGNAL(pressureAdvanceChanged()), this, SLOT(onExtruderPressureAdvanceChanged()));
    connect(m_extruder, SIGNAL(smoothTimeChanged()), this, SLOT(onExtruderSmoothTimeChanged()));
    connect(m_extruder, SIGNAL(targetTemperatureChanged()), this, SLOT(onExtruderTargetTempChanged()));
    connect(m_extruder, SIGNAL(powerChanged()), this, SLOT(onExtruderPowerChanged()));
    connect(m_extruder, SIGNAL(nozzleDiameterChanged()), this, SLOT(onExtruderNozzleDiameterChanged()));
    connect(m_extruder, SIGNAL(gearRatioChanged()), this, SLOT(onExtruderGearRatioChanged()));

    connect(m_extruder, SIGNAL(fanChanged()), this, SLOT(onExtruderFanChanged()));

    if(m_extruder->fan())
        connect(m_extruder->fan(), SIGNAL(speedChanged()), this, SLOT(onExtruderFanSpeedChanged()));

    connect(m_extruder, SIGNAL(pidCalibrating()), this, SLOT(showThrobber()));
    connect(m_extruder, SIGNAL(pidCalibratingFinished()), this, SLOT(hideThrobber()));

    updateUiValues();
}

void ExtruderWidget::setUiClasses()
{
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget"));
    ui->frame->setProperty("class", QStringList { "Widget", "PrinterWidget" });

    style()->polish(this);
}

void ExtruderWidget::setIcons()
{
    QPixmap pixmap = Settings::getThemeIcon("temperature").pixmap(18,18);
    ui->targetTemperatureeratureIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("pressure-advance").pixmap(18,18);
    ui->pressureAdvanceIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("smooth-time").pixmap(18,18);
    ui->smoothTimeIcon->setPixmap(pixmap);

    ui->pidButton->setIcon(
        Settings::getThemeIcon(
            "sine",
            QColor::fromString(Settings::get("theme/accent-color").toString())
            )
        );
    ui->pidButton->setIconSize(QSize(32,32));

    ui->retractButton->setIcon(
        Settings::getThemeIcon(
            "material-retract",
            QColor::fromString(Settings::get("theme/accent-color3").toString())
            )
        );
    ui->retractButton->setIconSize(QSize(32,32));

    ui->preheatButton->setIcon(
        Settings::getThemeIcon(
            "preheat",
            QColor::fromString(Settings::get("theme/accent-color2").toString())
            )
        );
    ui->preheatButton->setIconSize(QSize(32,32));

    ui->extrudeButton->setIcon(
        Settings::getThemeIcon(
            "material-extrude",
            QColor::fromString(Settings::get("theme/accent-color4").toString())
            )
        );
    ui->extrudeButton->setIconSize(QSize(32,32));

    ui->fanGauge->setIcon(
        Settings::getThemeIcon(
            "fan",
            QColor(Settings::get("theme/accent-color2").toString())
            )
        );
    ui->fanGauge->setIconSize(QSize(16,16));

    ui->powerGauge->setIcon(
        Settings::getThemeIcon(
            "power-device",
            QColor(Settings::get("theme/accent-color3").toString())
            )
        );
    ui->powerGauge->setIconSize(QSize(16,16));

    ui->temperatureGauge->setIcon(
        Settings::getThemeIcon(
            "temperature",
            QColor(Settings::get("theme/accent-color").toString())
            )
        );
    ui->temperatureGauge->setIconSize(QSize(32,32));

    ui->graphCard->setIcon(
        Settings::getThemeIcon(
            "temperature"
            )
        );

    ui->statusCard->setIcon(
        Settings::getThemeIcon(
            "extruder"
            )
        );

    ui->settingsCard->setIcon(
        Settings::getThemeIcon(
            "extruder-settings"
            )
        );

    ui->detailsCard->setIcon(
        Settings::getThemeIcon(
            "details"
            )
        );

    ui->spoolmanCard->setIcon(
        Settings::getThemeIcon(
            "reel"
            )
        );

    style()->polish(this);
}

void ExtruderWidget::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setIcons();

    QFrame::changeEvent(event);
}

void ExtruderWidget::on_targetTemperatureSpinBox_valueChanged(double arg1)
{
    if(!m_updating)
    {
        ui->resetButton->setEnabled((arg1 == m_extruder->targetTemperature()));
        ui->applyButton->setEnabled((arg1 == m_extruder->targetTemperature()));

        m_targetTemperatureEdited = (arg1 == m_extruder->targetTemperature());

        updateSettingsButtons();
    }
}


void ExtruderWidget::on_pressureAdvanceSpinBox_valueChanged(double arg1)
{
    if(!m_updating)
    {
        ui->resetButton->setEnabled((arg1 == m_extruder->pressureAdvance()));
        ui->applyButton->setEnabled((arg1 == m_extruder->pressureAdvance()));

        m_pressureAdvanceEdited = (arg1 == m_extruder->pressureAdvance());
    }
}


void ExtruderWidget::on_smoothTimeSpinBox_valueChanged(double arg1)
{
    if(!m_updating)
    {
        ui->resetButton->setEnabled((arg1 == m_extruder->smoothTime()));
        ui->applyButton->setEnabled((arg1 == m_extruder->smoothTime()));

        m_smoothTimeEdited = (arg1 == m_extruder->smoothTime());
    }
}


void ExtruderWidget::on_applyButton_clicked()
{
    ui->resetButton->setEnabled(false);
    ui->applyButton->setEnabled(false);

    //check for changes in target temp
    if(m_extruder->targetTemperature() != ui->targetTemperatureSpinBox->value())
        m_extruder->setTargetTemperature(ui->targetTemperatureSpinBox->value());

    m_targetTemperatureEdited = false;
    m_smoothTimeEdited = false;
    m_pressureAdvanceEdited = false;
    m_extrusionFactorEdited = false;

    //updateUiValues();
}

void ExtruderWidget::on_resetButton_clicked()
{
    ui->resetButton->setEnabled(false);
    ui->applyButton->setEnabled(false);

    m_targetTemperatureEdited = false;
    m_smoothTimeEdited = false;
    m_pressureAdvanceEdited = false;
    m_extrusionFactorEdited = false;

    updateUiValues();
}

void ExtruderWidget::on_extrudeButton_clicked()
{
    if(m_materialDialog)
        delete m_materialDialog;

    m_materialDialog = new ExtruderMaterialsDialog(this);
    m_materialDialog->setMaterialDirection(ExtruderMaterialsDialog::MaterialExtrude);
    emit dialogRequested(m_materialDialog);

    connect(m_materialDialog, SIGNAL(finished(int)), this, SLOT(onMaterialDialogFinished(int)));
}

void ExtruderWidget::on_retractButton_clicked()
{
    if(m_materialDialog)
        delete m_materialDialog;

    m_materialDialog = new ExtruderMaterialsDialog(this);
    m_materialDialog->setMaterialDirection(ExtruderMaterialsDialog::MaterialRetract);
    emit dialogRequested(m_materialDialog);

    connect(m_materialDialog, SIGNAL(finished(int)), this, SLOT(onMaterialDialogFinished(int)));
}

void ExtruderWidget::onPidDialogFinished(int returnCode)
{
    qreal temp = m_pidDialog->target();
    delete m_pidDialog;
    m_pidDialog = nullptr;

    if(returnCode == QDialog::Accepted)
        m_extruder->calibratePid(temp);
}

void ExtruderWidget::onMaterialDialogFinished(int returnCode)
{
    qreal distance = m_materialDialog->distance();
    qreal speed = m_materialDialog->speed();
    ExtruderMaterialsDialog::MaterialDirection direction = m_materialDialog->materialDirection();
    delete m_materialDialog;
    m_materialDialog = nullptr;

    if(returnCode == QDialog::Accepted && direction == ExtruderMaterialsDialog::MaterialExtrude)
        m_extruder->extrude(distance, speed);
    else if(returnCode == QDialog::Accepted && direction == ExtruderMaterialsDialog::MaterialRetract)
        m_extruder->retract(distance, speed);
}

void ExtruderWidget::onPreheatDialogFinished(int returnCode)
{
    qreal temp = m_preheatDialog->target();
    delete m_preheatDialog;
    m_preheatDialog = nullptr;

    if(returnCode == QDialog::Accepted)
        m_extruder->setTargetTemperature(temp);
}

void ExtruderWidget::onExtruderCanExtrudeChanged()
{
    ui->retractButton->setEnabled(m_extruder->canExtrude());
    ui->extrudeButton->setEnabled(m_extruder->canExtrude());

    if(m_extruder->canExtrude())
        ui->gearRatioLabel->setText(QString("<h3>Can Extrude</h3><p>Yes</p>"));
    else
        ui->gearRatioLabel->setText(QString("<h3>Can Extrude</h3><p>No</p>"));
}

void ExtruderWidget::onExtruderCurrentTempChanged()
{
    ui->temperatureGauge->setValue(m_extruder->temperature());

    QDateTime currentTime = QDateTime::currentDateTime();
    currentTime = currentTime.addSecs(currentTime.offsetFromUtc());

    qreal timeNow = QDateTime::currentDateTime().addSecs(currentTime.offsetFromUtc()).addSecs(-30).toSecsSinceEpoch();
    qreal timeDiff = m_temperatureGraph->dateMinimum().toSecsSinceEpoch() - timeNow;

        m_temperatureGraph->setDateMinimum(QDateTime::currentDateTime().addSecs(-30).addSecs(currentTime.offsetFromUtc()));

    m_temperatureGraph->data()->append(
        "extruder",
        QPointF(currentTime.toMSecsSinceEpoch(), m_extruder->temperature())
    );
}

void ExtruderWidget::onExtruderTargetTempChanged()
{
    //set updating flag to prevent this from registering as a change event
    m_updating = true;

    //make sure it has not been or is currently being edited
    if(!ui->targetTemperatureSpinBox->hasFocus() && !m_targetTemperatureEdited)
        ui->targetTemperatureSpinBox->setValue(m_extruder->targetTemperature());

    //ui->dashboardExtruderTargetTempLabel->setText(QString::number(m_extruder->targetTemperature()) + QString("°"));

    m_updating = false;
}

void ExtruderWidget::onExtruderGearRatioChanged()
{
    ui->gearRatioLabel->setText(QString("<h3>Gear Ratio</h3><p>%1:%2</p>").arg(m_extruder->gearRatio().first).arg(m_extruder->gearRatio().second));
}

void ExtruderWidget::onExtruderNozzleDiameterChanged()
{
    ui->nozzleDiameterLabel->setText(QString("<h3>Nozzle Diameter</h3><p>%1</p>").arg(QString::number(m_extruder->nozzleDiameter(), 'f', 2)));
}

void ExtruderWidget::onExtruderMaxTempChanged()
{
    ui->maximumTemperatureeratureLabel->setText(QString("<h3>Max Temperature</h3><p>%1</p>").arg(QString::number(m_extruder->maximumTemperature(), 'f', 2)));
    ui->temperatureGauge->setMaximum(m_extruder->maximumTemperature());
}

void ExtruderWidget::onExtruderMinTempChanged()
{
    ui->temperatureGauge->setMaximum(m_extruder->minimumTemperature());
}

void ExtruderWidget::onExtruderPressureAdvanceChanged()
{
    //set updating flag to prevent this from registering as a change event
    m_updating = true;

    // //make sure it has not been or is currently being edited
    if(!ui->pressureAdvanceSpinBox->hasFocus() && !m_pressureAdvanceEdited)
        ui->pressureAdvanceSpinBox->setValue(m_extruder->pressureAdvance());

    m_updating = false;
}

void ExtruderWidget::onExtruderSmoothTimeChanged()
{
    //set updating flag to prevent this from registering as a change event
    m_updating = true;

    // //make sure it has not been or is currently being edited
    if(!ui->smoothTimeSpinBox->hasFocus() && !m_smoothTimeEdited)
        ui->smoothTimeSpinBox->setValue(m_extruder->smoothTime());

    m_updating = false;
}

void ExtruderWidget::onExtruderFanSpeedChanged()
{
    ui->fanGauge->setValue((m_extruder->fan()->speed() * 100));
}

void ExtruderWidget::onExtruderPowerChanged()
{
    ui->powerGauge->setValue((m_extruder->power() * 100));
}

void ExtruderWidget::onExtruderFanChanged()
{
    if(m_extruder->fan())
        connect(m_extruder->fan(), SIGNAL(speedChanged()), this, SLOT(onExtruderFanSpeedChanged()));
}

void ExtruderWidget::updateUiValues()
{
    //set updating flag to prevent this from registering as a change event
    m_updating = true;

    ui->fanGauge->setValue((m_extruder->fan()->speed() * 100));

    ui->powerGauge->setValue((m_extruder->power() * 100));

    //make sure it has not been or is currently being edited
    if(!ui->targetTemperatureSpinBox->hasFocus() && !m_targetTemperatureEdited)
        ui->targetTemperatureSpinBox->setValue(m_extruder->targetTemperature());

    //ui->dashboardExtruderTargetTempLabel->setText(QString::number(m_extruder->targetTemperature()) + QString("°"));
    ui->temperatureGauge->setMaximum(m_extruder->maximumTemperature());
    ui->temperatureGauge->setValue(m_extruder->temperature());

    onExtruderCanExtrudeChanged();
    onExtruderGearRatioChanged();
    onExtruderNozzleDiameterChanged();

    //unset updating flag to resume change events
    m_updating = false;
}

void ExtruderWidget::updateSettingsButtons()
{
    bool changed = (
        (ui->targetTemperatureSpinBox->value() != m_extruder->targetTemperature())
        || (ui->smoothTimeSpinBox->value() != m_extruder->smoothTime())
        || (ui->pressureAdvanceSpinBox->value() != m_extruder->pressureAdvance())
    );

    ui->applyButton->setEnabled(changed);
    ui->resetButton->setEnabled(changed);
}

void ExtruderWidget::showThrobber()
{
    if(!m_throbberFrame)
    {
        m_throbberFrame = new QFrame(this);

        QVBoxLayout *layout = new QVBoxLayout(m_throbberFrame);
        m_throbberFrame->setFixedSize(width(), height());
        m_throbberFrame->setLayout(layout);
        m_throbberFrame->setProperty("class", "PopupOverlay");
        m_throbberFrame->setStyleSheet(Settings::currentTheme());
        m_throbberFrame->setVisible(true);
        m_throbberFrame->raise();

        m_throbber = new QThrobberWidget(m_throbberFrame);
        m_throbber->setFixedSize(150, 150);
        m_throbber->setThrobberWidth(4);
        m_throbber->setText("Calibrating");

        layout->addWidget(m_throbber, 0, Qt::AlignCenter);
        m_throbber->start();
    }
}

void ExtruderWidget::hideThrobber()
{
    if(m_throbberFrame)
    {
        m_throbber->stop();
        m_throbberFrame->hide();

        delete m_throbberFrame;
        m_throbberFrame = nullptr;
    }
}

void ExtruderWidget::on_pidButton_clicked()
{
    if(m_pidDialog)
        delete m_pidDialog;

    m_pidDialog = new PidDialog(this);
    emit dialogRequested(m_pidDialog);

    connect(m_pidDialog, SIGNAL(finished(int)), this, SLOT(onPidDialogFinished(int)));
}

void ExtruderWidget::on_preheatButton_clicked()
{
    if(m_preheatDialog)
        delete m_preheatDialog;

    m_preheatDialog = new PidDialog(this);
    emit dialogRequested(m_preheatDialog);

    connect(m_preheatDialog, SIGNAL(finished(int)), this, SLOT(onPreheatDialogFinished(int)));
}
