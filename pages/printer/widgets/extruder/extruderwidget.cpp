#include "extruderwidget.h"
#include "ui_extruderwidget.h"

#include "../../../../system/settings.h"

ExtruderWidget::ExtruderWidget(QKlipperExtruder *extruder, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ExtruderWidget)
{
    ui->setupUi(this);
    m_temperatureProgressBar = new CircularProgressBar(this, CircularProgressBar::Temperature);
    m_temperatureProgressBar->setFixedSize(150,150);
    m_temperatureProgressBar->setIconSize(QSize(36,36));
    ui->progressBarLayout->addWidget(m_temperatureProgressBar);

    m_powerProgressBar = new CircularProgressBar(this, CircularProgressBar::Percent);
    ui->partsFanLayout->addWidget(m_powerProgressBar);

    m_extruderFanProgressBar = new CircularProgressBar(this, CircularProgressBar::Percent);
    ui->extruderFanLayout->addWidget(m_extruderFanProgressBar);

    m_temperatureWidget = new ExtruderTemperatureWidget(extruder, ui->graphWidget);
    ui->graphWidget->layout()->addWidget(m_temperatureWidget);

    ui->targetTempSpinBox->setAttribute(Qt::WA_InputMethodEnabled, true);
    ui->targetTempSpinBox->setInputMethodHints(inputMethodHints() | Qt::InputMethodHint::ImhDigitsOnly);

    ui->extrusionFactorSpinBox->setAttribute(Qt::WA_InputMethodEnabled, true);
    ui->extrusionFactorSpinBox->setInputMethodHints(inputMethodHints() | Qt::InputMethodHint::ImhDigitsOnly);

    QGridLayout *buttonLayout = qobject_cast<QGridLayout*>(ui->buttonWidget->layout());

    if(buttonLayout)
    {
        QStringList buttonClass { "Button", "PrinterActionButton" };

        m_pidTuneButton = new QIconButton(this);
        m_pidTuneButton->setIconSize(QSize(36,36));
        m_pidTuneButton->setFixedSize(QSize(100,100));
        m_pidTuneButton->setText("PID Tune");
        m_pidTuneButton->setTextAlignment(Qt::AlignBottom | Qt::AlignHCenter);
        m_pidTuneButton->setIconAlignment(Qt::AlignCenter);
        m_pidTuneButton->setProperty("class", buttonClass);
        buttonLayout->addWidget(m_pidTuneButton, 0, 0);

        m_materialButton = new QIconButton(this);
        m_materialButton->setIconSize(QSize(36,36));
        m_materialButton->setFixedSize(QSize(100,100));
        m_materialButton->setText("Retract");
        m_materialButton->setTextAlignment(Qt::AlignBottom | Qt::AlignHCenter);
        m_materialButton->setIconAlignment(Qt::AlignCenter);
        m_materialButton->setProperty("class", buttonClass);
        buttonLayout->addWidget(m_materialButton, 1, 0);

        m_preheatButton = new QIconButton(this);
        m_preheatButton->setIconSize(QSize(36,36));
        m_preheatButton->setFixedSize(QSize(100,100));
        m_preheatButton->setText("Preheat");
        m_preheatButton->setTextAlignment(Qt::AlignBottom | Qt::AlignHCenter);
        m_preheatButton->setIconAlignment(Qt::AlignCenter);
        m_preheatButton->setProperty("class", buttonClass);
        buttonLayout->addWidget(m_preheatButton, 0, 1);

        m_setOffsetButton = new QIconButton(this);
        m_setOffsetButton->setIconSize(QSize(36,36));
        m_setOffsetButton->setFixedSize(QSize(100,100));
        m_setOffsetButton->setText("Extrude");
        m_setOffsetButton->setTextAlignment(Qt::AlignBottom | Qt::AlignHCenter);
        m_setOffsetButton->setIconAlignment(Qt::AlignCenter);
        m_setOffsetButton->setProperty("class", buttonClass);
        buttonLayout->addWidget(m_setOffsetButton, 1, 1);

        m_settingsButton = new QIconButton(this);
        m_settingsButton->setIconSize(QSize(36,36));
        m_settingsButton->setFixedSize(QSize(100,206));
        m_settingsButton->setText("Settings");
        m_settingsButton->setTextAlignment(Qt::AlignBottom | Qt::AlignHCenter);
        m_settingsButton->setIconAlignment(Qt::AlignCenter);
        m_settingsButton->setProperty("class", buttonClass);
        buttonLayout->addWidget(m_settingsButton, 0, 2, 2, 1, Qt::AlignTop);

        connect(m_settingsButton, SIGNAL(clicked()), this, SLOT(onExtruderSettingsButtonClicked()));
        connect(m_materialButton, SIGNAL(clicked()), this, SLOT(onMaterialsButtonClicked()));
        connect(m_pidTuneButton, SIGNAL(clicked()), this, SLOT(onPidButtonClicked()));
        connect(m_preheatButton, SIGNAL(clicked()), this, SLOT(onPreheatButtonClicked()));
        connect(m_setOffsetButton, SIGNAL(clicked()), this, SLOT(onOffsetButtonClicked()));
    }

    setUiClasses();
    setupIcons();
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
    connect(m_extruder, SIGNAL(currentTempChanged()), this, SLOT(onExtruderCurrentTempChanged()));
    connect(m_extruder, SIGNAL(extrusionFactorChanged()), this, SLOT(onExtruderExtrusionFactorChanged()));
    connect(m_extruder, SIGNAL(maxTempChanged()), this, SLOT(onExtruderMaxTempChanged()));
    connect(m_extruder, SIGNAL(minTempChanged()), this, SLOT(onExtruderMinTempChanged()));
    connect(m_extruder, SIGNAL(pressureAdvanceChanged()), this, SLOT(onExtruderPressureAdvanceChanged()));
    connect(m_extruder, SIGNAL(smoothTimeChanged()), this, SLOT(onExtruderSmoothTimeChanged()));
    connect(m_extruder, SIGNAL(targetTempChanged()), this, SLOT(onExtruderTargetTempChanged()));
    connect(m_extruder, SIGNAL(powerChanged()), this, SLOT(onExtruderPowerChanged()));

    connect(m_extruder, SIGNAL(fanChanged()), this, SLOT(onExtruderFanChanged()));

    if(m_extruder->fan())
        connect(m_extruder->fan(), SIGNAL(speedChanged()), this, SLOT(onExtruderFanSpeedChanged()));

    connect(m_extruder, SIGNAL(pidCalibrating()), this, SLOT(showThrobber()));
    connect(m_extruder, SIGNAL(pidCalibratingFinished()), this, SLOT(hideThrobber()));

    updateUiValues();
}

void ExtruderWidget::setUiClasses()
{
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "Widget"));
    ui->statsWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" << "SubWidget"));
    ui->graphWidget->setProperty("class", QStringList { "Widget", "PrinterWidget" });
    ui->fanWidget->setProperty("class", QStringList { "Widget", "PrinterWidget" });
    ui->powerWidget->setProperty("class", QStringList { "Widget", "PrinterWidget" });
    ui->targetTemperatureWidget->setProperty("class", QStringList { "Widget", "PrinterWidget" });
    ui->extrusionFactorWidget->setProperty("class", QStringList { "Widget", "PrinterWidget" });
    ui->pressureAdvanceWidget->setProperty("class", QStringList { "Widget", "PrinterWidget" });
    ui->smoothTimeWidget->setProperty("class", QStringList { "Widget", "PrinterWidget" });

    style()->polish(this);
}

void ExtruderWidget::setupIcons()
{
    QPixmap pixmap = Settings::getThemeIcon("temperature").pixmap(18,18);
    ui->targetTemperatureIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("extrusion-factor").pixmap(18,18);
    ui->extrusionFactorIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("pressure-advance").pixmap(18,18);
    ui->pressureAdvanceIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("smooth-time").pixmap(18,18);
    ui->smoothTimeIcon->setPixmap(pixmap);

    m_pidTuneButton->setIcon(Settings::getThemeIcon("sine"));

    m_materialButton->setIcon(
        Settings::getThemeIcon(
            "material-retract",
            QColor::fromString(Settings::get("theme/icon-color-alt").toString())
            )
        );

    m_preheatButton->setIcon(
        Settings::getThemeIcon(
            "preheat",
            QColor::fromString(Settings::get("theme/icon-color").toString())
            )
        );

    m_setOffsetButton->setIcon(
        Settings::getThemeIcon(
            "material-extrude",
            QColor::fromString(Settings::get("theme/icon-color-alt").toString())
            )
        );

    m_settingsButton->setIcon(
        Settings::getThemeIcon(
            "extruder-settings",
            QColor::fromString(Settings::get("theme/icon-color-alt1").toString())
            )
        );

    m_extruderFanProgressBar->setIcon(
        Settings::getThemeIcon(
            "fan",
            QColor(Settings::get("theme/icon-color-alt").toString())
            )
        );

    m_powerProgressBar->setIcon(
        Settings::getThemeIcon(
            "power-device",
            QColor(Settings::get("theme/icon-color-alt").toString())
            )
        );

    m_temperatureProgressBar->setIcon(
        Settings::getThemeIcon(
            "temperature",
            QColor(Settings::get("theme/icon-color").toString())
            )
        );

    style()->polish(this);
}

void ExtruderWidget::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setupIcons();

    QFrame::changeEvent(event);
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
    if(!m_updating)
    {
        ui->resetButton->setEnabled(true);
        ui->applyButton->setEnabled(true);

        m_extrusionFactorEdited = true;

        updateSettingsButtons();
    }
}

void ExtruderWidget::on_targetTempSpinBox_valueChanged(double arg1)
{
    if(!m_updating)
    {
        ui->resetButton->setEnabled(true);
        ui->applyButton->setEnabled(true);

        m_targetTempEdited = true;

        updateSettingsButtons();
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

    //check for changes in extrusion factor
    if(m_extruder->extrusionFactor() != ui->extrusionFactorSpinBox->value())
        m_extruder->setExtrusionFactor(ui->extrusionFactorSpinBox->value());

    m_targetTempEdited = false;
    m_smoothTimeEdited = false;
    m_pressureAdvanceEdited = false;
    m_extrusionFactorEdited = false;

    //updateUiValues();
}


void ExtruderWidget::on_resetButton_clicked()
{
    ui->resetButton->setEnabled(false);
    ui->applyButton->setEnabled(false);

    m_targetTempEdited = false;
    m_smoothTimeEdited = false;
    m_pressureAdvanceEdited = false;
    m_extrusionFactorEdited = false;

    updateUiValues();
}


void ExtruderWidget::on_extrudeButton_clicked()
{
    // qreal amount = ui->materialLengthSpinBox->value();
    // qreal rate = ui->materialFeedRateSpinBox->value();

    // m_extruder->extrude(amount, rate);
}


void ExtruderWidget::on_retractButton_clicked()
{
    // qreal amount = ui->materialLengthSpinBox->value();
    // qreal rate = ui->materialFeedRateSpinBox->value();

    // m_extruder->extrude(amount * -1, rate);
}

void ExtruderWidget::onExtruderCanExtrudeChanged()
{
    m_materialButton->setEnabled(m_extruder->canExtrude());
    m_setOffsetButton->setEnabled(m_extruder->canExtrude());
}

void ExtruderWidget::onExtruderCurrentTempChanged()
{
    m_temperatureProgressBar->setValue(m_extruder->currentTemp());
}

void ExtruderWidget::onExtruderTargetTempChanged()
{
    //set updating flag to prevent this from registering as a change event
    m_updating = true;

    //make sure it has not been or is currently being edited
    if(!ui->targetTempSpinBox->hasFocus() && !m_targetTempEdited)
        ui->targetTempSpinBox->setValue(m_extruder->targetTemp());

    //ui->dashboardExtruderTargetTempLabel->setText(QString::number(m_extruder->targetTemp()) + QString("°"));

    m_updating = false;
}

void ExtruderWidget::onExtruderMaxTempChanged()
{
    m_temperatureProgressBar->setMaximum(m_extruder->maxTemp());
}

void ExtruderWidget::onExtruderMinTempChanged()
{
    m_temperatureProgressBar->setMaximum(m_extruder->minTemp());
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

void ExtruderWidget::onExtruderExtrusionFactorChanged()
{
    //set updating flag to prevent this from registering as a change event
    m_updating = true;

    //make sure it has not been or is currently being edited
    if(!ui->extrusionFactorSpinBox->hasFocus() && !m_extrusionFactorEdited)
        ui->extrusionFactorSpinBox->setValue(m_extruder->extrusionFactor());

    m_updating = false;
}

void ExtruderWidget::onExtruderFanSpeedChanged()
{
    m_extruderFanProgressBar->setValue((m_extruder->fan()->speed() * 100));
}

void ExtruderWidget::onExtruderPowerChanged()
{
    m_powerProgressBar->setValue((m_extruder->power() * 100));
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

    m_extruderFanProgressBar->setValue((m_extruder->fan()->speed() * 100));

        m_powerProgressBar->setValue((m_extruder->power() * 100));

    //make sure it has not been or is currently being edited
    if(!ui->extrusionFactorSpinBox->hasFocus() && !m_extrusionFactorEdited)
        ui->extrusionFactorSpinBox->setValue(m_extruder->extrusionFactor());

    //make sure it has not been or is currently being edited
    if(!ui->targetTempSpinBox->hasFocus() && !m_targetTempEdited)
        ui->targetTempSpinBox->setValue(m_extruder->targetTemp());

    //ui->dashboardExtruderTargetTempLabel->setText(QString::number(m_extruder->targetTemp()) + QString("°"));
    m_temperatureProgressBar->setMaximum(m_extruder->maxTemp());
    m_temperatureProgressBar->setValue(m_extruder->currentTemp());

    //unset updating flag to resume change events
    m_updating = false;
}

void ExtruderWidget::updateSettingsButtons()
{
    bool changed = (
        (ui->targetTempSpinBox->value() != m_extruder->targetTemp()) ||
        (ui->extrusionFactorSpinBox->value() != m_extruder->extrusionFactor())
    );

    qDebug() << m_extruder->extrusionFactor() << m_extruder->targetTemp();

    ui->applyButton->setEnabled(changed);
    ui->resetButton->setEnabled(changed);
}


void ExtruderWidget::onExtruderSettingsButtonClicked()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    ExtruderInfoDialog *extruderDialog = new ExtruderInfoDialog(m_extruder, this);

    extruderDialog->setFixedSize(screenGeometry.width() * 0.75, screenGeometry.height() * 0.75);
    extruderDialog->exec();

    extruderDialog->deleteLater();
}


void ExtruderWidget::onMaterialsButtonClicked()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    ExtruderMaterialsDialog *materialDialog = new ExtruderMaterialsDialog(this);

    materialDialog->setMinimumWidth(screenGeometry.width() * 0.33);
    materialDialog->setMaterialDirection(ExtruderMaterialsDialog::MaterialRetract);

    if(materialDialog->exec() == Dialog::Accepted && m_extruder->canExtrude())
        m_extruder->retract(materialDialog->distance(), materialDialog->speed());

    materialDialog->deleteLater();
}

void ExtruderWidget::onPidButtonClicked()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    PidDialog *pidDialog = new PidDialog(this);

    pidDialog->setMinimumWidth(screenGeometry.width() * 0.33);

    if(pidDialog->exec() == Dialog::Accepted && m_extruder && pidDialog->target() > 0)
        m_extruder->calibratePid(pidDialog->target());

    delete pidDialog;
}

void ExtruderWidget::onPreheatButtonClicked()
{

}

//need to move this to the toolhead since you cant edit the extruder offset via command
void ExtruderWidget::onOffsetButtonClicked()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    ExtruderMaterialsDialog *materialDialog = new ExtruderMaterialsDialog(this);

    materialDialog->setMinimumWidth(screenGeometry.width() * 0.33);
    materialDialog->setMaterialDirection(ExtruderMaterialsDialog::MaterialExtrude);

    if(materialDialog->exec() == Dialog::Accepted && m_extruder->canExtrude())
        m_extruder->retract(materialDialog->distance(), materialDialog->speed());

    materialDialog->deleteLater();
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

        m_throbber = new QThrobber(m_throbberFrame);
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

