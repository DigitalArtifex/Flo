#include "printerpage.h"
#include "ui_printerpage.h"
#include "../../system/settings.h"

PrinterPage::PrinterPage(QKlipperInstance *instance, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PrinterPage)
{
    ui->setupUi(this);
    m_instance = instance;

    m_toolheadControlFrame = new ToolHeadControlFrame(instance->printer()->toolhead(), ui->controlContents);
    ui->controlContents->layout()->addWidget(m_toolheadControlFrame);

    m_centerLayout = new QFlowLayout(ui->centerWidget);
    m_centerLayout->setContentsMargins(QMargins(0,0,0,0));
    ui->centerWidget->setLayout(m_centerLayout);

    m_chamberTemperatureBar = new CircularProgressBar(this);
    m_printProgressBar = new CircularProgressBar(this);
    ui->printProgressLayout->addWidget(m_printProgressBar);

    ui->chamberTempLayout->addWidget(m_chamberTemperatureBar);
    ui->chamberWidget->setHidden(false);

    ui->tabWidget->setTabVisible(0, false);
    ui->tabWidget->setTabVisible(1, false);
    ui->tabWidget->setTabVisible(2, false);
    ui->tabWidget->setTabVisible(3, false);
    ui->tabWidget->setTabVisible(4, false);
    ui->tabWidget->setCurrentIndex(0);

    m_temperatureWidget = new PrinterTemperatureWidget(m_instance, ui->temperatureWidget);
    ui->temperatureLayout->addWidget(m_temperatureWidget);

    m_centerLayoutBottomSpacer = new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Preferred);
    m_centerLayout->setContentsMargins(9,0,0,0);

    m_terminal = new PrinterTerminal(instance, this);
    m_terminal->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->terminalTab->layout()->addWidget(m_terminal);

    m_fileBrowser = new FileBrowser(instance, QString("gcodes"));
    m_fileBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->gcodeTab->layout()->addWidget(m_fileBrowser);

    m_printerSettingsPage = new PrinterSettingsPage(instance, ui->settingsTab);
    ui->settingsTab->layout()->addWidget(m_printerSettingsPage);

    m_printerOfflineScreen = new PrinterOfflineScreen(instance, this);
    m_printerOfflineScreen->setGeometry(QRect(0,0,width(),height()));
    m_printerOfflineScreen->raise();

    QRegularExpression distanceExpression("\\d+\\.\\d+\\s*", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionValidator *distanceValidator = new QRegularExpressionValidator(distanceExpression);
    ui->posIncrementSelect->setValidator(distanceValidator);

    setPrinter(instance->printer());

    m_printerBedWidget = new PrinterBedWidget(m_printer->bed(), this);
    m_centerLayout->addWidget(m_printerBedWidget);

    m_webcamWidget = new PrinterWebcamWidget(instance, ui->webcamContentWidget);
    ui->webcamContentWidget->layout()->addWidget(m_webcamWidget);

    //Setup action bar buttons
    m_overviewButton = new QIconButton(this);
    m_overviewButton->setFixedSize(250,50);
    m_overviewButton->setText("Overview");
    m_overviewButton->setIcon(Settings::getThemeIcon("add-icon"));
    m_overviewButton->setEnabled(true);
    m_overviewButton->setCheckable(true);
    m_overviewButton->setExclusive(true);
    m_overviewButton->setChecked(true);
    ui->actionBar->layout()->addWidget(m_overviewButton);

    m_terminalButton = new QIconButton(this);
    m_terminalButton->setFixedSize(250,50);
    m_terminalButton->setText("Terminal");
    m_terminalButton->setIcon(Settings::getThemeIcon("add-icon"));
    m_terminalButton->setEnabled(true);
    m_terminalButton->setCheckable(true);
    m_terminalButton->setExclusive(true);
    ui->actionBar->layout()->addWidget(m_terminalButton);

    m_fileBrowserButton = new QIconButton(this);
    m_fileBrowserButton->setFixedSize(250,50);
    m_fileBrowserButton->setText("G-Code Browser");
    m_fileBrowserButton->setIcon(Settings::getThemeIcon("add-icon"));
    m_fileBrowserButton->setEnabled(true);
    m_fileBrowserButton->setCheckable(true);
    m_fileBrowserButton->setExclusive(true);
    ui->actionBar->layout()->addWidget(m_fileBrowserButton);

    m_bedMeshViewerButton = new QIconButton(this);
    m_bedMeshViewerButton->setFixedSize(250,50);
    m_bedMeshViewerButton->setText("Bed Mesh Viewer");
    m_bedMeshViewerButton->setIcon(Settings::getThemeIcon("add-icon"));
    m_bedMeshViewerButton->setEnabled(true);
    m_bedMeshViewerButton->setCheckable(true);
    m_bedMeshViewerButton->setExclusive(true);
    ui->actionBar->layout()->addWidget(m_bedMeshViewerButton);

    m_settingsButton = new QIconButton(this);
    m_settingsButton->setFixedSize(250,50);
    m_settingsButton->setText("Machine Settings");
    m_settingsButton->setIcon(Settings::getThemeIcon("add-icon"));
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
    connect(m_instance, SIGNAL(error(QKlipperInstance*, QKlipperError&)), this, SLOT(onInstanceError(QKlipperInstance*, QKlipperError&)));
    connect(m_instance->printer(), SIGNAL(statusChanged()), this, SLOT(onPrinterStatusChanged()));

    m_statusOverlayFrame = new QFrame(ui->printerStatusContents);
    m_statusLabel = new QLabel(m_statusOverlayFrame);

    m_statusOverlayFrame->setLayout(new QGridLayout(m_statusOverlayFrame));
    m_statusOverlayFrame->layout()->addWidget(m_statusLabel);
    m_statusOverlayFrame->lower();
    m_statusOverlayFrame->setVisible(false);

    setupUiClasses();
    setStyleSheet(Settings::currentTheme());

    setupAnimations();

    connect(ui->toggleFanButton, SIGNAL(clicked(bool)), this, SLOT(onFansToggleButtonClicked(bool)));
    connect(ui->togglePositionButton, SIGNAL(clicked(bool)), this, SLOT(onPositionToggleButtonClicked(bool)));
    connect(ui->toggleZoffsetButton, SIGNAL(clicked(bool)), this, SLOT(onZOffsetToggleButtonClicked(bool)));
    connect(ui->toggleWebcamButton, SIGNAL(clicked(bool)), this, SLOT(onWebcamToggleButtonClicked(bool)));
}

PrinterPage::~PrinterPage()
{
    // m_chamberTemperatureBar->deleteLater();
    // m_fileBrowser->deleteLater();

    // m_terminal->deleteLater();
    // m_printerOfflineScreen->deleteLater();

    delete ui;
}

void PrinterPage::addExtruder(QKlipperExtruder *extruder, QString name)
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
    }

    QPixmap pixmap = Settings::getThemeIcon(QString("printer")).pixmap(28,28);
    ui->statusIconLabel->setPixmap(pixmap);

    if(m_fileBrowser)
        m_fileBrowser->setStyleSheet(styleSheet);

    if(m_printerOfflineScreen)
        m_printerOfflineScreen->setStyleSheet(styleSheet);

    if(m_printerBedWidget)
        m_printerBedWidget->setStyleSheet(styleSheet);

    if(m_webcamWidget)
        m_webcamWidget->setStyleSheet(styleSheet);

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

    m_terminalButton->setIcon(Settings::getThemeIcon(QString("console-icon")));
    m_fileBrowserButton->setIcon(Settings::getThemeIcon(QString("browser-icon")));
    m_bedMeshViewerButton->setIcon(Settings::getThemeIcon(QString("mesh-icon")));
    m_overviewButton->setIcon(Settings::getThemeIcon(QString("overview-icon")));
    m_settingsButton->setIcon(Settings::getThemeIcon(QString("settings-icon")));

    ui->toggleZoffsetButton->setIcon(Settings::getThemeIcon("collapse-icon"));
    ui->toggleChamberButton->setIcon(Settings::getThemeIcon("collapse-icon"));
    ui->toggleFanButton->setIcon(Settings::getThemeIcon("collapse-icon"));
    ui->togglePositionButton->setIcon(Settings::getThemeIcon("collapse-icon"));
    ui->toggleWebcamButton->setIcon(Settings::getThemeIcon("collapse-icon"));
    ui->chamberTemperatureIconLabel->setPixmap(Settings::getThemeIcon("temperature-icon").pixmap(20,20));

    style()->polish(this);
}

void PrinterPage::setupUiClasses()
{
    ui->actionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageActionBar"));
    ui->pageContents->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->tabWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));

    ui->toolheadWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget"));
    ui->fanFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget"));
    ui->currentPositionFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" << "PrinterSubWidget"));
    ui->zOffsetFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" << "PrinterSubWidget"));
    ui->toolheadControlGroupBox->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" << "PrinterSubWidget"));
    m_statusOverlayFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" << "PrinterSubWidget"));

    ui->printJobWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget"));
    ui->printProgressWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" << "PrinterSubWidget"));
    ui->temperatureWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget"));
    ui->webcamGroupBox->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget"));

    ui->positionTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidgetTitleBar"));
    ui->positionTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));

    ui->chamberTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar"));
    ui->chamberWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget"));
    ui->chamberStatusWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" << "PrinterSubWidget"));

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

void PrinterPage::addFanLabels(QKlipperFan *fan, QString name)
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

QKlipperPrinter *PrinterPage::printer() const
{
    return m_printer;
}

void PrinterPage::setPrinter(QKlipperPrinter *printer)
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

    QMap<QString, QKlipperFan*> printerFans = m_printer->fans();
    QStringList printerFanNames = printerFans.keys();

    foreach(QString name, printerFanNames)
        addFanLabels(printerFans[name], name);

    connect(m_printer, SIGNAL(statusChanged()), this, SLOT(onPrinterStatusChanged()));
    connect(m_printer, SIGNAL(statusMessageChanged()), this, SLOT(onPrinterStatusMessageChanged()));
    connect(m_printer, SIGNAL(fansChanged()), this, SLOT(onPrinterFansChanged()));
    connect(m_printer, SIGNAL(printEndingChanged()), this, SLOT(onPrinterEndingTimeChanged()));
    connect(m_printer->toolhead(), SIGNAL(extruderMapChanged()), this, SLOT(onToolHeadExtrudersChanged()));
    connect(m_printer->toolhead(), SIGNAL(positionChanged()), this, SLOT(onToolheadPositionChanged()));
    connect(m_printer->toolhead(), SIGNAL(destinationChanged()), this, SLOT(onToolHeadDestinationChanged()));
    connect(m_printer->toolhead()->partsFan(), SIGNAL(speedChanged()), this, SLOT(onToolHeadPartsFanSpeedChanged()));

    onToolHeadExtrudersChanged();
}

void PrinterPage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if(m_printerOfflineScreen)
        m_printerOfflineScreen->setGeometry(QRect(0,0,width(),height()));

    //set expanded size for animations
    if(ui->fanFrameCentralWidget->isVisible() && (m_fansAnimationGroup->state() == QParallelAnimationGroup::Stopped))
    {
        m_fansFrameHeight = ui->fanFrame->height();
        m_fansWidgetHeight = ui->fanFrameCentralWidget->height();
    }

    if(ui->currentPositionContentWidget->isVisible() && (m_positionAnimationGroup->state() == QParallelAnimationGroup::Stopped))
    {
        m_positionFrameHeight = ui->currentPositionFrame->height();
        m_positionWidgetHeight = ui->currentPositionContentWidget->height();
    }

    if(ui->zOffsetContentWidget->isVisible() && (m_zOffsetAnimationGroup->state() == QParallelAnimationGroup::Stopped))
    {
        m_zOffsetFrameHeight = ui->zOffsetFrame->height();
        m_zOffsetWidgetHeight = ui->zOffsetContentWidget->height();
    }

    if(ui->webcamGroupBox->isVisible() && (m_webcamAnimationGroup->state() == QParallelAnimationGroup::Stopped))
    {
        m_webcamFrameHeight = ui->webcamGroupBox->height();
        m_webcamWidgetHeight = ui->webcamContentWidget->height();
    }
}

void PrinterPage::setPrintActionsEnabled(bool enabled)
{
    ui->webcamGroupBox->setEnabled(enabled);
    ui->chamberWidget->setEnabled(enabled);
    ui->temperatureWidget->setEnabled(enabled);
    ui->toolheadWidget->setEnabled(enabled);
    ui->centerWidget->setEnabled(enabled);
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

void PrinterPage::setupAnimations()
{
    m_positionWidgetAnimation = new QPropertyAnimation(ui->currentPositionContentWidget, "geometry");
    m_positionWidgetAnimation->setDuration(500);
    m_positionWidgetAnimation->setEasingCurve(QEasingCurve::Linear);

    m_positionFrameAnimation = new QPropertyAnimation(ui->currentPositionFrame, "geometry");
    m_positionFrameAnimation->setDuration(500);
    m_positionFrameAnimation->setEasingCurve(QEasingCurve::Linear);

    m_positionAnimationGroup = new QParallelAnimationGroup(this);
    m_positionAnimationGroup->addAnimation(m_positionWidgetAnimation);
    m_positionAnimationGroup->addAnimation(m_positionFrameAnimation);

    m_fansWidgetAnimation = new QPropertyAnimation(ui->fanFrameCentralWidget, "geometry");
    m_fansWidgetAnimation->setDuration(500);
    m_fansWidgetAnimation->setEasingCurve(QEasingCurve::Linear);

    m_fansFrameAnimation = new QPropertyAnimation(ui->fanFrame, "geometry");
    m_fansFrameAnimation->setDuration(500);
    m_fansFrameAnimation->setEasingCurve(QEasingCurve::Linear);

    m_fansAnimationGroup = new QParallelAnimationGroup(this);
    m_fansAnimationGroup->addAnimation(m_fansFrameAnimation);
    m_fansAnimationGroup->addAnimation(m_fansWidgetAnimation);

    m_zOffsetWidgetAnimation = new QPropertyAnimation(ui->zOffsetContentWidget, "geometry");
    m_zOffsetWidgetAnimation->setDuration(500);
    m_zOffsetWidgetAnimation->setEasingCurve(QEasingCurve::Linear);

    m_zOffsetFrameAnimation = new QPropertyAnimation(ui->zOffsetFrame, "geometry");
    m_zOffsetFrameAnimation->setDuration(500);
    m_zOffsetFrameAnimation->setEasingCurve(QEasingCurve::Linear);

    m_zOffsetAnimationGroup = new QParallelAnimationGroup(this);
    m_zOffsetAnimationGroup->addAnimation(m_zOffsetFrameAnimation);
    m_zOffsetAnimationGroup->addAnimation(m_zOffsetWidgetAnimation);

    m_webcamWidgetAnimation = new QPropertyAnimation(ui->webcamContentWidget, "geometry");
    m_webcamWidgetAnimation->setDuration(500);
    m_webcamWidgetAnimation->setEasingCurve(QEasingCurve::Linear);

    m_webcamFrameAnimation = new QPropertyAnimation(ui->webcamGroupBox, "geometry");
    m_webcamFrameAnimation->setDuration(500);
    m_webcamFrameAnimation->setEasingCurve(QEasingCurve::Linear);

    m_webcamAnimationGroup = new QParallelAnimationGroup(this);
    m_webcamAnimationGroup->addAnimation(m_webcamFrameAnimation);
    m_webcamAnimationGroup->addAnimation(m_webcamWidgetAnimation);

    connect(m_positionAnimationGroup, SIGNAL(finished()), this, SLOT(onPositionAnimationFinished()));
    connect(m_fansAnimationGroup, SIGNAL(finished()), this, SLOT(onFansAnimationFinished()));
    connect(m_zOffsetAnimationGroup, SIGNAL(finished()), this, SLOT(onZOffsetAnimationFinished()));
    connect(m_webcamAnimationGroup, SIGNAL(finished()), this, SLOT(onWebcamAnimationFinished()));
}

void PrinterPage::showFansWidget()
{
    m_fansShown = true;
    int currentFrameHeight = ui->fanFrameTitleBar->height();
    int currentWidgetHeight = 0;

    bool isRunning = (m_fansAnimationGroup->state() == QParallelAnimationGroup::Running);

    if(isRunning)
    {
        m_fansAnimationGroup->pause();
        currentFrameHeight = ui->fanFrame->height();
        currentWidgetHeight = ui->fanFrameCentralWidget->height();
    }

    ui->toggleFanButton->setIcon(Settings::getThemeIcon("collapse-icon"));

    m_fansFrameAnimation->setStartValue(
        QRect(ui->fanFrame->x(),
              ui->fanFrame->y(),
              ui->fanFrame->width(),
              currentFrameHeight
          )
    );

    m_fansFrameAnimation->setEndValue(
        QRect(
            ui->fanFrame->x(),
            ui->fanFrame->y(),
            ui->fanFrame->width(),
            m_fansFrameHeight
        )
    );

    m_fansWidgetAnimation->setStartValue(
        QRect(
            ui->fanFrameCentralWidget->x(),
            ui->fanFrameCentralWidget->y(),
            ui->fanFrameCentralWidget->width(),
            currentWidgetHeight
        )
    );

    m_fansWidgetAnimation->setEndValue(
        QRect(
            ui->fanFrameCentralWidget->x(),
            ui->fanFrameCentralWidget->y(),
            ui->fanFrameCentralWidget->width(),
            m_fansWidgetHeight
        )
    );

    ui->fanFrameLayout->addWidget(ui->fanFrameCentralWidget, 2, 0, 1, 2);

    if(isRunning)
        m_fansAnimationGroup->resume();
    else
        m_fansAnimationGroup->start();

    ui->fanFrameCentralWidget->setVisible(true);
}

void PrinterPage::hideFansWidget()
{
    m_fansShown = false;
    int currentFrameHeight = ui->fanFrameTitleBar->height();
    int currentWidgetHeight = 0;

    bool isRunning = (m_fansAnimationGroup->state() == QParallelAnimationGroup::Running);

    if(isRunning)
    {
        m_fansAnimationGroup->pause();
        currentFrameHeight = ui->fanFrame->height();
        currentWidgetHeight = ui->fanFrameCentralWidget->height();
    }
    else
    {
        m_fansFrameHeight = currentFrameHeight = ui->fanFrame->height();
        m_fansWidgetHeight = currentWidgetHeight = ui->fanFrameCentralWidget->height();
    }

    ui->toggleFanButton->setIcon(Settings::getThemeIcon("expand-icon"));

    m_fansFrameAnimation->setStartValue(
        QRect(ui->fanFrame->x(),
              ui->fanFrame->y(),
              ui->fanFrame->width(),
              currentFrameHeight
              )
        );

    m_fansFrameAnimation->setEndValue(
        QRect(
            ui->fanFrame->x(),
            ui->fanFrame->y(),
            ui->fanFrame->width(),
            ui->fanFrameTitleBar->height()
            )
        );

    m_fansWidgetAnimation->setStartValue(
        QRect(
            ui->fanFrameCentralWidget->x(),
            ui->fanFrameCentralWidget->y(),
            ui->fanFrameCentralWidget->width(),
            currentWidgetHeight
            )
        );

    m_fansWidgetAnimation->setEndValue(
        QRect(
            ui->fanFrameCentralWidget->x(),
            ui->fanFrameCentralWidget->y(),
            ui->fanFrameCentralWidget->width(),
            0
            )
        );

    if(isRunning)
        m_fansAnimationGroup->resume();
    else
        m_fansAnimationGroup->start();
}

void PrinterPage::showPositionWidget()
{
    m_positionShown = true;
    int currentFrameHeight = ui->positionTitleBar->height();
    int currentWidgetHeight = 0;

    bool isRunning = (m_positionAnimationGroup->state() == QParallelAnimationGroup::Running);

    if(isRunning)
    {
        m_positionAnimationGroup->pause();
        currentFrameHeight = ui->currentPositionFrame->height();
        currentWidgetHeight = ui->currentPositionContentWidget->height();
    }

    ui->toggleFanButton->setIcon(Settings::getThemeIcon("collapse-icon"));

    m_positionFrameAnimation->setStartValue(
        QRect(ui->currentPositionFrame->x(),
              ui->currentPositionFrame->y(),
              ui->currentPositionFrame->width(),
              currentFrameHeight
              )
        );

    m_positionFrameAnimation->setEndValue(
        QRect(
            ui->currentPositionFrame->x(),
            ui->currentPositionFrame->y(),
            ui->currentPositionFrame->width(),
            m_positionFrameHeight
            )
        );

    m_positionWidgetAnimation->setStartValue(
        QRect(
            ui->currentPositionContentWidget->x(),
            ui->currentPositionContentWidget->y(),
            ui->currentPositionContentWidget->width(),
            currentWidgetHeight
            )
        );

    m_positionWidgetAnimation->setEndValue(
        QRect(
            ui->currentPositionContentWidget->x(),
            ui->currentPositionContentWidget->y(),
            ui->currentPositionContentWidget->width(),
            m_positionWidgetHeight
            )
        );

    ui->currentPositionLayout->addWidget(ui->currentPositionContentWidget, 2, 0, 1, 2);

    if(isRunning)
        m_positionAnimationGroup->resume();
    else
        m_positionAnimationGroup->start();

    ui->currentPositionContentWidget->setVisible(true);
}

void PrinterPage::hidePositionWidget()
{
    m_positionShown = false;
    int currentFrameHeight = 0;
    int currentWidgetHeight = 0;

    bool isRunning = (m_positionAnimationGroup->state() == QParallelAnimationGroup::Running);

    if(isRunning)
    {
        m_positionAnimationGroup->pause();
        currentFrameHeight = ui->currentPositionFrame->height();
        currentWidgetHeight = ui->currentPositionContentWidget->height();
    }
    else
    {
        m_positionFrameHeight = currentFrameHeight = ui->currentPositionFrame->height();
        m_positionWidgetHeight = currentWidgetHeight = ui->currentPositionContentWidget->height();
    }

    ui->toggleFanButton->setIcon(Settings::getThemeIcon("expand-icon"));

    m_positionFrameAnimation->setStartValue(
        QRect(ui->currentPositionFrame->x(),
              ui->currentPositionFrame->y(),
              ui->currentPositionFrame->width(),
              currentFrameHeight
              )
        );

    m_positionFrameAnimation->setEndValue(
        QRect(
            ui->currentPositionFrame->x(),
            ui->currentPositionFrame->y(),
            ui->currentPositionFrame->width(),
            ui->positionTitleBar->height()
            )
        );

    m_positionWidgetAnimation->setStartValue(
        QRect(
            ui->currentPositionContentWidget->x(),
            ui->currentPositionContentWidget->y(),
            ui->currentPositionContentWidget->width(),
            currentWidgetHeight
            )
        );

    m_positionWidgetAnimation->setEndValue(
        QRect(
            ui->currentPositionContentWidget->x(),
            ui->currentPositionContentWidget->y(),
            ui->currentPositionContentWidget->width(),
            0
            )
        );

    if(isRunning)
        m_positionAnimationGroup->resume();
    else
        m_positionAnimationGroup->start();
}

void PrinterPage::showZOffsetWidget()
{
    m_zOffsetShown = true;
    int currentFrameHeight = ui->zOffsetTitleBar->height();
    int currentWidgetHeight = 0;

    bool isRunning = (m_zOffsetAnimationGroup->state() == QParallelAnimationGroup::Running);

    if(isRunning)
    {
        m_zOffsetAnimationGroup->pause();
        currentFrameHeight = ui->zOffsetFrame->height();
        currentWidgetHeight = ui->zOffsetContentWidget->height();
    }

    ui->toggleZoffsetButton->setIcon(Settings::getThemeIcon("collapse-icon"));

    m_zOffsetFrameAnimation->setStartValue(
        QRect(ui->zOffsetFrame->x(),
              ui->zOffsetFrame->y(),
              ui->zOffsetFrame->width(),
              currentFrameHeight
              )
        );

    m_zOffsetFrameAnimation->setEndValue(
        QRect(
            ui->zOffsetFrame->x(),
            ui->zOffsetFrame->y(),
            ui->zOffsetFrame->width(),
            m_zOffsetFrameHeight
            )
        );

    m_zOffsetWidgetAnimation->setStartValue(
        QRect(
            ui->zOffsetContentWidget->x(),
            ui->zOffsetContentWidget->y(),
            ui->zOffsetContentWidget->width(),
            currentWidgetHeight
            )
        );

    m_zOffsetWidgetAnimation->setEndValue(
        QRect(
            ui->zOffsetContentWidget->x(),
            ui->zOffsetContentWidget->y(),
            ui->zOffsetContentWidget->width(),
            m_zOffsetWidgetHeight
            )
        );

    ui->zOffsetLayout->addWidget(ui->zOffsetContentWidget, 2, 1, 1, 1);

    if(isRunning)
        m_zOffsetAnimationGroup->resume();
    else
        m_zOffsetAnimationGroup->start();

    ui->zOffsetContentWidget->setVisible(true);
}

void PrinterPage::hideZOffsetWidget()
{
    m_zOffsetShown = false;
    int currentFrameHeight = 0;
    int currentWidgetHeight = 0;

    bool isRunning = (m_zOffsetAnimationGroup->state() == QParallelAnimationGroup::Running);

    if(isRunning)
    {
        m_zOffsetAnimationGroup->pause();
        currentFrameHeight = ui->zOffsetFrame->height();
        currentWidgetHeight = ui->zOffsetContentWidget->height();
    }
    else
    {
        m_zOffsetFrameHeight = currentFrameHeight = ui->zOffsetFrame->height();
        m_zOffsetWidgetHeight = currentWidgetHeight = ui->zOffsetContentWidget->height();
    }

    ui->toggleZoffsetButton->setIcon(Settings::getThemeIcon("expand-icon"));

    m_zOffsetFrameAnimation->setStartValue(
        QRect(ui->zOffsetFrame->x(),
              ui->zOffsetFrame->y(),
              ui->zOffsetFrame->width(),
              currentFrameHeight
              )
        );

    m_zOffsetFrameAnimation->setEndValue(
        QRect(
            ui->zOffsetFrame->x(),
            ui->zOffsetFrame->y(),
            ui->zOffsetFrame->width(),
            ui->zOffsetTitleBar->height()
            )
        );

    m_zOffsetWidgetAnimation->setStartValue(
        QRect(
            ui->zOffsetContentWidget->x(),
            ui->zOffsetContentWidget->y(),
            ui->zOffsetContentWidget->width(),
            currentWidgetHeight
            )
        );

    m_zOffsetWidgetAnimation->setEndValue(
        QRect(
            ui->zOffsetContentWidget->x(),
            ui->zOffsetContentWidget->y(),
            ui->zOffsetContentWidget->width(),
            0
            )
        );

    if(isRunning)
        m_zOffsetAnimationGroup->resume();
    else
        m_zOffsetAnimationGroup->start();
}

void PrinterPage::showWebcamWidget()
{
    m_webcamShown = true;
    int currentFrameHeight = ui->webcamTitleBar->height();
    int currentWidgetHeight = 0;

    bool isRunning = (m_webcamAnimationGroup->state() == QParallelAnimationGroup::Running);

    if(isRunning)
    {
        m_webcamAnimationGroup->pause();
        currentFrameHeight = ui->webcamGroupBox->height();
        currentWidgetHeight = ui->webcamContentWidget->height();
    }

    ui->toggleWebcamButton->setIcon(Settings::getThemeIcon("collapse-icon"));

    m_webcamFrameAnimation->setStartValue(
        QRect(ui->webcamGroupBox->x(),
              ui->webcamGroupBox->y(),
              ui->webcamGroupBox->width(),
              currentFrameHeight
              )
        );

    m_webcamFrameAnimation->setEndValue(
        QRect(
            ui->webcamGroupBox->x(),
            ui->webcamGroupBox->y(),
            ui->webcamGroupBox->width(),
            m_webcamFrameHeight
            )
        );

    m_webcamWidgetAnimation->setStartValue(
        QRect(
            ui->webcamContentWidget->x(),
            ui->webcamContentWidget->y(),
            ui->webcamContentWidget->width(),
            currentWidgetHeight
            )
        );

    m_webcamWidgetAnimation->setEndValue(
        QRect(
            ui->webcamContentWidget->x(),
            ui->webcamContentWidget->y(),
            ui->webcamContentWidget->width(),
            m_webcamWidgetHeight
            )
        );

    ui->webcamLayout->addWidget(ui->webcamContentWidget, 2, 0, 1, 1);

    if(isRunning)
        m_webcamAnimationGroup->resume();
    else
        m_webcamAnimationGroup->start();

    ui->webcamContentWidget->setVisible(true);
}

void PrinterPage::hideWebcamWidget()
{
    m_webcamShown = false;
    int currentFrameHeight = 0;
    int currentWidgetHeight = 0;

    bool isRunning = (m_webcamAnimationGroup->state() == QParallelAnimationGroup::Running);

    if(isRunning)
    {
        m_webcamAnimationGroup->pause();
        currentFrameHeight = ui->webcamGroupBox->height();
        currentWidgetHeight = ui->webcamContentWidget->height();
    }
    else
    {
        m_webcamFrameHeight = currentFrameHeight = ui->webcamGroupBox->height();
        m_webcamWidgetHeight = currentWidgetHeight = ui->webcamContentWidget->height();
    }

    ui->toggleWebcamButton->setIcon(Settings::getThemeIcon("expand-icon"));

    m_webcamFrameAnimation->setStartValue(
        QRect(ui->webcamGroupBox->x(),
              ui->webcamGroupBox->y(),
              ui->webcamGroupBox->width(),
              currentFrameHeight
              )
        );

    m_webcamFrameAnimation->setEndValue(
        QRect(
            ui->webcamGroupBox->x(),
            ui->webcamGroupBox->y(),
            ui->webcamGroupBox->width(),
            ui->webcamTitleBar->height()
            )
        );

    m_webcamWidgetAnimation->setStartValue(
        QRect(
            ui->webcamContentWidget->x(),
            ui->webcamContentWidget->y(),
            ui->webcamContentWidget->width(),
            currentWidgetHeight
            )
        );

    m_webcamWidgetAnimation->setEndValue(
        QRect(
            ui->webcamContentWidget->x(),
            ui->webcamContentWidget->y(),
            ui->webcamContentWidget->width(),
            0
            )
        );

    if(isRunning)
        m_webcamAnimationGroup->resume();
    else
        m_webcamAnimationGroup->start();
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
    QColor color;

    switch(m_printer->status())
    {
    case QKlipperPrinter::Ready:
        status = QString("Ready");

        pixmap = Settings::getThemeIcon(QString("printer-icon")).pixmap(28,28);
        ui->statusIconLabel->setPixmap(pixmap);

        ui->cancelPrintButton->setEnabled(false);
        ui->printSpeedSlider->setEnabled(false);
        ui->printSpeedSpinBox->setEnabled(false);

        setPrintActionsEnabled(true);
        m_statusOverlayFrame->lower();
        m_statusOverlayFrame->setVisible(false);
        break;
    case QKlipperPrinter::Error:
        status = QString("Error");

        if(m_printer->statusMessage().contains("\n"))
        {
            QStringList split = m_printer->statusMessage().split(QString("\n"), Qt::SkipEmptyParts);
            status = split.last();
        }

        color = QColor::fromString(Settings::get("theme/icon-error-color").toString());

        pixmap = Settings::getThemeIcon(QString("printer-icon"), color).pixmap(28,28);
        ui->statusIconLabel->setPixmap(pixmap);

        ui->cancelPrintButton->setEnabled(false);
        ui->printSpeedSlider->setEnabled(false);
        ui->printSpeedSpinBox->setEnabled(false);

        setPrintActionsEnabled(false);

        m_statusOverlayFrame->resize(ui->printerStatusContents->size());
        m_statusOverlayFrame->raise();
        m_statusOverlayFrame->setVisible(true);
        break;
    case QKlipperPrinter::Cancelled:
        status = QString("Cancelled");
        m_printerOfflineScreen->lower();
        m_printerOfflineScreen->setHidden(true);

        ui->cancelPrintButton->setEnabled(false);
        ui->printSpeedSlider->setEnabled(false);
        ui->printSpeedSpinBox->setEnabled(false);

        setPrintActionsEnabled(true);

        m_statusOverlayFrame->lower();
        m_statusOverlayFrame->setVisible(false);
        break;
    case QKlipperPrinter::Printing:
        status = QString("Printing");
        m_printerOfflineScreen->lower();
        m_printerOfflineScreen->setHidden(true);

        color = QColor::fromString(Settings::get("theme/icon-warning-color").toString());

        pixmap = Settings::getThemeIcon(QString("printer-icon"), color).pixmap(28,28);
        ui->statusIconLabel->setPixmap(pixmap);

        ui->cancelPrintButton->setEnabled(true);
        ui->printSpeedSlider->setEnabled(true);
        ui->printSpeedSpinBox->setEnabled(true);

        setPrintActionsEnabled(false);
        m_statusOverlayFrame->lower();
        m_statusOverlayFrame->setVisible(false);
        break;
    case QKlipperPrinter::Paused:
        status = QString("Paused");
        m_printerOfflineScreen->lower();
        m_printerOfflineScreen->setHidden(true);

        color = QColor::fromString(Settings::get("theme/icon-warning-color").toString());

        pixmap = Settings::getThemeIcon(QString("printer-icon"), color).pixmap(28,28);
        ui->statusIconLabel->setPixmap(pixmap);

        ui->cancelPrintButton->setEnabled(true);
        ui->printSpeedSlider->setEnabled(true);
        ui->printSpeedSpinBox->setEnabled(true);

        setPrintActionsEnabled(true);
        m_statusOverlayFrame->lower();
        m_statusOverlayFrame->setVisible(false);
        break;
    case QKlipperPrinter::Offline:
        status = QString("Offline");
        m_printerOfflineScreen->raise();
        m_printerOfflineScreen->setHidden(false);

        color = QColor::fromString(Settings::get("theme/icon-disabled-color").toString());

        pixmap = Settings::getThemeIcon(QString("printer-icon"), color).pixmap(28,28);
        ui->statusIconLabel->setPixmap(pixmap);

        ui->cancelPrintButton->setEnabled(false);
        ui->printSpeedSlider->setEnabled(false);
        ui->printSpeedSpinBox->setEnabled(false);

        setPrintActionsEnabled(false);

        m_statusOverlayFrame->resize(ui->printerStatusContents->size());
        m_statusOverlayFrame->raise();
        m_statusOverlayFrame->setVisible(true);
        break;
    default:
        status = QString("Unknown");
        m_printerOfflineScreen->raise();
        m_printerOfflineScreen->setHidden(false);

        color = QColor::fromString(Settings::get("theme/icon-disabled-color").toString());

        pixmap = Settings::getThemeIcon(QString("printer-icon"), color).pixmap(28,28);
        ui->statusIconLabel->setPixmap(pixmap);

        ui->cancelPrintButton->setEnabled(false);
        ui->printSpeedSlider->setEnabled(false);
        ui->printSpeedSpinBox->setEnabled(false);

        setPrintActionsEnabled(false);

        m_statusOverlayFrame->resize(ui->printerStatusContents->size());
        m_statusOverlayFrame->raise();
        m_statusOverlayFrame->setVisible(true);
        break;
    }

    ui->restartButton->setEnabled(true);
}

void PrinterPage::onPrinterStatusMessageChanged()
{
    m_statusLabel->setText(m_printer->statusMessage());
}

void PrinterPage::onPrinterFansChanged()
{
    QPixmap partFanIcon;

    if(m_printer->toolhead()->partsFan()->speed() > 0.00)
        partFanIcon = Settings::getThemeIcon("fan-on-icon").pixmap(16,16);
    else
        partFanIcon = Settings::getThemeIcon("fan-icon").pixmap(16,16);

    ui->partsFanIconLabel->setPixmap(partFanIcon);
    ui->partsFanLabel->setText(QString::number((double)m_printer->toolhead()->partsFan()->speed() * 100) + QString("%"));

    QList<QLabel*> labels = ui->fanFrameCentralWidget->findChildren<QLabel*>();

    QMap<QString, QKlipperFan*> printerFans = m_printer->fans();
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

void PrinterPage::onToolHeadPartsFanSpeedChanged()
{
    ui->partsFanLabel->setText(QString::number((double)m_printer->toolhead()->partsFan()->speed() * 100) + QString("%"));
}

void PrinterPage::onInstanceError(QKlipperInstance *instance, QKlipperError &error)
{
    QMessageBox msgBox;
    msgBox.setText(error.errorTitle() + " (" + instance->name() + ")");
    msgBox.setInformativeText(error.errorString());
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
}

void PrinterPage::onFansAnimationFinished()
{
    if(!m_fansShown)
    {
        ui->fanFrameLayout->removeWidget(ui->fanFrameCentralWidget);
        ui->fanFrameCentralWidget->setVisible(false);
    }
}

void PrinterPage::onPositionAnimationFinished()
{
    if(!m_positionShown)
    {
        ui->currentPositionLayout->removeWidget(ui->currentPositionContentWidget);
        ui->currentPositionContentWidget->setVisible(false);
    }
}

void PrinterPage::onZOffsetAnimationFinished()
{
    if(!m_zOffsetShown)
    {
        ui->zOffsetLayout->removeWidget(ui->zOffsetContentWidget);
        ui->zOffsetContentWidget->setVisible(false);
    }
}

void PrinterPage::onWebcamAnimationFinished()
{
    if(!m_webcamShown)
    {
        ui->webcamLayout->removeWidget(ui->webcamContentWidget);
        ui->webcamContentWidget->setVisible(false);
    }
}

void PrinterPage::onFansToggleButtonClicked(bool toggled)
{
    if(toggled)
        showFansWidget();
    else
        hideFansWidget();
}

void PrinterPage::onPositionToggleButtonClicked(bool toggled)
{
    if(toggled)
        showPositionWidget();
    else
        hidePositionWidget();
}

void PrinterPage::onZOffsetToggleButtonClicked(bool toggled)
{
    if(toggled)
        showZOffsetWidget();
    else
        hideZOffsetWidget();
}

void PrinterPage::onWebcamToggleButtonClicked(bool toggled)
{
    if(toggled)
        showWebcamWidget();
    else
        hideWebcamWidget();
}


void PrinterPage::on_restartButton_clicked()
{
    ui->restartButton->setEnabled(false);
    m_printer->console()->restartFirmware();
}

