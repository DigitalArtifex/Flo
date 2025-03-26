#include "printerpage.h"
#include "ui_printerpage.h"
#include "flo/settings.h"
PrinterPage::PrinterPage(QKlipperInstance *instance, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrinterPage)
{
    ui->setupUi(this);
    m_instance = instance;

    m_printerFanWidget = new PrinterFanWidget(instance->printer(), ui->fanFrame);
    ui->fanFrameLayout->addWidget(m_printerFanWidget);

    m_bedMeshWidget = new BedMeshWidget(instance->printer()->bed(),ui->stackWidget);
    ui->stackWidget->addWidget(m_bedMeshWidget);
    connect(m_bedMeshWidget, SIGNAL(closed(Page*)), this, SLOT(onPageClosed(Page *)));

    m_terminal = new PrinterTerminal(instance, this);
    m_terminal->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->stackWidget->addWidget(m_terminal);

    connect(m_terminal, SIGNAL(closed(Page*)), this, SLOT(onPageClosed(Page *)));

    m_fileBrowser = new FileBrowser(instance, QString("gcodes"));
    m_fileBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->stackWidget->addWidget(m_fileBrowser);
    connect(m_fileBrowser, SIGNAL(closed(Page*)), this, SLOT(onPageClosed(Page *)));
    connect(m_fileBrowser, SIGNAL(dialogRequested(QDialog*)), this, SLOT(onDialogRequested(QDialog*)));
    connect(m_fileBrowser, SIGNAL(wizardRequested(QWizard*)), this, SLOT(onWizardRequested(QWizard*)));

    m_printerSettingsPage = new PrinterSettingsPage(instance, ui->settingsWidget);
    ui->settingsWidget->layout()->addWidget(m_printerSettingsPage);
    connect(m_printerSettingsPage, SIGNAL(dialogRequested(QDialog*)), this, SLOT(onDialogRequested(QDialog*)));
    connect(m_printerSettingsPage, SIGNAL(wizardRequested(QWizard*)), this, SLOT(onWizardRequested(QWizard*)));

    connect(m_printerSettingsPage, SIGNAL(closed(Page*)), this, SLOT(onPageClosed(Page *)));

    m_printerOfflineScreen = new PrinterOfflineScreen(instance, this);
    m_printerOfflineScreen->setGeometry(QRect(0,0,width(),height()));
    m_printerOfflineScreen->raise();

    m_printerBedWidget = new PrinterBedWidget(instance->printer()->bed(), ui->toolBox);
    ui->toolBox->addItem(m_printerBedWidget, Settings::getThemeIcon("mesh"), "Bed");

    connect(m_printerBedWidget, SIGNAL(dialogRequested(QDialog*)), this, SLOT(onDialogRequested(QDialog*)));

    m_overviewWidget = new PrinterOverviewWidget(m_instance->printer(), this);
    ui->toolBox->insertItem(0,m_overviewWidget, "Overview");

    setPrinter(instance->printer());

    m_webcamWidget = new PrinterWebcamWidget(instance, ui->webcamContentWidget);
    ui->webcamContentWidget->layout()->addWidget(m_webcamWidget);

    connect(m_instance, SIGNAL(error(QKlipperInstance*,QKlipperError&)), this, SLOT(onInstanceError(QKlipperInstance*,QKlipperError&)));
    connect(m_instance->printer(), SIGNAL(statusChanged()), this, SLOT(onPrinterStatusChanged()));
    connect(m_instance->system(), SIGNAL(stateChanged()), this, SLOT(onSystemStateChanged()));

    m_statusOverlayFrame = new QFrame(ui->printerStatusContents);
    m_statusLabel = new QLabel(m_statusOverlayFrame);
    m_statusLabel->setWordWrap(true);

    m_statusOverlayFrame->setLayout(new QGridLayout(m_statusOverlayFrame));
    m_statusOverlayFrame->layout()->addWidget(m_statusLabel);
    m_statusOverlayFrame->lower();
    m_statusOverlayFrame->setVisible(false);

    // m_toolheadWidget = new ToolheadWidget(instance, this);
    // ui->toolBox->addItem(m_toolheadWidget, Settings::getThemeIcon("control"), "Toolhead");

    // connect(m_toolheadWidget, SIGNAL(wizardRequested(QWizard*)), this, SLOT(onWizardRequested(QWizard*)));

    m_printingPage = new PrintingPage(instance->printer(), ui->stackWidget);
    ui->stackWidget->addWidget(m_printingPage);

    connect(m_printingPage, SIGNAL(closed(Page*)), this, SLOT(onPageClosed(Page *)));

    connect(m_printerBedWidget->bedMeshViewerButton(), SIGNAL(clicked()), this, SLOT(onBedMeshButtonClicked()));

    setupUiClasses();
    setStyleSheet(Settings::currentTheme());

    setupAnimations();

    ui->actionBar->setFixedHeight(0);

    m_statusOverlayFrame->resize(ui->printerStatusContents->size());
    m_statusOverlayFrame->raise();
    m_statusOverlayFrame->setVisible(true);

    ui->toolBox->setToolBoxButtonHeight(64);
    ui->toolBox->setSpacing(0);

    m_updatingScreen = new PrinterUpdatingScreen(m_instance->system()->updateManager(), this);
    ui->stackWidget->addWidget(m_updatingScreen);

    m_toolheadControlFrame = new ToolHeadControlFrame(instance->printer()->toolhead(), ui->controlContents);
    ui->controlContents->layout()->addWidget(m_toolheadControlFrame);

    ui->toolheadControlFrame->setCentralWidget(ui->toolheadContentWidget);
    ui->toolheadControlFrame->setTitle("Toolhead Control");
    ui->toolheadContentWidget->setProperty("class", QStringList {"SubWidget"});

    ui->positionCard->setCentralWidget(ui->positionContentsWidget);
    ui->positionCard->setTitle("Absolute Position");

    connect(m_printer, SIGNAL(hasChamberChanged()), this, SLOT(onPrinterHasChamberChanged()));
    connect(m_instance, SIGNAL(connected(QKlipperInstance *)), this, SLOT(onInstanceConnected(QKlipperInstance*)));
    connect(m_instance, SIGNAL(disconnected(QKlipperInstance*)), this, SLOT(onInstanceDisconnected(QKlipperInstance*)));
    connect(m_instance->system(), SIGNAL(powerDevicesChanged()), this, SLOT(onPrinterPowerDevicesChanged()));
    connect(m_instance->system(), SIGNAL(ledStripsChanged()), this, SLOT(onPrinterLedStripsChanged()));
    connect(m_instance->system(), SIGNAL(sensorsChanged()), this, SLOT(onPrinterSensorListChanged()));
    connect(m_printer->toolhead(), SIGNAL(destinationChanged()), this, SLOT(onToolHeadDestinationChanged()));

    QRegularExpression distanceExpression("\\d+\\.\\d+\\s*", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionValidator *distanceValidator = new QRegularExpressionValidator(distanceExpression);
    ui->posIncrementSelect->setValidator(distanceValidator);
}

PrinterPage::~PrinterPage()
{
    m_fileBrowser->deleteLater();

    m_terminal->deleteLater();
    m_printerOfflineScreen->deleteLater();

    delete ui;
}

void PrinterPage::addExtruder(QKlipperExtruder *extruder, QString name)
{
    if(name == QString("Extruder") && m_extruderMap.count() > 0)
        name = QString("Extruder #") + QString::number(m_extruderMap.count() + 1);

    int index = m_extruderMap.count();

    m_extruderMap[index] = new ExtruderWidget(extruder, ui->toolBox);
    m_extruderMap[index]->setExtruder(extruder);
    connect(m_extruderMap[index], SIGNAL(dialogRequested(QDialog*)), this, SLOT(onDialogRequested(QDialog*)));

    int stackIndex = 1;

    if(index > 0)
        stackIndex = ui->toolBox->indexOf(m_extruderMap[m_extruderMap.count() - 1]) + 1;

    ui->toolBox->insertItem(stackIndex, m_extruderMap[index], name);
    ui->toolBox->setItemIcon(ui->toolBox->indexOf(m_extruderMap[index]), Settings::getThemeIcon("extruder"));

    if (index == 0)
        ui->toolBox->setCurrentIndex(0);
}

void PrinterPage::setIcons()
{
    QPixmap pixmap = Settings::getThemeIcon(QString("printer")).pixmap(28,28);
    ui->statusIconLabel->setPixmap(pixmap);

    // ui->toolBox->setItemIcon(
    //     ui->toolBox->indexOf(m_toolheadWidget),
    //     Settings::getThemeIcon(QString("toolhead"))
    //     );

    ui->toolBox->setItemIcon(
        ui->toolBox->indexOf(m_printerBedWidget),
        Settings::getThemeIcon(QString("bed"))
        );

    for(ExtruderWidget *widget : m_extruderMap)
    {
        ui->toolBox->setItemIcon(
            ui->toolBox->indexOf(widget),
            Settings::getThemeIcon(QString("extruder"))
            );
    }

    ui->toolBox->setItemIcon(
        ui->toolBox->indexOf(m_overviewWidget),
        Settings::getThemeIcon(QString("overview"))
        );

    if(m_chamberWidget)
    {
        ui->toolBox->setItemIcon(
            ui->toolBox->indexOf(m_chamberWidget),
            Settings::getThemeIcon(QString("printer"))
            );
    }

    if(m_powerDeviceView)
    {
        ui->toolBox->setItemIcon(
            ui->toolBox->indexOf(m_powerDeviceView),
            Settings::getThemeIcon(QString("power-device"))
            );
    }

    if(m_ledDeviceView)
    {
        ui->toolBox->setItemIcon(
            ui->toolBox->indexOf(m_ledDeviceView),
            Settings::getThemeIcon(QString("led"))
            );
    }

    if(m_sensorDeviceView)
    {
        ui->toolBox->setItemIcon(
            ui->toolBox->indexOf(m_sensorDeviceView),
            Settings::getThemeIcon(QString("sensors"))
            );
    }

    ui->browserButton->setIcon(
        Settings::getThemeIcon(
            "browser",
            QColor::fromString(Settings::get("theme/accent-color").toString())
            )
        );

    ui->browserButton->setIconSize(QSize(50,50));

    ui->terminalButton->setIcon(Settings::getThemeIcon("console", QColor::fromString(Settings::get("theme/accent-color2").toString())));
    ui->terminalButton->setIconSize(QSize(50,50));

    ui->gcodeButton->setIcon(
        Settings::getThemeIcon(
            "tools",
            QColor::fromString(Settings::get("theme/accent-color3").toString())
            )
        );

    ui->toolheadControlFrame->setIcon(
        Settings::getThemeIcon(
            "toolhead"
            )
        );

    ui->positionCard->setIcon(
        Settings::getThemeIcon(
            "location"
            )
        );

    ui->gcodeButton->setIconSize(QSize(50,50));

    ui->settingsButton->setIcon(Settings::getThemeIcon("printer-settings", QColor::fromString(Settings::get("theme/accent-color4").toString())));
    ui->settingsButton->setIconSize(QSize(50,50));

    pixmap = Settings::getThemeIcon(QString("webcam")).pixmap(28,28);
    ui->webcamIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon(QString("printer")).pixmap(28,28);
    ui->statusIconLabel->setPixmap(pixmap);

    //m_overviewWidget->setIcon(Settings::getThemeIcon("chart"));
    ui->goBackButton->setIcon(Settings::getThemeIcon(QString("up-directory")));
}

void PrinterPage::setupUiClasses()
{
    ui->actionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageActionBar"));
    ui->pageContents->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    m_bedMeshWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));

    m_statusOverlayFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" << "PrinterSubWidget"));

    ui->printJobWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget"));
    //ui->printProgressWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" << "PrinterSubWidget"));
    //ui->temperatureWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget"));
    ui->webcamGroupBox->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget"));

    ui->printStatusTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));
    ui->printStatusTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    ui->webcamTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));
    ui->webcamTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

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

void PrinterPage::onOverviewButtonClicked()
{
    ui->stackWidget->slideInWgt(ui->overviewWidget);
    // m_webcamWidget->show();
}

void PrinterPage::onSettingsButtonClicked()
{
    ui->stackWidget->slideInWgt(ui->settingsWidget);
}

void PrinterPage::onBedMeshButtonClicked()
{
    ui->stackWidget->slideInWgt(m_bedMeshWidget);
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

    onToolHeadExtrudersChanged();
}

void PrinterPage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if(m_printerOfflineScreen)
        m_printerOfflineScreen->setGeometry(QRect(0,0,width(),height()));

    if(m_statusOverlayFrame)
        m_statusOverlayFrame->resize(ui->printerStatusContents->size());
}

void PrinterPage::setPrintActionsEnabled(bool enabled)
{
    if(m_chamberWidget)
        m_chamberWidget->setEnabled(enabled);
    m_overviewWidget->setEnabled(enabled);
    // m_toolheadWidget->setEnabled(enabled);
}

void PrinterPage::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
    {
        ui->xDestinationLabel->setAccentColor(Settings::get("theme/accent-color").toString());
        ui->yDestinationLabel->setAccentColor(Settings::get("theme/accent-color2").toString());
        ui->zDestinationLabel->setAccentColor(Settings::get("theme/accent-color3").toString());
        setIcons();
    }

    QWidget::changeEvent(event);
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

void PrinterPage::onInstanceDisconnected(QKlipperInstance* instance)
{
    //There is a bug with stopping and starting the stream. Recreate it to avoid it
    deleteWebcamWidget();
    createWebcamWidget();

    ui->stackWidget->slideInIdx(0);
}

void PrinterPage::createWebcamWidget()
{
    if(m_webcamWidget)
        return;

    m_webcamWidget = new PrinterWebcamWidget(m_instance);
    ui->webcamContentWidget->layout()->addWidget(m_webcamWidget);
}

void PrinterPage::deleteWebcamWidget()
{
    m_webcamWidget->stop();
    ui->webcamContentWidget->layout()->removeWidget(m_webcamWidget);
    delete m_webcamWidget;
    m_webcamWidget = nullptr;
}

void PrinterPage::onPrinterStatusChanged()
{
    // QString status;
    // QPixmap pixmap;

    // pixmap = Settings::getThemeIcon(QString("printer")).pixmap(28,28);
    // ui->statusIconLabel->setPixmap(pixmap);

    // m_statusOverlayFrame->raise();
    // m_statusOverlayFrame->setVisible(true);
    // m_statusOverlayFrame->setGeometry(0, 0, ui->printerStatusContents->width(), ui->printerStatusContents->height());

    // switch(m_printer->status())
    // {
    // case QKlipperPrinter::Ready:

    //     if(ui->stackWidget->currentWidget() == m_printingPage)
    //         ui->stackWidget->setCurrentIndex(0);

    //     status = QString("Ready");
    //     break;

    // case QKlipperPrinter::Error:

    //     if(ui->stackWidget->currentWidget() == m_printingPage)
    //         ui->stackWidget->setCurrentIndex(0);

    //     status = QString("Error");

    //     if(m_printer->statusMessage().contains("\n"))
    //     {
    //         QStringList split = m_printer->statusMessage().split(QString("\n"), Qt::SkipEmptyParts);
    //         status = split.last();
    //     }

    //     setPrintActionsEnabled(false);
    //     break;

    // case QKlipperPrinter::Cancelled:

    //     if(ui->stackWidget->currentWidget() == m_printingPage)
    //         ui->stackWidget->setCurrentIndex(0);

    //     status = QString("Cancelled");

    //     setPrintActionsEnabled(true);
    //     break;

    // case QKlipperPrinter::Printing:
    //     status = QString("Printing");

    //     if(ui->stackWidget->currentWidget() != m_printingPage)
    //         ui->stackWidget->setCurrentWidget(m_printingPage);

    //     break;

    // case QKlipperPrinter::Paused:
    //     status = QString("Paused");

    //     if(ui->stackWidget->currentWidget() != m_printingPage)
    //         ui->stackWidget->setCurrentWidget(m_printingPage);

    //     break;

    // case QKlipperPrinter::Offline:

    //     if(ui->stackWidget->currentWidget() == m_printingPage)
    //         ui->stackWidget->setCurrentIndex(0);

    //     //m_webcamWidget->stop();

    //     setPrintActionsEnabled(false);
    //     break;

    // default:

    //     if(ui->stackWidget->currentWidget() == m_printingPage)
    //         ui->stackWidget->setCurrentIndex(0);
    //     break;
    // }

    // m_toolheadWidget->setEnabled(true);
    //ui->restartButton->setEnabled(true);
}

void PrinterPage::onPrinterStatusMessageChanged()
{
    // QStringList splitMessage = m_printer->statusMessage().split('\n', Qt::SkipEmptyParts);

    // if(splitMessage.count() == 1)
    // {
    //     m_statusLabel->setText(splitMessage.at(0));

    //     ui->printerStatusTitleLabel->setText(QString("Printer Status"));
    // }
    // else if(splitMessage.count() == 2)
    // {
    //     QString status = splitMessage.takeFirst();
    //     QString message = splitMessage.join(' ');
    //     message = QString("<h4>%1</h4>\n\n<p>%2</p>").arg(status, message);

    //     ui->printerStatusTitleLabel->setText(QString("Printer Status"));
    //     m_statusLabel->setText(message);
    // }
    // else if(splitMessage.count() >= 3)
    // {
    //     QString title = splitMessage.takeLast();
    //     QString status = splitMessage.takeFirst();
    //     QString message = splitMessage.join(' ');
    //     message = QString("<h4>%1</h4>\n\n<p>%2</p>").arg(status, message);

    //     ui->printerStatusTitleLabel->setText(QString("Printer Status (%1)").arg(title));
    //     m_statusLabel->setText(message);
    // }
}

void PrinterPage::onPrinterEndingTimeChanged()
{
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

void PrinterPage::onSystemStateChanged()
{
    switch(m_instance->system()->state())
    {
        case QKlipperSystem::Idle:
            createWebcamWidget();
            ui->stackWidget->slideInIdx(0);
            break;
        case QKlipperSystem::Updating:
            deleteWebcamWidget();
            ui->stackWidget->slideInWgt(m_updatingScreen);
            break;
    }
}

void PrinterPage::onPrinterHasChamberChanged()
{
    if(m_printer->hasChamber() && !m_chamberWidget)
    {
        m_chamberWidget = new PrinterChamberWidget(m_instance, this);
        ui->toolBox->addItem(m_chamberWidget);
    }
    else if(!m_printer->hasChamber() && m_chamberWidget)
    {
        ui->toolBox->removeItem(m_chamberWidget);
        m_chamberWidget = nullptr; //gets deleted by removeItem
    }
}

void PrinterPage::onPrinterPowerDevicesChanged()
{
    if(m_instance->system()->powerDevices().count() > 0 && !m_powerDeviceView)
    {
        m_powerDeviceView = new PowerDeviceView(m_instance->system(), ui->toolBox);
        m_powerDeviceView->setCardFlags(CardWidget::NoTitleBar);
        ui->toolBox->addItem(m_powerDeviceView, Settings::getThemeIcon("power-device"), "Power Devices");
    }
    else if(m_instance->system()->powerDevices().isEmpty() && m_powerDeviceView)
    {
        ui->toolBox->removeItem(m_powerDeviceView);
        m_powerDeviceView = nullptr; //gets deleted by removeItem
    }
}

void PrinterPage::onPrinterLedStripsChanged()
{
    if(m_instance->system()->ledStrips().count() > 0 && !m_ledDeviceView)
    {
        m_ledDeviceView = new LedStripView(m_instance->system(), ui->toolBox);
        m_ledDeviceView->setCardFlags(CardWidget::NoTitleBar);
        ui->toolBox->addItem(m_ledDeviceView, Settings::getThemeIcon("led"), "LED Strips");
    }
    else if(m_instance->system()->ledStrips().isEmpty() && m_ledDeviceView)
    {
        ui->toolBox->removeItem(m_ledDeviceView);
        m_ledDeviceView = nullptr; //gets deleted by removeItem
    }
}

void PrinterPage::onPrinterSensorListChanged()
{
    if(m_instance->system()->sensors().count() > 0 && !m_sensorDeviceView)
    {
        m_sensorDeviceView = new SensorView(m_instance->system(), ui->toolBox);
        m_sensorDeviceView->setCardFlags(CardWidget::NoTitleBar);
        ui->toolBox->addItem(m_sensorDeviceView, Settings::getThemeIcon("sensors"), "Sensors");
    }
    else if(m_instance->system()->sensors().isEmpty() && m_sensorDeviceView)
    {
        ui->toolBox->removeItem(m_sensorDeviceView);
        m_sensorDeviceView = nullptr; //gets deleted by removeItem
    }
}

void PrinterPage::onInstanceError(QKlipperInstance *instance, QKlipperError &error)
{
    // QScreen *screen = QGuiApplication::primaryScreen();
    // QRect screenGeometry = screen->geometry();

    // MessageDialog dialog;
    // dialog.resize(screenGeometry.width() * 0.25, screenGeometry.height() * 0.25);
    // dialog.setText(error.errorString());
    // dialog.setWindowTitle(error.errorTitle() + " (" + instance->name() + ")");
    // dialog.setIcon(Settings::getThemeIcon("error", QColor::fromString(Settings::get("theme/icon-error-color").toString())));
    // dialog.exec();
}

void PrinterPage::on_settingsButton_clicked()
{
    onSettingsButtonClicked();
}

void PrinterPage::on_browserButton_clicked()
{
    ui->stackWidget->slideInWgt(m_fileBrowser);
}

void PrinterPage::on_terminalButton_clicked()
{
    ui->stackWidget->slideInWgt(m_terminal);
}

void PrinterPage::on_goBackButton_clicked()
{
    //ui->stackWidget->setCurrentIndex(0);
}

void PrinterPage::on_gcodeButton_clicked()
{
    m_toolsDialog = new PrinterToolsDialog(this);
    onDialogRequested(m_toolsDialog);
    connect(m_toolsDialog, SIGNAL(finished(int)), this, SLOT(onToolsDialogFinished(int)));
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

void PrinterPage::on_toolButton_clicked()
{
    ui->stackWidget->setCurrentWidget(m_printingPage);
}

void PrinterPage::onPageClosed(Page *page)
{
    ui->stackWidget->slideInIdx(0);
}

void PrinterPage::onDialogRequested(QDialog *dialog)
{
    m_requestedDialog = dialog;

    m_dialogSheet = new Sheet(m_requestedDialog, qobject_cast<QWidget*>(parent()));
    m_dialogSheet->setWidth(width() / 3);
    m_dialogSheet->showSheet(this);
    connect(dialog, SIGNAL(finished(int)), this, SLOT(onDialogFinished(int)));
}

void PrinterPage::onDialogFinished(int returnCode)
{
    Q_UNUSED(returnCode)

    m_dialogSheet->hideSheet(Settings::get("ui/animations_enabled").toBool());
    disconnect(m_requestedDialog, SIGNAL(finished(int)), this, SLOT(onDialogFinished(int)));
    m_requestedDialog = nullptr;
}

void PrinterPage::onWizardRequested(QWizard *wizard)
{
    m_requestedWizardReturnIndex = ui->stackWidget->currentIndex();
    m_requestedWizard = wizard;
    connect(m_requestedWizard, SIGNAL(finished(int)), this, SLOT(onWizardFinished(int)));

    ui->stackWidget->addWidget(wizard);
    ui->stackWidget->slideInWgt(wizard);
}

void PrinterPage::onWizardFinished(int returnCode)
{
    Q_UNUSED(returnCode);

    ui->stackWidget->removeWidget(m_requestedWizard);
    ui->stackWidget->slideInIdx(m_requestedWizardReturnIndex);
    m_requestedWizardReturnIndex = 0;

    disconnect(m_requestedWizard, SIGNAL(finished(int)), this, SLOT(onWizardFinished(int)));
    m_requestedWizard = nullptr;
}

void PrinterPage::onToolsDialogFinished(int code)
{
    switch(code)
    {
    case PrinterToolsDialog::InputShaper:
        m_inputShaperWizard = new InputShaperWizard(m_instance, this);
        onWizardRequested(m_inputShaperWizard);
        connect(m_inputShaperWizard, SIGNAL(finished(int)), this, SLOT(onInputShaperWizardFinished(int)));
        break;
    case PrinterToolsDialog::ZOffset:
        m_zOffsetWizard = new ZOffsetWizard(m_instance, this);
        onWizardRequested(m_zOffsetWizard);
        connect(m_zOffsetWizard, SIGNAL(finished(int)), this, SLOT(onZOffsetWizardFinished(int)));
        break;
    }

    delete m_toolsDialog;
    m_toolsDialog = nullptr;
}

void PrinterPage::onInputShaperWizardFinished(int code)
{
    Q_UNUSED(code)
    if(m_inputShaperWizard)
    {
        delete m_inputShaperWizard;
        m_inputShaperWizard = nullptr;
    }
}

void PrinterPage::onZOffsetWizardFinished(int code)
{
    Q_UNUSED(code)
    if(m_zOffsetWizard)
    {
        delete m_zOffsetWizard;
        m_zOffsetWizard = nullptr;
    }
}

void PrinterPage::on_xDestinationSpinBox_valueChanged(double arg1)
{
    if(ui->xDestinationSpinBox->hasFocus() && arg1 != m_printer->toolhead()->position().x())
        xPosEditing = true;

    ui->applyDestinationButton->setEnabled((zPosEditing || xPosEditing || yPosEditing));
    ui->resetDestinationButton->setEnabled((zPosEditing || xPosEditing || yPosEditing));
}

void PrinterPage::on_yDestinationSpinBox_valueChanged(double arg1)
{
    if(ui->yDestinationSpinBox->hasFocus() && arg1 != m_printer->toolhead()->position().y())
        yPosEditing = true;

    ui->applyDestinationButton->setEnabled((zPosEditing || xPosEditing || yPosEditing));
    ui->resetDestinationButton->setEnabled((zPosEditing || xPosEditing || yPosEditing));
}

void PrinterPage::on_zDestinationSpinBox_valueChanged(double arg1)
{
    if(ui->zDestinationSpinBox->hasFocus() && arg1 != m_printer->toolhead()->position().z())
        zPosEditing = true;

    ui->applyDestinationButton->setEnabled((zPosEditing || xPosEditing || yPosEditing));
    ui->resetDestinationButton->setEnabled((zPosEditing || xPosEditing || yPosEditing));
}

void PrinterPage::on_resetDestinationButton_clicked()
{
    ui->xDestinationSpinBox->setValue((m_printer->toolhead()->destination().x()));
    ui->yDestinationSpinBox->setValue((m_printer->toolhead()->destination().y()));
    ui->zDestinationSpinBox->setValue((m_printer->toolhead()->destination().z()));
    xPosEditing = false;
    yPosEditing = false;
    zPosEditing = false;
}

void PrinterPage::on_applyDestinationButton_clicked()
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

    on_resetDestinationButton_clicked();
}

void PrinterPage::onToolHeadDestinationChanged()
{
    // set maximums
    ui->xDestinationSpinBox->setMaximum(m_printer->toolhead()->maxPosition().x());
    ui->yDestinationSpinBox->setMaximum(m_printer->toolhead()->maxPosition().y());
    ui->zDestinationSpinBox->setMaximum(m_printer->toolhead()->maxPosition().y());

    if(!xPosEditing)
        ui->xDestinationSpinBox->setValue((m_printer->toolhead()->destination().x()));

    if(!yPosEditing)
        ui->yDestinationSpinBox->setValue((m_printer->toolhead()->destination().y()));

    if(!zPosEditing)
        ui->zDestinationSpinBox->setValue((m_printer->toolhead()->destination().z()));

    // ui->xPosLabel->setText(QString("<i>%1</i>").arg(m_printer->toolhead()->position().x(), 0, 'f', 2));
    // ui->yPosLabel->setText(QString("<i>%1</i>").arg(m_printer->toolhead()->position().y(), 0, 'f', 2));
    // ui->zPosLabel->setText(QString("<i>%1</i>").arg(m_printer->toolhead()->position().z(), 0, 'f', 2));
}
