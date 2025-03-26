#include "printerbedwidget.h"
#include "ui_printerbedwidget.h"

#include "flo/settings.h"

PrinterBedWidget::PrinterBedWidget(QKlipperPrintBed *printerBed, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PrinterBedWidget)
{
    ui->setupUi(this);

    setPrinterBed(printerBed);

    ui->temperatureGauge->setMaximum(150);
    ui->temperatureGauge->setIconSize(QSize(36,36));
    ui->temperatureGauge->setFixedSize(150,150);

    ui->healthGauge->setFontSize(9);
    ui->healthGauge->setIconSize(QSize(16,16));

    ui->powerGauge->setFontSize(9);
    ui->powerGauge->setIconSize(QSize(16,16));

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget"));
    ui->toolsFrame->setProperty("class", QStringList { "Widget" , "PrinterWidget" });

    QStringList buttonClass { "Button", "PrinterActionButton" };

    ui->pidButton->setIconSize(QSize(36,36));
    ui->pidButton->setText("PID Tune");

    ui->meshViewerButton->setIconSize(QSize(36,36));
    ui->meshViewerButton->setText("Mesh Viewer");

    ui->calibrateScrewsButton->setIconSize(QSize(36,36));
    ui->calibrateScrewsButton->setText("Bed Screws");

    ui->calibrateMeshButton->setIconSize(QSize(36,36));
    ui->calibrateMeshButton->setText("Scan Mesh");

    connect(ui->calibrateMeshButton, SIGNAL(clicked()), this, SLOT(onCalibrateBedMeshButtonClicked()));
    connect(ui->calibrateScrewsButton, SIGNAL(clicked()), this, SLOT(onCalibrateScrewsButtonClicked()));
    connect(ui->meshViewerButton, SIGNAL(clicked()), this, SLOT(onViewBedMeshButtonClicked()));
    connect(ui->pidButton, SIGNAL(clicked()), this, SLOT(onPidTuneButtonClicked()));

    setupIcons();

    m_bedMeshData = new BedMeshData(printerBed, this);
    onBedMeshDataChanged();
    connect(m_bedMeshData, SIGNAL(dataChanged()), this, SLOT(onBedMeshDataChanged()));

    ui->targetTemperatureSpinBox->setInputMethodHints(inputMethodHints() | Qt::InputMethodHint::ImhDigitsOnly);

    onToolheadHomedChanged();

    QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_printerBed->parent());

    if(printer)
        connect(printer->toolhead(), SIGNAL(isHomedChanged()), this, SLOT(onToolheadHomedChanged()));

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
    ui->temperatureContentsWidget->layout()->addWidget(m_temperatureGraph);

    ui->temperatureCard->setTitle("Thermals");
    ui->temperatureCard->setCentralWidget(ui->temperatureContentsWidget);

    ui->settingsCard->setTitle("Settings");
    ui->settingsCard->setCentralWidget(ui->settingsContentsWidget);

    ui->statusCard->setTitle("Status");
    ui->statusCard->setCentralWidget(ui->statusContentsWidget);

    ui->adjustmentScrewFrame->setPrinterBed(printerBed);
    ui->meshHealthFrame->setMeshData(m_bedMeshData);
}

PrinterBedWidget::~PrinterBedWidget()
{
    // ui->temperatureGauge->deleteLater();
    // m_adjustmentScrewFrame->deleteLater();
    // m_bedMeshFrame->deleteLater();
    delete ui;
}

void PrinterBedWidget::onPrintbedCurrentTempChanged()
{
    ui->temperatureGauge->setValue(m_printerBed->temperature());

    QDateTime currentTime = QDateTime::currentDateTime();
    currentTime = currentTime.addSecs(currentTime.offsetFromUtc());

    qreal timeNow = QDateTime::currentDateTime().addSecs(currentTime.offsetFromUtc()).addSecs(-30).toSecsSinceEpoch();
    qreal timeDiff = m_temperatureGraph->dateMinimum().toSecsSinceEpoch() - timeNow;

    if(timeDiff <= 0)
        m_temperatureGraph->setDateMinimum(QDateTime::currentDateTime().addSecs(-30).addSecs(currentTime.offsetFromUtc()));

    m_temperatureGraph->data()->append(
        "bed",
        QPointF(currentTime.toMSecsSinceEpoch(), m_printerBed->temperature())
    );
}

void PrinterBedWidget::onPrintbedTargetTempChanged()
{

    if(!m_targetTemperatureEdited)
        ui->targetTemperatureSpinBox->setValue(m_printerBed->targetTemperature());
}

void PrinterBedWidget::onPrintbedPowerChanged()
{
    ui->powerGauge->setValue((m_printerBed->power() * 100));
}

void PrinterBedWidget::onToolheadHomedChanged()
{
    QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_printerBed->parent());

    if(!printer) //invalid cast
        return;

    ui->calibrateMeshButton->setEnabled(printer->toolhead()->isHomed());
    ui->calibrateScrewsButton->setEnabled(printer->toolhead()->isHomed());
    //m_homeButton->setEnabled(!printer->toolhead()->isHomed());
}

void PrinterBedWidget::showThrobber()
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

void PrinterBedWidget::hideThrobber()
{
    if(m_throbberFrame)
    {
        m_throbber->stop();
        m_throbberFrame->hide();

        delete m_throbberFrame;
        m_throbberFrame = nullptr;
    }
}

void PrinterBedWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

QKlipperPrintBed *PrinterBedWidget::printerBed() const
{
    return m_printerBed;
}

void PrinterBedWidget::setPrinterBed(QKlipperPrintBed *printerBed)
{
    if(m_printerBed)
    {
        disconnect(m_printerBed, SIGNAL(temperatureChanged()), this, SLOT(onPrintbedCurrentTempChanged()));
        disconnect(m_printerBed, SIGNAL(targetTemperatureChanged()), this, SLOT(onPrintbedTargetTempChanged()));
        disconnect(m_printerBed, SIGNAL(powerChanged()), this, SLOT(onPrintbedPowerChanged()));
        disconnect(m_printerBed, SIGNAL(bedMeshCalibrating()), this, SLOT(showThrobber()));
        disconnect(m_printerBed, SIGNAL(adjustmentScrewsCalibrating()), this, SLOT(showThrobber()));
        disconnect(m_printerBed, SIGNAL(bedMeshCalibratingFinished()), this, SLOT(hideThrobber()));
        disconnect(m_printerBed, SIGNAL(adjustmentScrewsCalibratingFinished()), this, SLOT(hideThrobber()));
    }

    m_printerBed = printerBed;

    connect(m_printerBed, SIGNAL(temperatureChanged()), this, SLOT(onPrintbedCurrentTempChanged()));
    connect(m_printerBed, SIGNAL(targetTemperatureChanged()), this, SLOT(onPrintbedTargetTempChanged()));
    connect(m_printerBed, SIGNAL(powerChanged()), this, SLOT(onPrintbedPowerChanged()));
    connect(m_printerBed, SIGNAL(bedMeshCalibrating()), this, SLOT(showThrobber()));
    connect(m_printerBed, SIGNAL(adjustmentScrewsCalibrating()), this, SLOT(showThrobber()));
    connect(m_printerBed, SIGNAL(pidCalibrating()), this, SLOT(showThrobber()));
    connect(m_printerBed, SIGNAL(bedMeshCalibratingFinished()), this, SLOT(hideThrobber()));
    connect(m_printerBed, SIGNAL(adjustmentScrewsCalibratingFinished()), this, SLOT(hideThrobber()));
    connect(m_printerBed, SIGNAL(pidCalibratingFinished()), this, SLOT(hideThrobber()));
}

void PrinterBedWidget::setPrintActionsEnabled(bool enabled)
{
    Q_UNUSED(enabled)
}

void PrinterBedWidget::setupIcons()
{
    QPixmap pixmap = Settings::getThemeIcon("settings").pixmap(18,18);

    pixmap = Settings::getThemeIcon("temperature").pixmap(18,18);
    ui->targetTemperatureeratureIconLabel->setPixmap(pixmap);

    ui->pidButton->setIcon(
        Settings::getThemeIcon(
            "sine",
            QColor(Settings::get("theme/accent-color").toString())
            )
        );

    ui->calibrateMeshButton->setIcon(
        Settings::getThemeIcon(
            "mesh-calibrate",
            QColor(Settings::get("theme/accent-color4").toString())
            )
        );

    ui->calibrateScrewsButton->setIcon(
        Settings::getThemeIcon(
            "adjustment-screws-calibrate",
            QColor(Settings::get("theme/accent-color3").toString())
            )
        );

    ui->meshViewerButton->setIcon(
        Settings::getThemeIcon(
            "mesh-viewer",
            QColor(Settings::get("theme/accent-color2").toString())
            )
        );

    ui->temperatureGauge->setIcon(
        Settings::getThemeIcon(
            "temperature",
            QColor(Settings::get("theme/accent-color").toString())
            )
        );

    ui->powerGauge->setIcon(
        Settings::getThemeIcon(
            "power-device",
            QColor(Settings::get("theme/accent-color2").toString())
            )
        );

    ui->healthGauge->setIcon(
        Settings::getThemeIcon(
            "health",
            QColor(Settings::get("theme/accent-color3").toString())
            )
        );

    ui->settingsCard->setIcon(
        Settings::getThemeIcon(
            "settings"
            )
        );

    ui->temperatureCard->setIcon(
        Settings::getThemeIcon(
            "temperature"
            )
        );

    ui->statusCard->setIcon(
        Settings::getThemeIcon(
            "bed"
            )
        );
}

void PrinterBedWidget::setStyleSheet(const QString &styleSheet)
{
    setupIcons();

    QFrame::setStyleSheet(styleSheet);
}

QIconButton *PrinterBedWidget::bedMeshViewerButton()
{
    return ui->meshViewerButton;
}

void PrinterBedWidget::on_applyButton_clicked()
{
    m_printerBed->setTargetTemperature(ui->targetTemperatureSpinBox->value());
    m_targetTemperatureEdited = false;
}

void PrinterBedWidget::on_resetButton_clicked()
{
    ui->targetTemperatureSpinBox->setValue(m_printerBed->targetTemperature());
    m_targetTemperatureEdited = false;
}


void PrinterBedWidget::on_targetTemperatureSpinBox_valueChanged(double arg1)
{
    bool changed = (arg1 != m_printerBed->targetTemperature());

    m_targetTemperatureEdited = changed;
    ui->resetButton->setEnabled(changed);
    ui->applyButton->setEnabled(changed);
}


void PrinterBedWidget::onViewBedMeshButtonClicked()
{

}


void PrinterBedWidget::onCalibrateBedMeshButtonClicked()
{
    if(m_printerBed)
        m_printerBed->calibrateBedMesh();
}

void PrinterBedWidget::onCalibrateScrewsButtonClicked()
{
    if(m_printerBed)
        m_printerBed->calibrateAdjustmentScrews();
}

void PrinterBedWidget::onPidTuneButtonClicked()
{
    m_pidDialog = new PidDialog(this);
    emit dialogRequested(m_pidDialog);

    connect(m_pidDialog, SIGNAL(finished(int)), this, SLOT(onPidDialogFinished(int)));
}

void PrinterBedWidget::onBedMeshDataChanged()
{
    qreal variance = m_bedMeshData->maximum() - m_bedMeshData->minimum();
    qreal health = (1 - (variance / 0.3000)) * 100;

    if(variance == 0 && m_bedMeshData->maximum() == 0 && m_bedMeshData->minimum() == 0)
        health = 0; //no result yet

    if(ui->healthGauge)
        ui->healthGauge->setValue(health);
}

void PrinterBedWidget::onPidDialogFinished(int returnCode)
{
    qreal temp = m_pidDialog->target();
    delete m_pidDialog;
    m_pidDialog = nullptr;

    if(returnCode == QDialog::Accepted)
        m_printerBed->calibratePid(temp);
}
