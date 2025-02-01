#include "printerpage.h"
#include "ui_printerpage.h"
#include "flo/settings.h"
PrinterPage::PrinterPage(QKlipperInstance *instance, QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::PrinterPage)
{
    ui->setupUi(this);
    m_instance = instance;

    m_toolheadControlFrame = new ToolHeadControlFrame(instance->printer()->toolhead(), ui->controlContents);
    ui->controlContents->layout()->addWidget(m_toolheadControlFrame);

    ui->chamberTemperatureGauge->setFixedSize(150,150);
    m_chamberTemperatureWidget = new PrinterTemperatureWidget(instance, ui->chamberTemperatureFrame);
    ui->chamberTemperatureFrame->layout()->addWidget(m_chamberTemperatureWidget);

    m_printProgressBar = new QGaugeWidget(this);
    ui->printProgressLayout->addWidget(m_printProgressBar);

    m_printerFanWidget = new PrinterFanWidget(instance->printer(), ui->fanFrame);
    ui->fanFrameLayout->addWidget(m_printerFanWidget);

    ui->chamberWidget->setHidden(false);

    m_temperatureWidget = new PrinterTemperatureWidget(m_instance, ui->temperatureWidget);
    ui->temperatureLayout->addWidget(m_temperatureWidget);

    m_terminal = new PrinterTerminal(instance, this);
    m_terminal->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_fileBrowser = new FileBrowser(instance, QString("gcodes"));
    m_fileBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_printerSettingsPage = new PrinterSettingsPage(instance, ui->settingsWidget);
    ui->settingsWidget->layout()->addWidget(m_printerSettingsPage);

    m_printerOfflineScreen = new PrinterOfflineScreen(instance, this);
    m_printerOfflineScreen->setGeometry(QRect(0,0,width(),height()));
    m_printerOfflineScreen->raise();

    QRegularExpression distanceExpression("\\d+\\.\\d+\\s*", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionValidator *distanceValidator = new QRegularExpressionValidator(distanceExpression);
    ui->posIncrementSelect->setValidator(distanceValidator);

    setPrinter(instance->printer());

    m_printerBedWidget = new PrinterBedWidget(m_printer->bed(), ui->toolBox);
    ui->toolBox->insertItem(0, m_printerBedWidget, Settings::getThemeIcon("mesh"), "Bed");

    m_webcamWidget = new PrinterWebcamWidget(instance, ui->webcamContentWidget);
    ui->webcamContentWidget->layout()->addWidget(m_webcamWidget);

    connect(m_instance, SIGNAL(error(QKlipperInstance*,QKlipperError&)), this, SLOT(onInstanceError(QKlipperInstance*,QKlipperError&)));
    connect(m_instance->printer(), SIGNAL(statusChanged()), this, SLOT(onPrinterStatusChanged()));
    connect(m_instance->system(), SIGNAL(stateChanged()), this, SLOT(onSystemStateChanged()));

    m_statusOverlayFrame = new QFrame(ui->printerStatusContents);
    m_statusLabel = new QLabel(m_statusOverlayFrame);

    m_statusOverlayFrame->setLayout(new QGridLayout(m_statusOverlayFrame));
    m_statusOverlayFrame->layout()->addWidget(m_statusLabel);
    m_statusOverlayFrame->lower();
    m_statusOverlayFrame->setVisible(false);

    m_powerDeviceView = new PowerDeviceView(m_instance->system(), ui->toolBox);
    m_powerDeviceView->setCardFlags(CardWidget::NoTitleBar);
    ui->toolBox->addItem(m_powerDeviceView, Settings::getThemeIcon("power-device"), "Power Devices");

    m_ledDeviceView = new LedStripView(m_instance->system(), ui->toolBox);
    m_ledDeviceView->setCardFlags(CardWidget::NoTitleBar);
    ui->toolBox->addItem(m_ledDeviceView, Settings::getThemeIcon("led"), "LED Strips");

    m_sensorDeviceView = new SensorView(m_instance->system(), ui->toolBox);
    m_sensorDeviceView->setCardFlags(CardWidget::NoTitleBar);
    ui->toolBox->addItem(m_sensorDeviceView, Settings::getThemeIcon("sensors"), "Sensors");
    ui->toolBox->setCurrentWidget(m_printerBedWidget);

    m_bedMeshWidget = new BedMeshWidget(instance->printer()->bed(),ui->stackedWidget);
    ui->stackedWidget->addWidget(m_bedMeshWidget);

    m_printingPage = new PrintingPage(instance->printer(), ui->stackedWidget);
    ui->stackedWidget->addWidget(m_printingPage);

    connect(m_printerBedWidget->bedMeshViewerButton(), SIGNAL(clicked()), this, SLOT(onBedMeshButtonClicked()));

    ui->stackedWidget->setCurrentIndex(0);

    setupUiClasses();
    setStyleSheet(Settings::currentTheme());

    setupAnimations();

    ui->actionBar->setFixedHeight(0);

    m_statusOverlayFrame->resize(ui->printerStatusContents->size());
    m_statusOverlayFrame->raise();
    m_statusOverlayFrame->setVisible(true);
}

PrinterPage::~PrinterPage()
{
    ui->chamberTemperatureGauge->deleteLater();
    m_fileBrowser->deleteLater();

    m_terminal->deleteLater();
    m_printerOfflineScreen->deleteLater();

    delete ui;
}

void PrinterPage::addExtruder(QKlipperExtruder *extruder, QString name)
{
    if(name == QString("Extruder") && m_extruderMap.count() >= 1)
        name = QString("Extruder #") + QString::number(m_extruderMap.count() + 1);

    int index = m_extruderMap.count();

    m_extruderMap[index] = new ExtruderWidget(extruder, ui->toolBox);
    m_extruderMap[index]->setExtruder(extruder);

    ui->toolBox->insertItem(0, m_extruderMap[index], name);
    ui->toolBox->setItemIcon(ui->toolBox->indexOf(ui->page), Settings::getThemeIcon("printer"));
    ui->toolBox->setItemIcon(ui->toolBox->indexOf(m_extruderMap[index]), Settings::getThemeIcon("extruder"));
}

void PrinterPage::setupIcons()
{
    QPixmap pixmap = Settings::getThemeIcon(QString("printer")).pixmap(28,28);
    ui->statusIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon(QString("location")).pixmap(18,18);
    ui->positionIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon(QString("control")).pixmap(18,18);
    ui->controlIconLabel->setPixmap(pixmap);

    ui->toolBox->setItemIcon(
        ui->toolBox->indexOf(ui->toolheadPage),
        Settings::getThemeIcon(QString("toolhead"))
        );

    ui->toolBox->setItemIcon(
        ui->toolBox->indexOf(ui->thermalsPage),
        Settings::getThemeIcon(QString("temperature"))
        );

    ui->toolBox->setItemIcon(
        ui->toolBox->indexOf(ui->chamberWidget),
        Settings::getThemeIcon(QString("printer"))
        );

    ui->toolBox->setItemIcon(
        ui->toolBox->indexOf(m_powerDeviceView),
        Settings::getThemeIcon(QString("power-device"))
        );

    ui->toolBox->setItemIcon(
        ui->toolBox->indexOf(m_ledDeviceView),
        Settings::getThemeIcon(QString("led"))
        );

    ui->toolBox->setItemIcon(
        ui->toolBox->indexOf(m_sensorDeviceView),
        Settings::getThemeIcon(QString("sensors"))
        );

    ui->chamberTemperatureGauge->setIcon(
        Settings::getThemeIcon(QString("temperature"))
        );

    ui->browserButton->setIcon(
        Settings::getThemeIcon(
            "browser",
            QColor::fromString(Settings::get("theme/icon-color").toString())
            )
        );

    ui->browserButton->setIconSize(QSize(50,50));

    ui->inputShaperButton->setIcon(
        Settings::getThemeIcon(
            "input-shaper",
            QColor::fromString(Settings::get("theme/icon-color-alt").toString())
            )
        );

    ui->inputShaperButton->setIconSize(QSize(50,50));

    ui->zOffsetWizardButton->setIcon(
        Settings::getThemeIcon(
            "zoffset",
            QColor::fromString(Settings::get("theme/icon-color-alt1").toString())
            )
        );

    ui->zOffsetWizardButton->setIconSize(QSize(50,50));

    ui->terminalButton->setIcon(Settings::getThemeIcon("console", QColor::fromString(Settings::get("theme/icon-color-alt1").toString())));
    ui->terminalButton->setIconSize(QSize(50,50));

    ui->gcodeButton->setIcon(
        Settings::getThemeIcon(
            "gcode",
            QColor::fromString(Settings::get("theme/icon-color-alt").toString())
            )
        );

    ui->gcodeButton->setIconSize(QSize(50,50));

    ui->settingsButton->setIcon(Settings::getThemeIcon("printer-settings", QColor::fromString(Settings::get("theme/icon-color-alt2").toString())));
    ui->settingsButton->setIconSize(QSize(50,50));

    pixmap = Settings::getThemeIcon(QString("webcam")).pixmap(28,28);
    ui->webcamIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon(QString("printer")).pixmap(28,28);
    ui->statusIconLabel->setPixmap(pixmap);

    m_temperatureWidget->setIcon(Settings::getThemeIcon("chart"));
    ui->chamberTemperatureIconLabel->setPixmap(Settings::getThemeIcon("temperature").pixmap(20,20));
    ui->goBackButton->setIcon(Settings::getThemeIcon(QString("up-directory")));
}

void PrinterPage::setupUiClasses()
{
    ui->actionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageActionBar"));
    ui->pageContents->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    m_bedMeshWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));

    ui->toolheadWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget"));
    ui->currentPositionFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" << "PrinterSubWidget"));
    ui->toolheadControlFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" << "PrinterSubWidget"));
    m_statusOverlayFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" << "PrinterSubWidget"));

    ui->printJobWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget"));
    ui->printProgressWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" << "PrinterSubWidget"));
    ui->temperatureWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget"));
    ui->webcamGroupBox->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget"));

    ui->positionTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidgetTitleBar"));
    ui->positionTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    ui->chamberWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget"));
    ui->chamberStatusWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" << "PrinterSubWidget"));

    ui->controlTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidgetTitleBar"));
    ui->controlTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    ui->printStatusTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));
    ui->printStatusTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    ui->webcamTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));
    ui->webcamTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    ui->chamberTemperatureSettingsFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget"));
    //ui->chamberTemperatureFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget"));
}

bool PrinterPage::animating() const
{
    return m_animating;
}

void PrinterPage::setAnimating(bool animating)
{
    m_animating = animating;
}

void PrinterPage::on_xPosDecreaseButton_clicked()
{
    QString valueString = ui->posIncrementSelect->currentText();
    valueString.remove(QString("mm"));

    qreal amount = valueString.toDouble();

    m_printer->toolhead()->moveX(amount * -1);
}

void PrinterPage::onOverviewButtonClicked()
{
    ui->stackedWidget->setCurrentWidget(ui->overviewWidget);
    // m_webcamWidget->show();
}

void PrinterPage::onSettingsButtonClicked()
{
    ui->stackedWidget->setCurrentWidget(ui->settingsWidget);
}

void PrinterPage::onBedMeshButtonClicked()
{
    ui->stackedWidget->setCurrentWidget(m_bedMeshWidget);
}

QKlipperPrinter *PrinterPage::printer() const
{
    return m_printer;
}

void PrinterPage::setPrinter(QKlipperPrinter *printer)
{
    if(m_printerBedWidget)
        m_printerBedWidget->setPrinterBed(printer->bed());

    if(m_printerFanWidget)
        m_printerFanWidget->setPrinter(printer);

    m_printer = printer;

    connect(m_printer, SIGNAL(statusChanged()), this, SLOT(onPrinterStatusChanged()));
    connect(m_printer, SIGNAL(statusMessageChanged()), this, SLOT(onPrinterStatusMessageChanged()));
    connect(m_printer, SIGNAL(printEndingChanged()), this, SLOT(onPrinterEndingTimeChanged()));
    connect(m_printer->toolhead(), SIGNAL(extruderMapChanged()), this, SLOT(onToolHeadExtrudersChanged()));
    connect(m_printer->toolhead(), SIGNAL(positionChanged()), this, SLOT(onToolheadPositionChanged()));
    connect(m_printer->toolhead(), SIGNAL(destinationChanged()), this, SLOT(onToolHeadDestinationChanged()));

    onToolHeadExtrudersChanged();
}

void PrinterPage::resizeEvent(QResizeEvent *event)
{
    QOpenGLWidget::resizeEvent(event);

    if(m_printerOfflineScreen)
        m_printerOfflineScreen->setGeometry(QRect(0,0,width(),height()));

    if(m_statusOverlayFrame)
        m_statusOverlayFrame->resize(ui->printerStatusContents->size());
}

void PrinterPage::setPrintActionsEnabled(bool enabled)
{
    ui->chamberWidget->setEnabled(enabled);
    ui->temperatureWidget->setEnabled(enabled);
    ui->toolheadWidget->setEnabled(enabled);
}

void PrinterPage::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setupIcons();

    QOpenGLWidget::changeEvent(event);
}

void PrinterPage::showEvent(QShowEvent *event)
{
    if(m_statusOverlayFrame)
        m_statusOverlayFrame->resize(ui->printerStatusContents->size());
}

void PrinterPage::setupAnimations()
{

}

void PrinterPage::on_homeToolheadButton_clicked()
{
    m_printer->toolhead()->home();
}

void PrinterPage::on_posIncrementSelect_currentTextChanged(const QString &arg1)
{
    QString number;

    if(arg1.contains(m_number_expression))
    {
        QRegularExpressionMatch match = m_number_expression.globalMatch(arg1).next();
        number = match.captured();
    }

    int pos = number.length();

    if(ui->posIncrementSelect->hasFocus())
    {
        ui->posIncrementSelect->setCurrentText(number + QString("mm"));
        ui->posIncrementSelect->lineEdit()->setCursorPosition(pos);
    }
    else
        ui->posIncrementSelect->setCurrentText(number + QString("mm"));

    bool ok = false;
    qreal increment = number.toDouble(&ok);

    if(ok)
        m_toolheadControlFrame->setIncrement(increment);
    else
        qDebug() << QString("Could not set toolhead increment: Invalid number format \"") + number + QString("\"");
}

void PrinterPage::on_xPosIncreaseButton_clicked()
{
    QString valueString = ui->posIncrementSelect->currentText();
    valueString.remove(QString("mm"));

    qreal amount = valueString.toDouble();

    switch(m_printer->status())
    {

    case QKlipperPrinter::Ready:
        qDebug() << "Moving toolhead";
        m_printer->toolhead()->moveX(amount);
        break;
    case QKlipperPrinter::Paused:
    case QKlipperPrinter::Cancelled:
    case QKlipperPrinter::Printing:
        qDebug() << "Cannot move toolhead during print operation";
        break;
    case QKlipperPrinter::Error:
    case QKlipperPrinter::Offline:
    case QKlipperPrinter::Connecting:
        qDebug() << "Cannot move toolhead. Printer offline.";
        break;
    };
}

void PrinterPage::on_yPosDecreaseButton_clicked()
{
    QString valueString = ui->posIncrementSelect->currentText();
    valueString.remove(QString("mm"));

    qreal amount = valueString.toDouble();

    switch(m_printer->status())
    {

    case QKlipperPrinter::Ready:
        qDebug() << "Moving toolhead";
        m_printer->toolhead()->moveY(amount * -1);
        break;
    case QKlipperPrinter::Paused:
    case QKlipperPrinter::Cancelled:
    case QKlipperPrinter::Printing:
        qDebug() << "Cannot move toolhead during print operation";
        break;
    case QKlipperPrinter::Error:
    case QKlipperPrinter::Offline:
    case QKlipperPrinter::Connecting:
        qDebug() << "Cannot move toolhead. Printer offline.";
        break;
    };
}

void PrinterPage::on_yPosIncreaseButton_clicked()
{
    QString valueString = ui->posIncrementSelect->currentText();
    valueString.remove(QString("mm"));

    qreal amount = valueString.toDouble();

    switch(m_printer->status())
    {

        case QKlipperPrinter::Ready:
            qDebug() << "Moving toolhead";
            m_printer->toolhead()->moveY(amount);
            break;
        case QKlipperPrinter::Paused:
        case QKlipperPrinter::Cancelled:
        case QKlipperPrinter::Printing:
            qDebug() << "Cannot move toolhead during print operation";
            break;
        case QKlipperPrinter::Error:
        case QKlipperPrinter::Offline:
        case QKlipperPrinter::Connecting:
            qDebug() << "Cannot move toolhead. Printer offline.";
            break;
    };
}

void PrinterPage::on_zPosDecreaseButton_clicked()
{
    QString valueString = ui->posIncrementSelect->currentText();
    valueString.remove(QString("mm"));

    qreal amount = valueString.toDouble();

    switch(m_printer->status())
    {

    case QKlipperPrinter::Ready:
        qDebug() << "Moving toolhead";
        m_printer->toolhead()->moveZ(amount * -1);
        break;
    case QKlipperPrinter::Paused:
    case QKlipperPrinter::Cancelled:
    case QKlipperPrinter::Printing:
        qDebug() << "Cannot move toolhead during print operation";
        break;
    case QKlipperPrinter::Error:
    case QKlipperPrinter::Offline:
    case QKlipperPrinter::Connecting:
        qDebug() << "Cannot move toolhead. Printer offline.";
        break;
    };
}

void PrinterPage::on_zPosIncreaseButton_clicked()
{
    QString valueString = ui->posIncrementSelect->currentText();
    valueString.remove(QString("mm"));

    qreal amount = valueString.toDouble();

    switch(m_printer->status())
    {

    case QKlipperPrinter::Ready:
        qDebug() << "Moving toolhead";
        m_printer->toolhead()->moveZ(amount);
        break;
    case QKlipperPrinter::Paused:
    case QKlipperPrinter::Cancelled:
    case QKlipperPrinter::Printing:
        qDebug() << "Cannot move toolhead during print operation";
        break;
    case QKlipperPrinter::Error:
    case QKlipperPrinter::Offline:
    case QKlipperPrinter::Connecting:
        qDebug() << "Cannot move toolhead. Printer offline.";
        break;
    };
}

void PrinterPage::on_xDestinationSpinBox_valueChanged(double arg1)
{
    if(ui->xDestinationSpinBox->hasFocus() && arg1 != m_printer->toolhead()->position().x())
        xPosEditing = true;
}


void PrinterPage::on_yDestinationSpinBox_valueChanged(double arg1)
{
    if(ui->yDestinationSpinBox->hasFocus() && arg1 != m_printer->toolhead()->position().y())
        yPosEditing = true;
}


void PrinterPage::on_zDestinationSpinBox_valueChanged(double arg1)
{
    if(ui->zDestinationSpinBox->hasFocus() && arg1 != m_printer->toolhead()->position().z())
        zPosEditing = true;
}


void PrinterPage::on_positionResetButton_clicked()
{
    ui->xDestinationSpinBox->setValue((m_printer->toolhead()->destination().x()));
    ui->yDestinationSpinBox->setValue((m_printer->toolhead()->destination().y()));
    ui->zDestinationSpinBox->setValue((m_printer->toolhead()->destination().z()));
}


void PrinterPage::on_positionApplyButton_clicked()
{
    QKlipperPosition position;
    position["x"] = (ui->xDestinationSpinBox->value());
    position["y"] = (ui->yDestinationSpinBox->value());
    position["z"] = (ui->zDestinationSpinBox->value());

    switch(m_printer->status())
    {

    case QKlipperPrinter::Ready:
        qDebug() << "Moving toolhead";
        m_printer->toolhead()->setPosition(position);
        break;
    case QKlipperPrinter::Paused:
    case QKlipperPrinter::Cancelled:
    case QKlipperPrinter::Printing:
        qDebug() << "Cannot move toolhead during print operation";
        break;
    case QKlipperPrinter::Error:
    case QKlipperPrinter::Offline:
    case QKlipperPrinter::Connecting:
        qDebug() << "Cannot move toolhead. Printer offline.";
        break;
    };
}

void PrinterPage::printerStartupEvent()
{
    m_printerOfflineScreen->lower();
    m_printerOfflineScreen->hide();
}

void PrinterPage::printerDisconnectEvent()
{
    m_printerOfflineScreen->raise();
    m_printerOfflineScreen->show();
}

void PrinterPage::onPrinterStatusChanged()
{
    QString status;
    QPixmap pixmap;

    pixmap = Settings::getThemeIcon(QString("printer")).pixmap(28,28);
    ui->statusIconLabel->setPixmap(pixmap);

    m_statusOverlayFrame->raise();
    m_statusOverlayFrame->setVisible(true);
    m_statusOverlayFrame->setGeometry(0, 0, ui->printerStatusContents->width(), ui->printerStatusContents->height());

    switch(m_printer->status())
    {
    case QKlipperPrinter::Ready:

        if(ui->stackedWidget->currentWidget() == m_printingPage)
            ui->stackedWidget->setCurrentIndex(0);

        status = QString("Ready");
        break;

    case QKlipperPrinter::Error:

        if(ui->stackedWidget->currentWidget() == m_printingPage)
            ui->stackedWidget->setCurrentIndex(0);

        status = QString("Error");

        if(m_printer->statusMessage().contains("\n"))
        {
            QStringList split = m_printer->statusMessage().split(QString("\n"), Qt::SkipEmptyParts);
            status = split.last();
        }

        // setPrintActionsEnabled(false);
        break;

    case QKlipperPrinter::Cancelled:

        if(ui->stackedWidget->currentWidget() == m_printingPage)
            ui->stackedWidget->setCurrentIndex(0);

        status = QString("Cancelled");

        setPrintActionsEnabled(true);
        break;

    case QKlipperPrinter::Printing:
        status = QString("Printing");

        if(ui->stackedWidget->currentWidget() != m_printingPage)
            ui->stackedWidget->setCurrentWidget(m_printingPage);

        break;

    case QKlipperPrinter::Paused:
        status = QString("Paused");

        if(ui->stackedWidget->currentWidget() != m_printingPage)
            ui->stackedWidget->setCurrentWidget(m_printingPage);

        break;

    case QKlipperPrinter::Offline:

        if(ui->stackedWidget->currentWidget() == m_printingPage)
            ui->stackedWidget->setCurrentIndex(0);

        setPrintActionsEnabled(false);
        break;

    default:

        if(ui->stackedWidget->currentWidget() == m_printingPage)
            ui->stackedWidget->setCurrentIndex(0);
        break;
    }

    ui->toolheadControlFrame->setEnabled(true);
    ui->restartButton->setEnabled(true);
}

void PrinterPage::onPrinterStatusMessageChanged()
{
    m_statusLabel->setText(m_printer->statusMessage());
}

void PrinterPage::onPrinterEndingTimeChanged()
{
    if(m_printer->status() == QKlipperPrinter::Printing)
        ui->etaLabel->setText(QString("ETA: ") + m_printer->printEnding().toString());
}

void PrinterPage::onToolHeadExtrudersChanged()
{
    if(m_extruderMap.count() < m_printer->toolhead()->extruderMap().count())
    {
        for(int i = m_extruderMap.count(); i < m_printer->toolhead()->extruderMap().count(); i++)
        {
            QString name = i > 0 ? QString("extruder") + QString::number(i) : QString("extruder");
            addExtruder(m_printer->toolhead()->extruder(name));
        }
    }
}

void PrinterPage::onToolheadPositionChanged()
{
    ui->xLabel->setText(QString("X: ") + QString::number(m_printer->toolhead()->position().x()));
    ui->yLabel->setText(QString("Y: ") + QString::number(m_printer->toolhead()->position().y()));
    ui->zLabel->setText(QString("Z: ") + QString::number(m_printer->toolhead()->position().z()));
}

void PrinterPage::onToolHeadDestinationChanged()
{
    if(!xPosEditing && !ui->xDestinationSpinBox->hasFocus())
        ui->xDestinationSpinBox->setValue((m_printer->toolhead()->destination().x()));

    if(!yPosEditing && !ui->yDestinationSpinBox->hasFocus())
        ui->yDestinationSpinBox->setValue((m_printer->toolhead()->destination().y()));

    if(!zPosEditing && !ui->zDestinationSpinBox->hasFocus())
        ui->zDestinationSpinBox->setValue((m_printer->toolhead()->destination().z()));
}

void PrinterPage::onSystemStateChanged()
{
    switch(m_instance->system()->state())
    {
        case QKlipperSystem::Idle:
            if(m_instance->isConnected())
            {
                m_printerOfflineScreen->lower();
                m_printerOfflineScreen->setVisible(false);
            }
            break;
        case QKlipperSystem::Updating:
            m_printerOfflineScreen->setText("Klipper Is Updating..");
            m_printerOfflineScreen->setVisible(true);
            m_printerOfflineScreen->raise();
            break;
    }
}

void PrinterPage::onInstanceError(QKlipperInstance *instance, QKlipperError &error)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    MessageDialog dialog;
    dialog.resize(screenGeometry.width() * 0.25, screenGeometry.height() * 0.25);
    dialog.setText(error.errorString());
    dialog.setWindowTitle(error.errorTitle() + " (" + instance->name() + ")");
    dialog.setIcon(Settings::getThemeIcon("error", QColor::fromString(Settings::get("theme/icon-error-color").toString())));
    dialog.exec();
}

void PrinterPage::on_stackedWidget_currentChanged(int arg1)
{
    if(ui->stackedWidget->widget(arg1) == ui->overviewWidget)
        ui->actionBar->setFixedHeight(0);
    else
        ui->actionBar->setFixedHeight(50);
}

void PrinterPage::on_settingsButton_clicked()
{
    onSettingsButtonClicked();
}

void PrinterPage::on_browserButton_clicked()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    m_fileBrowser->resize(screenGeometry.width() * 0.75, screenGeometry.height() * 0.75);
    m_fileBrowser->exec();
}

void PrinterPage::on_terminalButton_clicked()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    m_terminal->resize(screenGeometry.width() * 0.75, screenGeometry.height() * 0.75);
    m_terminal->exec();
}

void PrinterPage::on_goBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void PrinterPage::on_gcodeButton_clicked()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    GCodeMacroDialog *dialog = new GCodeMacroDialog(m_instance->server(), this);
    dialog->resize(screenGeometry.width() * 0.75, screenGeometry.height() * 0.75);
    dialog->exec();
}

void PrinterPage::on_restartButton_clicked()
{
    QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(m_printer->parent());

    if(instance)
        instance->console()->restartFirmware();
}

void PrinterPage::on_restartKlipperButton_clicked()
{
    QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(m_printer->parent());

    if(instance)
        instance->console()->restartKlipper();
}

void PrinterPage::on_toolButton_triggered(QAction *arg1)
{
    //ui->stackedWidget->setCurrentWidget(m_printingPage);
}

void PrinterPage::on_toolButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_printingPage);
}

void PrinterPage::on_inputShaperButton_clicked()
{
    QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(m_printer->parent());

    if(instance)
    {
        m_inputShaperWizard = new InputShaperWizard(instance, this);
        m_inputShaperWizard->exec();

        delete m_inputShaperWizard;
    }
}

void PrinterPage::on_zOffsetWizardButton_clicked()
{
    QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(m_printer->parent());

    if(instance)
    {
        m_zOffsetWizard = new ZOffsetWizard(instance, this);
        m_zOffsetWizard->exec();

        delete m_zOffsetWizard;
    }
}
