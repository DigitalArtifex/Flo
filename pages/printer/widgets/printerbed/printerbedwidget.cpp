#include "printerbedwidget.h"
#include "ui_printerbedwidget.h"

#include "flo/settings.h"

PrinterBedWidget::PrinterBedWidget(QKlipperPrintBed *printerBed, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PrinterBedWidget)
{
    ui->setupUi(this);

    setPrinterBed(printerBed);

    m_bedTemperatureBar = new QGaugeWidget(this, QGaugeWidget::Temperature);
    m_bedTemperatureBar->setMaximum(150);
    m_bedTemperatureBar->setIconSize(QSize(36,36));
    m_bedTemperatureBar->setFixedSize(150,150);
    ui->bedLayout->addWidget(m_bedTemperatureBar);

    m_bedHealthProgressBar = new QGaugeWidget(ui->healthWidget, QGaugeWidget::Percent);
    m_bedHealthProgressBar->setFontSize(9);
    m_bedHealthProgressBar->setIconSize(QSize(16,16));
    ui->healthWidget->layout()->addWidget(m_bedHealthProgressBar);

    m_bedPowerProgressBar = new QGaugeWidget(ui->powerWidget, QGaugeWidget::Percent);
    m_bedPowerProgressBar->setFontSize(9);
    m_bedPowerProgressBar->setIconSize(QSize(16,16));
    ui->powerLayout->addWidget(m_bedPowerProgressBar);

    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget"));
    //ui->bedInfoWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget"));
    ui->powerWidget->setProperty("class", QStringList { "Widget" , "PrinterWidget" });
    ui->infoWidget->setProperty("class", QStringList { "Widget" , "PrinterWidget" });
    ui->targetTempWidget->setProperty("class", QStringList { "Widget" , "PrinterWidget" });
    ui->healthWidget->setProperty("class", QStringList { "Widget" , "PrinterWidget" });

    QGridLayout *buttonLayout = qobject_cast<QGridLayout*>(ui->buttonWidget->layout());

    if(buttonLayout)
    {
        QStringList buttonClass { "Button", "PrinterActionButton" };

        m_pidButton = new QIconButton(this);
        m_pidButton->setIcon(Settings::getThemeIcon("sine"));
        m_pidButton->setIconSize(QSize(36,36));
        m_pidButton->setFixedSize(QSize(100,100));
        m_pidButton->setText("PID Tune");
        m_pidButton->setTextAlignment(Qt::AlignBottom | Qt::AlignHCenter);
        m_pidButton->setIconAlignment(Qt::AlignCenter);
        m_pidButton->setProperty("class", buttonClass);
        m_pidButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        buttonLayout->addWidget(m_pidButton, 0, 0, 1, 1, Qt::AlignTop);

        m_meshViewerButton = new QIconButton(this);
        m_meshViewerButton->setIcon(Settings::getThemeIcon("mesh-viewer"));
        m_meshViewerButton->setIconSize(QSize(36,36));
        m_meshViewerButton->setFixedSize(QSize(100,100));
        m_meshViewerButton->setText("Mesh Viewer");
        m_meshViewerButton->setTextAlignment(Qt::AlignBottom | Qt::AlignHCenter);
        m_meshViewerButton->setIconAlignment(Qt::AlignCenter);
        m_meshViewerButton->setProperty("class", buttonClass);
        m_meshViewerButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        buttonLayout->addWidget(m_meshViewerButton, 0, 1, 1, 1, Qt::AlignTop);

        m_calibrateScrewsButton = new QIconButton(this);
        m_calibrateScrewsButton->setIcon(Settings::getThemeIcon("adjustment-screws-calibrate"));
        m_calibrateScrewsButton->setIconSize(QSize(36,36));
        m_calibrateScrewsButton->setFixedSize(QSize(100,100));
        m_calibrateScrewsButton->setText("Bed Screws");
        m_calibrateScrewsButton->setTextAlignment(Qt::AlignBottom | Qt::AlignHCenter);
        m_calibrateScrewsButton->setIconAlignment(Qt::AlignCenter);
        m_calibrateScrewsButton->setProperty("class", buttonClass);
        m_calibrateScrewsButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        buttonLayout->addWidget(m_calibrateScrewsButton, 1, 0, 1, 1, Qt::AlignTop);

        m_calibrateMeshButton = new QIconButton(this);
        m_calibrateMeshButton->setIcon(Settings::getThemeIcon("mesh-calibrate"));
        m_calibrateMeshButton->setIconSize(QSize(36,36));
        m_calibrateMeshButton->setFixedSize(QSize(100,100));
        m_calibrateMeshButton->setText("Scan Mesh");
        m_calibrateMeshButton->setTextAlignment(Qt::AlignBottom | Qt::AlignHCenter);
        m_calibrateMeshButton->setIconAlignment(Qt::AlignCenter);
        m_calibrateMeshButton->setProperty("class", buttonClass);
        m_calibrateMeshButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        buttonLayout->addWidget(m_calibrateMeshButton, 1, 1, 1, 1, Qt::AlignTop);

        m_bedInfoButton = new QIconButton(this);
        m_bedInfoButton->setIcon(Settings::getThemeIcon("mesh-info"));
        m_bedInfoButton->setIconSize(QSize(36,36));
        m_bedInfoButton->setFixedSize(QSize(100,206));
        m_bedInfoButton->setText("Information");
        m_bedInfoButton->setTextAlignment(Qt::AlignBottom | Qt::AlignHCenter);
        m_bedInfoButton->setIconAlignment(Qt::AlignCenter);
        m_bedInfoButton->setProperty("class", buttonClass);
        buttonLayout->addWidget(m_bedInfoButton, 0, 2, 2, 1, Qt::AlignTop);
        buttonLayout->addItem(new QSpacerItem(QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 0, 1, 1);

        connect(m_calibrateMeshButton, SIGNAL(clicked()), this, SLOT(onCalibrateBedMeshButtonClicked()));
        connect(m_calibrateScrewsButton, SIGNAL(clicked()), this, SLOT(onCalibrateScrewsButtonClicked()));
        connect(m_meshViewerButton, SIGNAL(clicked()), this, SLOT(onViewBedMeshButtonClicked()));
        connect(m_bedInfoButton, SIGNAL(clicked()), this, SLOT(onSettingsButtonClicked()));
        connect(m_pidButton, SIGNAL(clicked()), this, SLOT(onPidTuneButtonClicked()));
    }

    setupIcons();

    m_bedMeshData = new BedMeshData(printerBed, this);
    onBedMeshDataChanged();
    connect(m_bedMeshData, SIGNAL(dataChanged()), this, SLOT(onBedMeshDataChanged()));

    ui->targetTempSpinBox->setInputMethodHints(inputMethodHints() | Qt::InputMethodHint::ImhDigitsOnly);

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
    ui->infoWidget->layout()->addWidget(m_temperatureGraph);
}

PrinterBedWidget::~PrinterBedWidget()
{
    // m_bedTemperatureBar->deleteLater();
    // m_adjustmentScrewFrame->deleteLater();
    // m_bedMeshFrame->deleteLater();
    delete ui;
}

void PrinterBedWidget::onPrintbedCurrentTempChanged()
{
    m_bedTemperatureBar->setValue(m_printerBed->currentTemp());

    QDateTime currentTime = QDateTime::currentDateTime();
    currentTime = currentTime.addSecs(currentTime.offsetFromUtc());

    qreal timeNow = QDateTime::currentDateTime().addSecs(currentTime.offsetFromUtc()).addSecs(-30).toSecsSinceEpoch();
    qreal timeDiff = m_temperatureGraph->dateMinimum().toSecsSinceEpoch() - timeNow;

    if(timeDiff <= 0)
        m_temperatureGraph->setDateMinimum(QDateTime::currentDateTime().addSecs(-30).addSecs(currentTime.offsetFromUtc()));

    m_temperatureGraph->data()->append(
        "bed",
        QPointF(currentTime.toMSecsSinceEpoch(), m_printerBed->currentTemp())
    );
}

void PrinterBedWidget::onPrintbedTargetTempChanged()
{

    if(!m_targetTempEdited)
        ui->targetTempSpinBox->setValue(m_printerBed->targetTemp());
}

void PrinterBedWidget::onPrintbedPowerChanged()
{
    m_bedPowerProgressBar->setValue((m_printerBed->power() * 100));
}

void PrinterBedWidget::onToolheadHomedChanged()
{
    QKlipperPrinter *printer = qobject_cast<QKlipperPrinter*>(m_printerBed->parent());

    if(!printer) //invalid cast
        return;

    m_calibrateMeshButton->setEnabled(printer->toolhead()->isHomed());
    m_calibrateScrewsButton->setEnabled(printer->toolhead()->isHomed());
    //m_homeButton->setEnabled(!printer->toolhead()->isHomed());
}

void PrinterBedWidget::showThrobber()
{
    if(!m_throbberFrame)
    {
        m_throbberFrame = new QFrame(ui->contentWidget);
        QVBoxLayout *layout = new QVBoxLayout(m_throbberFrame);
        m_throbberFrame->setFixedSize(ui->contentWidget->width(), ui->contentWidget->height());
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
        disconnect(m_printerBed, SIGNAL(currentTempChanged()), this, SLOT(onPrintbedCurrentTempChanged()));
        disconnect(m_printerBed, SIGNAL(targetTempChanged()), this, SLOT(onPrintbedTargetTempChanged()));
        disconnect(m_printerBed, SIGNAL(powerChanged()), this, SLOT(onPrintbedPowerChanged()));
        disconnect(m_printerBed, SIGNAL(bedMeshCalibrating()), this, SLOT(showThrobber()));
        disconnect(m_printerBed, SIGNAL(adjustmentScrewsCalibrating()), this, SLOT(showThrobber()));
        disconnect(m_printerBed, SIGNAL(bedMeshCalibratingFinished()), this, SLOT(hideThrobber()));
        disconnect(m_printerBed, SIGNAL(adjustmentScrewsCalibratingFinished()), this, SLOT(hideThrobber()));
    }

    m_printerBed = printerBed;

    connect(m_printerBed, SIGNAL(currentTempChanged()), this, SLOT(onPrintbedCurrentTempChanged()));
    connect(m_printerBed, SIGNAL(targetTempChanged()), this, SLOT(onPrintbedTargetTempChanged()));
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
    ui->targetTemperatureIconLabel->setPixmap(pixmap);

    m_pidButton->setIcon(
        Settings::getThemeIcon(
            "sine",
            QColor(Settings::get("theme/accent-color").toString())
            )
        );

    m_calibrateMeshButton->setIcon(
        Settings::getThemeIcon(
            "mesh-calibrate",
            QColor(Settings::get("theme/accent-color4").toString())
            )
        );

    m_calibrateScrewsButton->setIcon(
        Settings::getThemeIcon(
            "adjustment-screws-calibrate",
            QColor(Settings::get("theme/accent-color3").toString())
            )
        );

    m_meshViewerButton->setIcon(
        Settings::getThemeIcon(
            "mesh-viewer",
            QColor(Settings::get("theme/accent-color2").toString())
            )
        );

    m_bedInfoButton->setIcon(
        Settings::getThemeIcon(
            "mesh-info",
            QColor(Settings::get("theme/accent-color5").toString())
            )
        );

    m_bedTemperatureBar->setIcon(
        Settings::getThemeIcon(
            "temperature",
            QColor(Settings::get("theme/accent-color").toString())
            )
        );

    // QPen bedTempProgressPen;
    // bedTempProgressPen.setColor(QColor(Settings::get("theme/accent-color").toString()));
    // bedTempProgressPen.setWidth(8);
    // m_bedTemperatureBar->setProgressBarFillPen(bedTempProgressPen);

    m_bedPowerProgressBar->setIcon(
        Settings::getThemeIcon(
            "power-device",
            QColor(Settings::get("theme/accent-color2").toString())
            )
        );

    m_bedHealthProgressBar->setIcon(
        Settings::getThemeIcon(
            "health",
            QColor(Settings::get("theme/accent-color3").toString())
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
    return m_meshViewerButton;
}

void PrinterBedWidget::on_applyButton_clicked()
{
    m_printerBed->setTargetTemp(ui->targetTempSpinBox->value());
    m_targetTempEdited = false;
}

void PrinterBedWidget::on_resetButton_clicked()
{
    ui->targetTempSpinBox->setValue(m_printerBed->targetTemp());
    m_targetTempEdited = false;
}


void PrinterBedWidget::on_targetTempSpinBox_valueChanged(double arg1)
{
    bool changed = (arg1 != m_printerBed->targetTemp());

    m_targetTempEdited = changed;
    ui->resetButton->setEnabled(changed);
    ui->applyButton->setEnabled(changed);
}


void PrinterBedWidget::onSettingsButtonClicked()
{
    m_settingsDialog = new PrinterBedInfoDialog(m_printerBed, this);
    emit dialogRequested(m_settingsDialog);

    connect(m_settingsDialog, SIGNAL(finished(int)), this, SLOT(onSettingsDialogFinished(int)));
}


void PrinterBedWidget::onViewBedMeshButtonClicked()
{
    // QScreen *screen = QGuiApplication::primaryScreen();
    // QRect screenGeometry = screen->geometry();
    // BedMeshWidget *bedMeshWidget = new BedMeshWidget(m_printerBed, this);

    // bedMeshWidget->setFixedSize(screenGeometry.width() * 0.75, screenGeometry.height() * 0.75);
    // bedMeshWidget->exec();

    // delete bedMeshWidget;
}


void PrinterBedWidget::onCalibrateBedMeshButtonClicked()
{
    if(m_printerBed)
    {
        m_printerBed->calibrateBedMesh();
    }
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

    if(m_bedHealthProgressBar)
        m_bedHealthProgressBar->setValue(health);
}

void PrinterBedWidget::onPidDialogFinished(int returnCode)
{
    qreal temp = m_pidDialog->target();
    delete m_pidDialog;
    m_pidDialog = nullptr;

    if(returnCode == QDialog::Accepted)
        m_printerBed->calibratePid(temp);
}

void PrinterBedWidget::onSettingsDialogFinished(int returnCode)
{
    delete m_settingsDialog;
    m_settingsDialog = nullptr;
}
