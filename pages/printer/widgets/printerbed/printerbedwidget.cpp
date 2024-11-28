#include "printerbedwidget.h"
#include "ui_printerbedwidget.h"

#include "../../../../system/settings.h"

PrinterBedWidget::PrinterBedWidget(QKlipperPrintBed *printerBed, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::PrinterBedWidget)
{
    ui->setupUi(this);

    setPrinterBed(printerBed);

    //QGridLayout *layout = new QGridLayout(ui->adjustmentScrewFrame);
    //ui->adjustmentScrewFrame->setLayout(layout);

    m_bedTemperatureBar = new CircularProgressBar(this, CircularProgressBar::Temperature);
    m_bedTemperatureBar->setMaximum(150);

    ui->bedLayout->addWidget(m_bedTemperatureBar);
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Widget" << "PrinterWidget"));
    //ui->toolsWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetSideCard"));
    ui->contentWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetContents"));
    ui->bedInfoWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" << "PrinterSubWidget"));
    //ui->adjustmentScrewFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" << "PrinterSubWidget"));
    ui->titleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WidgetTitleBar" << "PrinterSubWidget"));
    //ui->adjustmentFrameTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidgetTitleBar" << "PrinterSubWidget"));

    ui->settingsTitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidgetTitleBar"));
    ui->settingsTitleBar->setProperty("page", QVariant::fromValue<QStringList>( QStringList() << "PrinterOverview"));
    ui->bedSettingsWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "SubWidget" << "PrinterSubWidget"));

    // m_bedMeshFrame = new BedMeshFrame(m_printerBed, ui->bedMeshContent);
    // ui->bedMeshContent->layout()->addWidget(m_bedMeshFrame);

    // m_adjustmentScrewFrame = new AdjustmentScrewFrame(m_printerBed, ui->adjustmentScrewFrame);
    // ui->adjustmentScrewContent->layout()->addWidget(m_adjustmentScrewFrame);

    //connect(ui->toggleToolsButton, SIGNAL(clicked(bool)), this, SLOT(onToggleToolsButtonClicked(bool)));

    setIcons();
    setupAnimations();
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
    m_bedTemperatureBar->setProgress(m_printerBed->currentTemp());
    ui->bedTemperatureLabel->setText(QString::number(m_printerBed->currentTemp()) + QString("°"));
}

void PrinterBedWidget::onPrintbedTargetTempChanged()
{
    ui->bedTargetTempLabel->setText(QString::number(m_printerBed->targetTemp()) + QString("°"));

    if(!m_targetTempEdited)
        ui->targetTempSpinBox->setValue(m_printerBed->targetTemp());
}

void PrinterBedWidget::onPrintbedPowerChanged()
{
    ui->bedPowerLabel->setText(QString::number(m_printerBed->power()) + QString(""));
}

void PrinterBedWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    // if(m_bedMeshFrame->isVisible() && (m_bedMeshAnimationGroup->state() == QParallelAnimationGroup::Stopped))
    // {
    //     m_bedMeshWidgetHeight = m_bedMeshFrame->height();
    //     m_bedMeshFrameHeight = ui->bedMeshFrame->height();
    // }

    // if(m_adjustmentScrewFrame->isVisible() && (m_adjustmentScrewAnimationGroup->state() == QParallelAnimationGroup::Stopped))
    // {
    //     m_adjustmentScrewFrameHeight = ui->adjustmentScrewFrame->height();
    //     m_adjustmentScrewWidgetHeight = m_adjustmentScrewFrame->height();
    // }
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
    }

    m_printerBed = printerBed;

    connect(m_printerBed, SIGNAL(currentTempChanged()), this, SLOT(onPrintbedCurrentTempChanged()));
    connect(m_printerBed, SIGNAL(targetTempChanged()), this, SLOT(onPrintbedTargetTempChanged()));
    connect(m_printerBed, SIGNAL(powerChanged()), this, SLOT(onPrintbedPowerChanged()));
}

void PrinterBedWidget::setPrintActionsEnabled(bool enabled)
{

}

void PrinterBedWidget::setIcons()
{
    QPixmap pixmap = Settings::getThemeIcon(QString("bed-icon")).pixmap(28,28);
    ui->iconLabel->setPixmap(pixmap);
    pixmap = Settings::getThemeIcon("settings-icon").pixmap(18,18);
    ui->settingsFrameIcon->setPixmap(pixmap);

    pixmap = Settings::getThemeIcon("temperature-icon").pixmap(18,18);
    ui->targetTemperatureIconLabel->setPixmap(pixmap);
}

void PrinterBedWidget::setStyleSheet(const QString &styleSheet)
{
    setIcons();

    QFrame::setStyleSheet(styleSheet);
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

void PrinterBedWidget::onToggleToolsButtonClicked(bool toggled)
{
    if(toggled)
        showAdjustmentScrews();
    else
        hideAdjustmentScrews();
}

void PrinterBedWidget::onToggleBedMeshButtonClicked(bool toggled)
{
    if(toggled)
        showBedMesh();
    else
        hideBedMesh();
}

void PrinterBedWidget::showAdjustmentScrews()
{
    // m_toolsShown = true;
    // int currentFrameHeight = ui->adjustmentFrameTitleBar->height();
    // int currentWidgetHeight = 0;

    // bool isRunning = (m_adjustmentScrewAnimationGroup->state() == QParallelAnimationGroup::Running);

    // if(isRunning)
    // {
    //     m_adjustmentScrewAnimationGroup->pause();
    //     currentFrameHeight = ui->adjustmentScrewFrame->height();
    //     currentWidgetHeight = m_adjustmentScrewFrame->height();
    // }

    // ui->toggleToolsButton->setIcon(Settings::getThemeIcon("collapse-icon"));

    // m_adjustmentScrewFrameAnimation->setStartValue(QRect(ui->adjustmentScrewFrame->x(), ui->adjustmentScrewFrame->y(), ui->adjustmentScrewFrame->width(), currentFrameHeight));
    // m_adjustmentScrewFrameAnimation->setEndValue(QRect(ui->adjustmentScrewFrame->x(), ui->adjustmentScrewFrame->y(), ui->adjustmentScrewFrame->width(), m_adjustmentScrewFrameHeight));

    // m_adjustmentScrewWidgetAnimation->setStartValue(QRect(m_adjustmentScrewFrame->x(), m_adjustmentScrewFrame->y(), m_adjustmentScrewFrame->width(), currentWidgetHeight));
    // m_adjustmentScrewWidgetAnimation->setEndValue(QRect(m_adjustmentScrewFrame->x(), m_adjustmentScrewFrame->y(), m_adjustmentScrewFrame->width(), m_adjustmentScrewWidgetHeight));

    // ui->adjustmentScrewLayout->addWidget(m_adjustmentScrewFrame, 0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);

    // if(isRunning)
    //     m_adjustmentScrewAnimationGroup->resume();
    // else
    //     m_adjustmentScrewAnimationGroup->start();

    // m_adjustmentScrewFrame->setVisible(true);
}

void PrinterBedWidget::hideAdjustmentScrews()
{
    // m_toolsShown = false;
    // int currentFrameHeight = m_adjustmentScrewFrameHeight;
    // int currentWidgetHeight = m_adjustmentScrewWidgetHeight;

    // bool isRunning = (m_adjustmentScrewAnimationGroup->state() == QParallelAnimationGroup::Running);

    // if(isRunning)
    // {
    //     m_adjustmentScrewAnimationGroup->pause();
    //     currentFrameHeight = m_adjustmentScrewFrame->height();
    //     currentWidgetHeight = ui->adjustmentScrewFrame->height();
    // }

    // ui->toggleToolsButton->setIcon(Settings::getThemeIcon("expand-icon"));

    // m_adjustmentScrewFrameAnimation->setStartValue(QRect(ui->adjustmentScrewFrame->x(), ui->adjustmentScrewFrame->y(), ui->adjustmentScrewFrame->width(), currentFrameHeight));
    // m_adjustmentScrewFrameAnimation->setEndValue(QRect(ui->adjustmentScrewFrame->x(), ui->adjustmentScrewFrame->y(), ui->adjustmentScrewFrame->width(), ui->adjustmentFrameTitleBar->height()));

    // m_adjustmentScrewWidgetAnimation->setStartValue(QRect(m_adjustmentScrewFrame->x(), m_adjustmentScrewFrame->y(), m_adjustmentScrewFrame->width(), currentWidgetHeight));
    // m_adjustmentScrewWidgetAnimation->setEndValue(QRect(m_adjustmentScrewFrame->x(), m_adjustmentScrewFrame->y(), m_adjustmentScrewFrame->width(), 0));

    // if(isRunning)
    //     m_adjustmentScrewAnimationGroup->resume();
    // else
    //     m_adjustmentScrewAnimationGroup->start();
}

void PrinterBedWidget::showBedMesh()
{
    // m_bedMeshShown = true;
    // bool isRunning = (m_bedMeshAnimationGroup->state() == QParallelAnimationGroup::Running);

    // if(isRunning)
    //     m_bedMeshAnimationGroup->pause();

    // ui->toggleBedMeshButton->setIcon(Settings::getThemeIcon("collapse-icon"));

    // m_bedMeshWidgetAnimation->setStartValue(QRect(0, 0, 400, 0));
    // m_bedMeshWidgetAnimation->setEndValue(QRect(0, 0, 400, m_bedMeshWidgetHeight));

    // m_bedMeshFrameAnimation->setStartValue(QRect(0, 0, 400, ui->bedMeshTitleBar->height()));
    // m_bedMeshFrameAnimation->setEndValue(QRect(0, 0, 400, m_bedMeshFrameHeight));

    // ui->bedMeshLayout->addWidget(m_bedMeshFrame, 0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);

    // if(isRunning)
    //     m_bedMeshAnimationGroup->resume();
    // else
    //     m_bedMeshAnimationGroup->start();

    // m_bedMeshFrame->setVisible(true);
}

void PrinterBedWidget::hideBedMesh()
{
    // m_bedMeshShown = false;
    // bool isRunning = (m_bedMeshAnimationGroup->state() == QParallelAnimationGroup::Running);

    // if(isRunning)
    //     m_bedMeshAnimationGroup->pause();

    // ui->toggleBedMeshButton->setIcon(Settings::getThemeIcon("collapse-icon"));

    // m_bedMeshWidgetAnimation->setStartValue(QRect(m_bedMeshFrame->x(), m_bedMeshFrame->y(), m_bedMeshFrame->width(), m_bedMeshWidgetHeight));
    // m_bedMeshWidgetAnimation->setEndValue(QRect(m_bedMeshFrame->x(), m_bedMeshFrame->y(), m_bedMeshFrame->width(), 0));

    // m_bedMeshFrameAnimation->setStartValue(QRect(ui->bedMeshFrame->x(), ui->bedMeshFrame->y(), ui->bedMeshFrame->width(), m_bedMeshFrameHeight));
    // m_bedMeshFrameAnimation->setEndValue(QRect(ui->bedMeshFrame->x(), ui->bedMeshFrame->y(), ui->bedMeshFrame->width(), ui->bedMeshTitleBar->height()));

    // if(isRunning)
    //     m_bedMeshAnimationGroup->resume();
    // else
    //     m_bedMeshAnimationGroup->start();
}

void PrinterBedWidget::onToolsWidgetAnimationFinished()
{
    // if(!m_toolsShown)
    // {
    //     ui->adjustmentScrewLayout->removeWidget(m_adjustmentScrewFrame);
    //     //m_adjustmentScrewWidgetHeight = m_adjustmentScrewFrame->height();
    // }

    // m_adjustmentScrewFrame->setHidden(!m_toolsShown);
}

void PrinterBedWidget::onBedMeshAnimationFinished()
{
    // if(!m_bedMeshShown)
    // {
    //     ui->bedMeshLayout->removeWidget(m_bedMeshFrame);
    //     //m_bedMeshWidgetHeight = m_bedMeshFrame->height();
    // }

    // m_bedMeshFrame->setHidden(!m_bedMeshShown);
}

void PrinterBedWidget::setupAnimations()
{
    // m_bedMeshWidgetAnimation = new QPropertyAnimation(m_bedMeshFrame, "geometry");
    // m_bedMeshWidgetAnimation->setDuration(500);
    // m_bedMeshWidgetAnimation->setEasingCurve(QEasingCurve::Linear);

    // m_bedMeshFrameAnimation = new QPropertyAnimation(ui->bedMeshFrame, "geometry");
    // m_bedMeshFrameAnimation->setDuration(500);
    // m_bedMeshFrameAnimation->setEasingCurve(QEasingCurve::Linear);

    // m_bedMeshAnimationGroup = new QParallelAnimationGroup(this);
    // m_bedMeshAnimationGroup->addAnimation(m_bedMeshWidgetAnimation);
    // m_bedMeshAnimationGroup->addAnimation(m_bedMeshFrameAnimation);

    // m_adjustmentScrewWidgetAnimation = new QPropertyAnimation(m_adjustmentScrewFrame, "geometry");
    // m_adjustmentScrewWidgetAnimation->setDuration(500);
    // m_adjustmentScrewWidgetAnimation->setEasingCurve(QEasingCurve::Linear);

    // m_adjustmentScrewFrameAnimation = new QPropertyAnimation(ui->adjustmentScrewFrame, "geometry");
    // m_adjustmentScrewFrameAnimation->setDuration(500);
    // m_adjustmentScrewFrameAnimation->setEasingCurve(QEasingCurve::Linear);

    // m_adjustmentScrewAnimationGroup = new QParallelAnimationGroup(this);
    // m_adjustmentScrewAnimationGroup->addAnimation(m_adjustmentScrewFrameAnimation);
    // m_adjustmentScrewAnimationGroup->addAnimation(m_adjustmentScrewWidgetAnimation);

    // connect(m_bedMeshAnimationGroup, SIGNAL(finished()), this, SLOT(onBedMeshAnimationFinished()));
    // connect(m_adjustmentScrewAnimationGroup, SIGNAL(finished()), this, SLOT(onToolsWidgetAnimationFinished()));
}

