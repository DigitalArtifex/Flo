#include "printerpage.h"
#include "ui_printerpage.h"
#include "../../system/settings.h"

PrinterPage::PrinterPage(Printer *printer, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PrinterPage)
{
    ui->setupUi(this);

    m_toolheadControlFrame = new ToolHeadControlFrame(printer->toolhead(), ui->controlContents);
    ui->controlContents->layout()->addWidget(m_toolheadControlFrame);

    m_centerLayout = new QFlowLayout(ui->centerWidget);
    m_centerLayout->setContentsMargins(QMargins(0,0,0,0));
    ui->centerWidget->setLayout(m_centerLayout);

    m_chamberTemperatureBar = new CircularProgressBar(this);
    //_extruderTemperatureBar = new CircularProgressBar(this);

    ui->chamberLayout->addWidget(m_chamberTemperatureBar);
    ui->chamberWidget->setHidden(true);

    ui->tabWidget->setTabVisible(0, false);
    ui->tabWidget->setTabVisible(1, false);
    ui->tabWidget->setTabVisible(2, false);
    ui->tabWidget->setTabVisible(3, false);
    ui->tabWidget->setTabVisible(4, false);
    ui->tabWidget->setCurrentIndex(0);

    ui->restartFirmwareButton->setHidden(true);
    ui->cancelPrintButton->setHidden(true);
    ui->fileLabel->setHidden(true);
    ui->etaLabel->setHidden(true);
    ui->printStatsLine->setHidden(true);
    ui->printSpeedLabel->setHidden(true);
    ui->printSpeedSlider->setHidden(true);
    ui->printSpeedSpacer->changeSize(0,0);
    ui->printSpeedSpinBox->setHidden(true);
    ui->printProgress->setHidden(true);

    m_centerLayoutBottomSpacer = new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Preferred);
    m_centerLayout->setContentsMargins(9,0,0,0);

    m_terminal = new PrinterTerminal(printer, this);
    m_terminal->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->terminalTab->layout()->addWidget(m_terminal);

    m_fileBrowser = new FileBrowser(printer, QString("gcodes"));
    m_fileBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->gcodeTab->layout()->addWidget(m_fileBrowser);

    m_printerSettingsPage = new PrinterSettingsPage(printer, ui->settingsTab);
    ui->settingsTab->layout()->addWidget(m_printerSettingsPage);

    m_bedMeshWidget = new Q3DPrintBedMeshViewer(printer->bed(), ui->bedMeshTab);
    m_bedMeshWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->bedMeshTab->layout()->addWidget(m_bedMeshWidget);

    m_printerOfflineScreen = new PrinterOfflineScreen(printer, this);
    m_printerOfflineScreen->setGeometry(QRect(0,0,width(),height()));
    m_printerOfflineScreen->raise();

    QRegularExpression distanceExpression("\\d+\\.\\d+\\s*", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionValidator *distanceValidator = new QRegularExpressionValidator(distanceExpression);
    ui->posIncrementSelect->setValidator(distanceValidator);

    setPrinter(printer);

    m_printerBedWidget = new PrinterBedWidget(m_printer->bed(), this);
    m_centerLayout->addWidget(m_printerBedWidget);

    m_webcamWidget = new PrinterWebcamWidget(m_printer, ui->webcamContentWidget);
    ui->webcamContentWidget->layout()->addWidget(m_webcamWidget);

    //Setup action bar buttons
    QPixmap pixmap = Settings::getThemeIcon("add-icon").pixmap(28,28);
    m_overviewButton = new QIconButton(this);
    m_overviewButton->setFixedSize(250,50);
    m_overviewButton->setText("Overview");
    m_overviewButton->setPixmap(pixmap);
    m_overviewButton->setEnabled(true);
    m_overviewButton->setCheckable(true);
    m_overviewButton->setExclusive(true);
    m_overviewButton->setChecked(true);
    ui->actionBar->layout()->addWidget(m_overviewButton);

    pixmap = Settings::getThemeIcon("add-icon").pixmap(28,28);
    m_terminalButton = new QIconButton(this);
    m_terminalButton->setFixedSize(250,50);
    m_terminalButton->setText("Terminal");
    m_terminalButton->setPixmap(pixmap);
    m_terminalButton->setEnabled(true);
    m_terminalButton->setCheckable(true);
    m_terminalButton->setExclusive(true);
    ui->actionBar->layout()->addWidget(m_terminalButton);

    pixmap = Settings::getThemeIcon("add-icon").pixmap(28,28);
    m_fileBrowserButton = new QIconButton(this);
    m_fileBrowserButton->setFixedSize(250,50);
    m_fileBrowserButton->setText("G-Code Browser");
    m_fileBrowserButton->setPixmap(pixmap);
    m_fileBrowserButton->setEnabled(true);
    m_fileBrowserButton->setCheckable(true);
    m_fileBrowserButton->setExclusive(true);
    ui->actionBar->layout()->addWidget(m_fileBrowserButton);

    pixmap = Settings::getThemeIcon("add-icon").pixmap(28,28);
    m_bedMeshViewerButton = new QIconButton(this);
    m_bedMeshViewerButton->setFixedSize(250,50);
    m_bedMeshViewerButton->setText("Bed Mesh Viewer");
    m_bedMeshViewerButton->setPixmap(pixmap);
    m_bedMeshViewerButton->setEnabled(true);
    m_bedMeshViewerButton->setCheckable(true);
    m_bedMeshViewerButton->setExclusive(true);
    ui->actionBar->layout()->addWidget(m_bedMeshViewerButton);

    pixmap = Settings::getThemeIcon("add-icon").pixmap(28,28);
    m_settingsButton = new QIconButton(this);
    m_settingsButton->setFixedSize(250,50);
    m_settingsButton->setText("Machine Settings");
    m_settingsButton->setPixmap(pixmap);
    m_settingsButton->setEnabled(true);
    m_settingsButton->setCheckable(true);
    m_settingsButton->setExclusive(true);
    ui->actionBar->layout()->addWidget(m_settingsButton);

    m_buttonSpacer = new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Ignored);
    ui->actionBar->layout()->addItem(m_buttonSpacer);

    connect(m_overviewButton, SIGNAL(clicked()), this, SLOT(overviewButtonClickEvent()));
    connect(m_terminalButton, SIGNAL(clicked()), this, SLOT(terminalButtonClickEvent()));
    connect(m_bedMeshViewerButton, SIGNAL(clicked()), this, SLOT(bedMeshViewerButtonClickEvent()));
    connect(m_fileBrowserButton, SIGNAL(clicked()), this, SLOT(fileBrowserButtonClickEvent()));
    connect(m_settingsButton, SIGNAL(clicked()), this, SLOT(settingsButtonClickEvent()));

    setupUiClasses();
    setStyleSheet(Settings::currentTheme());
}

PrinterPage::~PrinterPage()
{
    delete m_chamberTemperatureBar;
    delete m_fileBrowser;

    if(m_bedMeshWidget)
        delete m_bedMeshWidget;

    delete m_terminal;
    delete m_printerOfflineScreen;

    delete ui;
}

void PrinterPage::addExtruder(Extruder *extruder, QString name)
{
    if(name == QString("Extruder") && m_extruderMap.count() >= 1)
        name = QString("Extruder #") + QString::number(m_extruderMap.count() + 1);

    int index = m_extruderMap.count();

    m_extruderMap[index] = new ExtruderWidget(this);
    m_extruderMap[index]->setExtruder(extruder);

    if(m_printerBedWidget)
        m_centerLayout->removeWidget(m_printerBedWidget);

    m_centerLayout->addWidget(m_extruderMap[index]);

    if(m_printerBedWidget)
        m_centerLayout->addWidget(m_printerBedWidget);
}

void PrinterPage::setStyleSheet(QString styleSheet)
{
    QFrame::setStyleSheet(styleSheet);

    for(int i = 0; i < m_extruderMap.count(); i++)
    {
        m_extruderMap[i]->setStyleSheet(styleSheet);
        qDebug() << "Setting extruder style";
    }

    QPixmap pixmap = Settings::getThemeIcon(QString("printer")).pixmap(28,28);
    ui->statusIconLabel->setPixmap(pixmap);

    if(m_fileBrowser)
        m_fileBrowser->setStyleSheet(styleSheet);

    if(m_printerOfflineScreen)
        m_printerOfflineScreen->setStyleSheet(styleSheet);

    if(m_printerBedWidget)
        m_printerBedWidget->setStyleSheet(styleSheet);

    ui->zOffsetDownButton->setIcon(Settings::getThemeIcon("move-down-icon"));
    ui->zOffsetUpButton->setIcon(Settings::getThemeIcon("move-up-icon"));

    pixmap = Settings::getThemeIcon(QString("location-icon")).pixmap(18,18);
    ui->positionIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon(QString("height-icon")).pixmap(18,18);
    ui->zOffsetIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon(QString("control-icon")).pixmap(18,18);
    ui->controlIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon(QString("toolhead-icon")).pixmap(28,28);
    ui->toolheadIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon(QString("cooler-icon")).pixmap(28,28);
    ui->fanIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon(QString("webcam-icon")).pixmap(28,28);
    ui->webcamIconLabel->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon(QString("printer-icon")).pixmap(28,28);
    ui->statusIconLabel->setPixmap(pixmap);

    style()->polish(this);
}

void PrinterPage::setupUiClasses()
{
    ui->actionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageActionBar"));
    ui->pageContents->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->tabWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->chamberWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget"));
    ui->toolheadWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget"));
    ui->fanFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget"));
    ui->currentPositionFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));
    ui->zOffsetGroupBox->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));
    ui->toolheadControlGroupBox->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));

    ui->pageOverview->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageOverview"));

    ui->settingsFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget"));
    ui->fileGroupBox->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget"));
    ui->webcamGroupBox->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget"));

    ui->positionTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidgetTitleBar"));
    ui->positionTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    ui->zOffsetTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidgetTitleBar"));
    ui->zOffsetTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    ui->controlTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidgetTitleBar"));
    ui->controlTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    ui->printStatusTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));
    ui->printStatusTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    ui->toolheadTItleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));
    ui->toolheadTItleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    ui->webcamTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));
    ui->webcamTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    ui->fanFrameTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));
    ui->fanFrameTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    ui->zOffsetUpButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ButtonBarLeft"));
    ui->zOffsetUp005->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ButtonBarCenter"));
    ui->zOffsetUp01->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ButtonBarCenter"));
    ui->zOffsetUp025->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ButtonBarCenter"));
    ui->zOffsetUp05->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ButtonBarRight"));

    ui->zOffsetDownButton->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ButtonBarLeft"));
    ui->zOffsetDown005->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ButtonBarCenter"));
    ui->zOffsetDown01->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ButtonBarCenter"));
    ui->zOffsetDown025->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ButtonBarCenter"));
    ui->zOffsetDown05->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ButtonBarRight"));
}

void PrinterPage::addFanLabels(Fan *fan, QString name)
{
    QString formattedName = name;

    if(formattedName.startsWith(QString("controller_fan ")))
    {
        formattedName = formattedName.remove(QString("controller_fan "));
        formattedName.replace(QString("_"), QString(" "));
    }

    if(formattedName.startsWith(QString("heater_fan ")))
    {
        formattedName = formattedName.remove(QString("heater_fan "));
        formattedName.replace(QString("_"), QString(" "));
    }

    QStringList parts = formattedName.split(' ', Qt::SkipEmptyParts);

    for (int i = 0; i < parts.size(); ++i)
        parts[i].replace(0, 1, parts[i][0].toUpper());

    formattedName = parts.join(' ') + QString(":");

    QLabel *nameLabel = new QLabel(ui->fanFrameCentralWidget);
    nameLabel->setProperty("component", name);
    nameLabel->setText(formattedName);

    QLabel *valueLabel = new QLabel(ui->fanFrameCentralWidget);
    valueLabel->setProperty("component", name + QString("_value"));
    valueLabel->setText(QString::number((double)fan->speed() * 100) + QString("%"));

    QLabel *iconLabel = new QLabel(ui->fanFrameCentralWidget);
    iconLabel->setProperty("component", name + QString("_icon"));
    iconLabel->setFixedSize(20,20);
    iconLabel->setPixmap(Settings::getThemeIcon("fan-icon").pixmap(16,16));

    QGridLayout *layout = (QGridLayout*)ui->fanFrameCentralWidget->layout();
    int row = layout->rowCount();

    layout->addWidget(iconLabel, row, 0);
    layout->addWidget(nameLabel, row, 1);
    layout->addWidget(valueLabel, row, 2);
}

bool PrinterPage::animating() const
{
    return m_animating;
}

void PrinterPage::setAnimating(bool animating)
{
    m_animating = animating;

    //_webcamWidget->setProperty("isAnimating", animating);
}

void PrinterPage::on_xPosDecreaseButton_clicked()
{
    QString valueString = ui->posIncrementSelect->currentText();
    valueString.remove(QString("mm"));

    qreal amount = valueString.toDouble();

    m_printer->toolhead()->moveX(amount * -1);
}

void PrinterPage::terminalButtonClickEvent()
{
    ui->tabWidget->setCurrentIndex(1);
    m_overviewButton->setChecked(false);
    m_fileBrowserButton->setChecked(false);
    m_bedMeshViewerButton->setChecked(false);
    m_settingsButton->setChecked(false);
}

void PrinterPage::overviewButtonClickEvent()
{
    ui->tabWidget->setCurrentIndex(0);
    m_webcamWidget->show();

    m_terminalButton->setChecked(false);
    m_fileBrowserButton->setChecked(false);
    m_bedMeshViewerButton->setChecked(false);
    m_settingsButton->setChecked(false);
}

void PrinterPage::fileBrowserButtonClickEvent()
{
    ui->tabWidget->setCurrentIndex(2);
    m_overviewButton->setChecked(false);
    m_terminalButton->setChecked(false);
    m_bedMeshViewerButton->setChecked(false);
    m_settingsButton->setChecked(false);
}

void PrinterPage::bedMeshViewerButtonClickEvent()
{
    ui->tabWidget->setCurrentIndex(3);
    m_overviewButton->setChecked(false);
    m_fileBrowserButton->setChecked(false);
    m_terminalButton->setChecked(false);
    m_settingsButton->setChecked(false);
}

void PrinterPage::settingsButtonClickEvent()
{
    ui->tabWidget->setCurrentIndex(4);
    m_overviewButton->setChecked(false);
    m_fileBrowserButton->setChecked(false);
    m_bedMeshViewerButton->setChecked(false);
    m_terminalButton->setChecked(false);
}

void PrinterPage::on_printerUpdate(Printer *printer)
{

    if(!m_overviewBrowser)
    {
        m_overviewBrowser = new FileBrowser(printer, QString("gcodes"), ui->fileGroupBox, FileBrowser::Widget);
        m_overviewBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        ui->fileGroupBox->layout()->addWidget(m_overviewBrowser);
    }

    if(m_extruderMap.count() < printer->extruderCount())
    {
        for(int i = m_extruderMap.count(); i < printer->extruderCount(); i++)
            addExtruder(printer->extruder(i));
    }

    ui->xLabel->setText(QString("X: ") + QString::number(printer->toolhead()->position().x()));
    ui->yLabel->setText(QString("Y: ") + QString::number(printer->toolhead()->position().y()));
    ui->zLabel->setText(QString("Z: ") + QString::number(printer->toolhead()->position().z()));

    if(!xPosEditing && !ui->xDestinationSpinBox->hasFocus())
        ui->xDestinationSpinBox->setValue((printer->toolhead()->destination().x()));

    if(!yPosEditing && !ui->yDestinationSpinBox->hasFocus())
        ui->yDestinationSpinBox->setValue((printer->toolhead()->destination().y()));

    if(!zPosEditing && !ui->zDestinationSpinBox->hasFocus())
        ui->zDestinationSpinBox->setValue((printer->toolhead()->destination().z()));

    ui->etaLabel->setText(QString("ETA: ") + printer->printEndTime().toString());

    ui->statusMessageLabel->setText(QString(""));

    QString status;
    QPixmap pixmap;

    switch(printer->status())
    {
    case Printer::Ready:
        status = QString("Ready");

        pixmap = Settings::getThemeIcon(QString("printer-ready-icon")).pixmap(28,28);
        ui->statusIconLabel->setPixmap(pixmap);

        ui->restartFirmwareButton->setHidden(true);
        ui->cancelPrintButton->setHidden(true);
        ui->fileLabel->setHidden(true);
        ui->etaLabel->setHidden(true);
        ui->printStatsLine->setHidden(true);
        ui->printSpeedLabel->setHidden(true);
        ui->printSpeedSlider->setHidden(true);
        ui->printSpeedSpacer->changeSize(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding);
        ui->printSpeedSpinBox->setHidden(true);
        ui->printProgress->setHidden(true);

        break;
    case Printer::Error:
        status = QString("Error");

        if(m_printer->statusMessage().contains("\n"))
        {
            QStringList split = m_printer->statusMessage().split(QString("\n"), Qt::SkipEmptyParts);
            status = split.last();

            split.removeLast();
            ui->statusMessageLabel->setText(split.join(QString("\n")));
        }

        ui->restartFirmwareButton->setHidden(false);
        ui->restartFirmwareButton->setEnabled(true);
        ui->cancelPrintButton->setHidden(true);
        ui->fileLabel->setHidden(true);
        ui->etaLabel->setHidden(true);
        ui->printStatsLine->setHidden(true);
        ui->printSpeedLabel->setHidden(true);
        ui->printSpeedSlider->setHidden(true);
        ui->printSpeedSpacer->changeSize(0,0);
        ui->printSpeedSpinBox->setHidden(true);
        ui->printProgress->setHidden(true);

        pixmap = Settings::getThemeIcon(QString("printer-error-icon")).pixmap(28,28);
        ui->statusIconLabel->setPixmap(pixmap);

        ui->restartFirmwareButton->setEnabled(true);
        break;
    case Printer::Cancelled:
        status = QString("Cancelled");
        m_printerOfflineScreen->lower();
        m_printerOfflineScreen->setHidden(true);

        pixmap = Settings::getThemeIcon(QString("printer-cancelled-icon")).pixmap(28,28);
        ui->statusIconLabel->setPixmap(pixmap);
        ui->fileLabel->setHidden(true);
        ui->etaLabel->setHidden(true);
        ui->printStatsLine->setHidden(true);
        ui->printSpeedLabel->setHidden(true);
        ui->printSpeedSlider->setHidden(true);
        ui->printSpeedSpacer->changeSize(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding);
        ui->printSpeedSpinBox->setHidden(true);
        ui->printProgress->setHidden(true);
        break;
    case Printer::Printing:
        status = QString("Printing");
        m_printerOfflineScreen->lower();
        m_printerOfflineScreen->setHidden(true);

        pixmap = Settings::getThemeIcon(QString("printer-printing-icon")).pixmap(28,28);
        ui->statusIconLabel->setPixmap(pixmap);

        ui->restartFirmwareButton->setHidden(true);
        ui->cancelPrintButton->setHidden(false);
        ui->fileLabel->setHidden(false);
        ui->etaLabel->setHidden(false);
        ui->printStatsLine->setHidden(false);
        ui->printSpeedLabel->setHidden(false);
        ui->printSpeedSlider->setHidden(false);
        ui->printSpeedSpacer->changeSize(0,0, QSizePolicy::Expanding, QSizePolicy::Ignored);
        ui->printSpeedSpinBox->setHidden(false);
        ui->printProgress->setHidden(false);

        break;
    case Printer::Paused:
        status = QString("Paused");
        m_printerOfflineScreen->lower();
        m_printerOfflineScreen->setHidden(true);

        pixmap = Settings::getThemeIcon(QString("printer-paused-icon")).pixmap(28,28);
        ui->statusIconLabel->setPixmap(pixmap);
        break;
    case Printer::Offline:
        status = QString("Offline");
        m_printerOfflineScreen->raise();
        m_printerOfflineScreen->setHidden(false);

        pixmap = Settings::getThemeIcon(QString("printer-offline-icon")).pixmap(28,28);
        ui->statusIconLabel->setPixmap(pixmap);

        ui->restartFirmwareButton->setHidden(true);
        ui->cancelPrintButton->setHidden(true);
        ui->fileLabel->setHidden(true);
        ui->etaLabel->setHidden(true);
        ui->printStatsLine->setHidden(true);
        ui->printSpeedLabel->setHidden(true);
        ui->printSpeedSlider->setHidden(true);
        ui->printSpeedSpacer->changeSize(0,0);
        ui->printSpeedSpinBox->setHidden(true);
        ui->printProgress->setHidden(true);
        break;
    default:
        status = QString("Unknown");
        m_printerOfflineScreen->raise();
        m_printerOfflineScreen->setHidden(false);

        pixmap = Settings::getThemeIcon(QString("printer-offline-icon")).pixmap(28,28);
        ui->statusIconLabel->setPixmap(pixmap);

        ui->restartFirmwareButton->setHidden(true);
        ui->cancelPrintButton->setHidden(true);
        ui->fileLabel->setHidden(true);
        ui->etaLabel->setHidden(true);
        ui->printStatsLine->setHidden(true);
        ui->printSpeedLabel->setHidden(true);
        ui->printSpeedSlider->setHidden(true);
        ui->printSpeedSpacer->changeSize(0,0);
        ui->printSpeedSpinBox->setHidden(true);
        ui->printProgress->setHidden(true);
        break;
    }

    if(m_printer->status() != Printer::Error)
        ui->statusMessageLabel->setText(m_printer->statusMessage());

    ui->printerStatusLabel->setText(status);

    if(printer->status() == Printer::Ready)
    {
    }
    else
    {
        setPrintActionsEnabled(false);
    }

    ui->partsFanLabel->setText(QString::number((double)printer->toolhead()->fan()->speed() * 100) + QString("%"));

    QPixmap partFanIcon;

    if(printer->toolhead()->fan()->speed() > 0.00)
        partFanIcon = Settings::getThemeIcon("fan-on-icon").pixmap(16,16);
    else
        partFanIcon = Settings::getThemeIcon("fan-icon").pixmap(16,16);

    ui->partsFanIconLabel->setPixmap(partFanIcon);

    QList<QLabel*> labels = ui->fanFrameCentralWidget->findChildren<QLabel*>();

    QMap<QString, Fan*> printerFans = m_printer->fans();
    QStringList printerFanNames = printerFans.keys();

    foreach(QString name, printerFanNames)
    {
        bool found = false;

        foreach(QLabel *label, labels)
        {
            if(label->property("component").isValid())
            {
                QString componentName = name + QString("_value");
                QString componentIcon = name + QString("_icon");

                if(label->property("component") == componentName)
                {
                    label->setText(QString::number((double)printerFans[name]->speed() * 100) + QString("%"));
                    found = true;
                }
                else if(label->property("component") == componentIcon)
                {
                    QPixmap fanIcon;

                    if(printerFans[name]->speed() > 0.00)
                        fanIcon = Settings::getThemeIcon("fan-on-icon").pixmap(16,16);
                    else
                        fanIcon = Settings::getThemeIcon("fan-icon").pixmap(16,16);

                    label->setPixmap(fanIcon);
                }
            }
        }

        if(!found)
            addFanLabels(printerFans[name], name);
    }

    update();
}

Printer *PrinterPage::printer() const
{
    return m_printer;
}

void PrinterPage::setPrinter(Printer *printer)
{
    if(m_printer)
    {
        disconnect(m_printer, SIGNAL(printerUpdate(Printer*)), this, SLOT(on_printerUpdate(Printer*)));

        QList<QLabel*> labels = ui->fanFrameCentralWidget->findChildren<QLabel*>();

        foreach(QLabel *label, labels)
        {
            if(label->property("component").isValid())
            {
                ui->fanFrameCentralWidget->layout()->removeWidget(label);
                label->deleteLater();
            }
        }
    }

    if(m_printerBedWidget)
        m_printerBedWidget->setPrinterBed(printer->bed());

    m_printer = printer;

    QMap<QString, Fan*> printerFans = m_printer->fans();
    QStringList printerFanNames = printerFans.keys();


    foreach(QString name, printerFanNames)
        addFanLabels(printerFans[name], name);

    connect(m_printer, SIGNAL(printerUpdate(Printer*)), this, SLOT(on_printerUpdate(Printer*)));
    connect(m_printer->console(), SIGNAL(moonrakerDisconnected()), this, SLOT(on_printerUpdate(Printer*)));
    connect(m_printer, SIGNAL(startup(Printer*)), this, SLOT(printerStartupEvent(Printer*)));
}

void PrinterPage::resizeEvent(QResizeEvent *event)
{
    m_printerOfflineScreen->setGeometry(QRect(0,0,width(),height()));
}

void PrinterPage::setPrintActionsEnabled(bool enabled)
{
}

void PrinterPage::showEvent(QShowEvent *event)
{
    //_webcamWidget->show();
    QFrame::showEvent(event);
}

void PrinterPage::hideEvent(QHideEvent *event)
{
    //_webcamWidget->hide();
    QFrame::hideEvent(event);
}

void PrinterPage::on_homeToolheadButton_clicked()
{
    m_printer->console()->sendGcode(QString("G28"));
}

void PrinterPage::on_restartFirmwareButton_clicked()
{
    m_printer->console()->restartFirmware();
    ui->restartFirmwareButton->setEnabled(false);
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

    m_printer->toolhead()->moveX(amount);
}

void PrinterPage::on_yPosDecreaseButton_clicked()
{
    QString valueString = ui->posIncrementSelect->currentText();
    valueString.remove(QString("mm"));

    qreal amount = valueString.toDouble();

    m_printer->toolhead()->moveY(amount * -1);
}

void PrinterPage::on_yPosIncreaseButton_clicked()
{
    QString valueString = ui->posIncrementSelect->currentText();
    valueString.remove(QString("mm"));

    qreal amount = valueString.toDouble();

    m_printer->toolhead()->moveY(amount);
}

void PrinterPage::on_zPosDecreaseButton_clicked()
{
    QString valueString = ui->posIncrementSelect->currentText();
    valueString.remove(QString("mm"));

    qreal amount = valueString.toDouble();

    m_printer->toolhead()->moveZ(amount * -1);
}

void PrinterPage::on_zPosIncreaseButton_clicked()
{
    QString valueString = ui->posIncrementSelect->currentText();
    valueString.remove(QString("mm"));

    qreal amount = valueString.toDouble();

    m_printer->toolhead()->moveZ(amount);
}

void PrinterPage::on_xHomeButton_clicked()
{
    m_printer->toolhead()->homeX();
}

void PrinterPage::on_yHomeButton_clicked()
{
    m_printer->toolhead()->homeY();
}


void PrinterPage::on_zHomeButton_clicked()
{
    m_printer->toolhead()->homeZ();
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
    Position position;
    position.setX(ui->xDestinationSpinBox->value());
    position.setY(ui->yDestinationSpinBox->value());
    position.setZ(ui->zDestinationSpinBox->value());

    if(m_printer->isOnline())
    {
        qDebug() << "Moving toolhead";
        m_printer->toolhead()->setPosition(position);
    }
    else
        qDebug() << "Cannot move toolhead. Printer offline.";
}

void PrinterPage::printerStartupEvent(Printer *printer)
{
    m_printerOfflineScreen->lower();
    m_printerOfflineScreen->setHidden(true);
}

void PrinterPage::printerDisconnectEvent(Printer *printer)
{
    m_printerOfflineScreen->raise();
    m_printerOfflineScreen->setHidden(false);
}

