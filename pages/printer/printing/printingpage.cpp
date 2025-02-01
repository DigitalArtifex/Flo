#include "printingpage.h"

#include "flo/settings.h"

PrintingPage::PrintingPage(QKlipperPrinter *printer, QWidget *parent)
    : QFrame{parent}
{
    m_printer = printer;

    setupUI();
    setupIcons();

    initValues();
    setProperty("class", QStringList { "PrintingPage", "Page" });

    connect(m_printer, SIGNAL(currentFileChanged()), this, SLOT(onPrinterFileChanged()));
    connect(m_printer, SIGNAL(printJobChanged()), this, SLOT(onPrintJobChanged()));
    connect(m_printer, SIGNAL(printEndingChanged()), this, SLOT(onPrinterETAChanged()));
    connect(m_printer, SIGNAL(gcodeMoveChanged()), this, SLOT(onPrinterGCodeMoveChanged()));
    connect(m_printer->bed(), SIGNAL(targetTempChanged()), this, SLOT(onBedTargetTemperatureChanged()));
    connect(m_printer->toolhead(), SIGNAL(currentExtruderNameChanged()), this, SLOT(onToolheadCurrentExtruderChanged()));
}

void PrintingPage::setupUI()
{
    m_mainLayout = new QGridLayout(this);
    setLayout(m_mainLayout);

    m_printPreviewPixmap = QPixmap(":/images/ui/filebrowser/no_gcode_thumbnail.png");

    //build info panel
    m_infoWidget = new QWidget(this);
    m_infoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_infoWidget->setProperty("class", QStringList { "PrintPreview", "SubWidget" });
    m_infoLayout = new QHBoxLayout(m_infoWidget);
    m_infoLayout->setContentsMargins(9,9,9,9);
    m_mainLayout->addWidget(m_infoWidget, 0, 1, 3, 1);

    m_printPreviewLabel = new QLabel(m_infoWidget);
    m_printPreviewLabel->setPixmap(m_printPreviewPixmap);
    m_printPreviewLabel->setScaledContents(false);
    m_infoLayout->addWidget(m_printPreviewLabel, 0, Qt::AlignLeft);

    m_infoPanelWidget = new QWidget(this);
    m_infoPanelWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_infoPanelWidget->setProperty("class", QStringList { "Widget" });
    m_infoLabelsLayout = new QVBoxLayout(m_infoPanelWidget);
    m_infoPanelWidget->setLayout(m_infoLabelsLayout);
    m_mainLayout->addWidget(m_infoPanelWidget, 0, 2, 1, 1);

    m_filenameLabel = new QLabel(m_infoWidget);
    m_filenameLabel->setText("Filename: ");
    m_filenameLabel->setProperty("class", QStringList { "PrintInfo" });
    m_filenameLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_infoLabelsLayout->addWidget(m_filenameLabel);

    m_etaLabel = new QLabel(m_infoWidget);
    m_etaLabel->setText("ETA: N/A");
    m_etaLabel->setProperty("class", QStringList { "PrintInfo" });
    m_etaLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_infoLabelsLayout->addWidget(m_etaLabel);

    m_currentLayerLabel = new QLabel(m_infoWidget);
    m_currentLayerLabel->setText("Current Layer: 0");
    m_currentLayerLabel->setProperty("class", QStringList { "PrintInfo" });
    m_currentLayerLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_infoLabelsLayout->addWidget(m_currentLayerLabel);

    m_totalLayerLabel = new QLabel(m_infoWidget);
    m_totalLayerLabel->setText("Total Layers: 0");
    m_totalLayerLabel->setProperty("class", QStringList { "PrintInfo" });
    m_totalLayerLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_infoLabelsLayout->addWidget(m_totalLayerLabel);

    m_extruderTargetTempLabel = new QLabel(m_infoWidget);
    m_extruderTargetTempLabel->setText("Extruder Temperature: 0°C");
    m_extruderTargetTempLabel->setProperty("class", QStringList { "PrintInfo" });
    m_extruderTargetTempLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_infoLabelsLayout->addWidget(m_extruderTargetTempLabel);

    m_bedTargetTempLabel = new QLabel(m_infoWidget);
    m_bedTargetTempLabel->setText("Bed Temperature: 0°C");
    m_bedTargetTempLabel->setProperty("class", QStringList { "PrintInfo" });
    m_bedTargetTempLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_infoLabelsLayout->addWidget(m_bedTargetTempLabel);

    m_messageLabel = new QLabel(m_infoWidget);
    m_messageLabel->setText("");
    m_messageLabel->setProperty("class", QStringList { "PrintInfo" });
    m_messageLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_infoLabelsLayout->addWidget(m_messageLabel);
    m_infoLabelsLayout->addItem(new QSpacerItem(40,40, QSizePolicy::Expanding, QSizePolicy::Expanding));

    //build slider box
    m_sliderBoxFrame = new QFrame(this);
    m_sliderBoxFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_sliderBoxFrame->setProperty("class", QStringList { "SubWidget" });
    m_mainLayout->addWidget(m_sliderBoxFrame, 1, 2);

    m_sliderBoxLayout = new QVBoxLayout(m_sliderBoxFrame);
    m_sliderBoxFrame->setLayout(m_sliderBoxLayout);

    m_printSpeedText = new QLabel(m_sliderBoxFrame);
    m_printSpeedText->setText("Print Speed");
    m_printSpeedText->setProperty("class", QStringList { "PrintInfo" });
    m_sliderBoxLayout->addWidget(m_printSpeedText);

    m_printSpeedSlider = new QSlider(Qt::Orientation::Horizontal, m_sliderBoxFrame);
    m_printSpeedSlider->setMinimum(0);
    m_printSpeedSlider->setMaximum(200);
    m_printSpeedSlider->setValue(100);
    m_sliderBoxLayout->addWidget(m_printSpeedSlider);

    m_extrusionSpeedText = new QLabel(m_sliderBoxFrame);
    m_extrusionSpeedText->setProperty("class", QStringList { "PrintInfo" });
    m_extrusionSpeedText->setText("Extrusion Speed");
    m_sliderBoxLayout->addWidget(m_extrusionSpeedText);

    m_extrusionSpeedSlider = new QSlider(Qt::Orientation::Horizontal, m_sliderBoxFrame);
    m_extrusionSpeedSlider->setMinimum(0);
    m_extrusionSpeedSlider->setMaximum(200);
    m_extrusionSpeedSlider->setValue(100);
    m_sliderBoxLayout->addWidget(m_extrusionSpeedSlider);

    //build button box
    m_buttonBoxWidget = new QWidget(this);
    m_buttonBoxWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_buttonBoxWidget->setProperty("class", QStringList { "SubWidget" });
    m_mainLayout->addWidget(m_buttonBoxWidget, 2, 2);

    m_buttonBoxLayout = new QVBoxLayout(m_buttonBoxWidget);
    m_buttonBoxWidget->setLayout(m_buttonBoxLayout);

    m_cancelPrintButton = new QIconButton(m_buttonBoxWidget);
    m_cancelPrintButton->setFixedHeight(50);
    m_cancelPrintButton->setText("Cancel Print");
    m_cancelPrintButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_cancelPrintButton->setIcon(Settings::getThemeIcon("cancel"));
    m_buttonBoxLayout->addWidget(m_cancelPrintButton);

    m_pausePrintButton = new QIconButton(m_buttonBoxWidget);
    m_pausePrintButton->setFixedHeight(50);
    m_pausePrintButton->setText("Pause Print");
    m_pausePrintButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_pausePrintButton->setIcon(Settings::getThemeIcon("pause"));
    m_buttonBoxLayout->addWidget(m_pausePrintButton);

    //build the status panel
    m_statusWidget = new QFrame(this);
    m_statusWidget->setProperty("class", QStringList {"PrintStatus", "Widget"});

    m_statusLayout = new QGridLayout(m_statusWidget);
    m_statusLayout->setContentsMargins(9,9,9,9);
    m_statusWidget->setLayout(m_statusLayout);

    m_printerWebcam = new PrinterWebcamWidget(qobject_cast<QKlipperInstance*>(m_printer->parent()));
    m_printerWebcam->setFixedWidth(512);
    m_statusLayout->addWidget(m_printerWebcam, 0, 0, 1, 2, Qt::AlignTop);
    m_statusLayout->addItem(new QSpacerItem(40,40, QSizePolicy::Expanding, QSizePolicy::Expanding), 1, 0, 1, 1);

    m_printProgressBar = new QGaugeWidget(m_statusWidget);
    m_printProgressBar->setFixedSize(128,128);
    m_statusLayout->addWidget(m_printProgressBar, 2, 0, 1, 1, Qt::AlignCenter);

    m_materialStatusWidget = new QWidget(m_statusWidget);
    m_materialStatusWidget->setFixedHeight(128);
    m_materialStatusLayout = new QVBoxLayout(m_materialStatusWidget);
    m_materialStatusWidget->setLayout(m_materialStatusLayout);

    m_materialUsedLabel = new QLabel(m_statusWidget);
    m_materialUsedLabel->setText("Material Used: 0g");
    m_materialUsedLabel->setProperty("class", QStringList { "PrintInfo" });
    m_materialUsedLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_materialStatusLayout->addWidget(m_materialUsedLabel);

    m_materialRemainingLabel = new QLabel(m_statusWidget);
    m_materialRemainingLabel->setText("Material Remaining: 0g");
    m_materialRemainingLabel->setProperty("class", QStringList { "PrintInfo" });
    m_materialRemainingLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_materialStatusLayout->addWidget(m_materialRemainingLabel);

    m_materialStatusLayout->addItem(new QSpacerItem(40,40, QSizePolicy::Expanding, QSizePolicy::MinimumExpanding));

    m_statusLayout->addWidget(m_materialStatusWidget, 2, 1, 1, 1);

    m_statusLayout->addItem(new QSpacerItem(40,40, QSizePolicy::Expanding, QSizePolicy::Expanding), 4, 0, 1, 1);

    m_timeRemainingTextLabel = new QLabel(m_statusWidget);
    m_timeRemainingTextLabel->setText("Time Remaining");
    m_timeRemainingTextLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_statusLayout->addWidget(m_timeRemainingTextLabel, 5, 0, 1, 2);

    QFont font(Settings::digitalFontFamily());
    font.setPointSize(14);

    m_timeRemainingLabel = new QLabel(m_statusWidget);
    m_timeRemainingLabel->setFont(font);
    m_timeRemainingLabel->setAlignment(Qt::AlignCenter);
    m_timeRemainingLabel->setText("00:00:00");
    m_timeRemainingLabel->setProperty("class", QStringList { "PrintTimeRemaining", "SubWidget" });
    m_timeRemainingLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_timeRemainingLabel->setMaximumHeight(64);
    m_statusLayout->addWidget(m_timeRemainingLabel, 6, 0, 1, 2);

    m_mainLayout->addWidget(m_statusWidget, 0, 0, 4, 1);

    m_printJobWidget = new PrintJobWidget(qobject_cast<QKlipperInstance*>(m_printer->parent()), this);
    m_printJobWidget->setProperty("class", QStringList { "SubWidget" });
    m_mainLayout->addWidget(m_printJobWidget, 3, 1, 1, 2);

    setProperty("class", "Page");
}

void PrintingPage::setupIcons()
{
    if(m_printProgressBar)
        m_printProgressBar->setAnimatedIcon(Settings::getThemeIconLocation("printing"));
}

void PrintingPage::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setupIcons();

    QFrame::changeEvent(event);
}

void PrintingPage::resizeEvent(QResizeEvent *event)
{
    quint32 thirdHeight = qFloor(height() * .33);
    quint32 quarterWidth = qFloor(width() * .25);

    if(m_printJobWidget)
    {
        m_printJobWidget->setMinimumHeight(256);
        m_printJobWidget->setFixedHeight(thirdHeight);
    }

    if(m_statusWidget)
    {
        m_statusWidget->setFixedWidth(quarterWidth);

        qreal ratio = 9.0/16.0;
        quint32 webcamWidth = m_statusWidget->width() - 18;
        quint32 webcamHeight = qFloor(webcamWidth * ratio);

        m_printerWebcam->setFixedSize(webcamWidth, webcamHeight);
    }

    if(m_infoPanelWidget)
        m_infoPanelWidget->setFixedWidth(quarterWidth);

    if(m_infoWidget)
    {
        m_printPreviewLabel->setPixmap(m_printPreviewPixmap.scaled((quarterWidth * 2), (quarterWidth * 2), Qt::KeepAspectRatio));
        m_infoWidget->setMaximumWidth(quarterWidth * 2);
    }

    QFrame::resizeEvent(event);
}

void PrintingPage::onPrinterETAChanged()
{
    //always has an ETA result, so only display it if the printer is printing
    if(m_printer->status() == QKlipperPrinter::Printing || m_printer->status() == QKlipperPrinter::Paused)
        m_etaLabel->setText(QString("End Time: %1").arg(m_printer->printEnding().toString()));
    else
        m_etaLabel->setText("End Time: N/A");
}

void PrintingPage::onPrinterFileChanged()
{
    if(m_currentFile == m_printer->currentFile())
        return;

    if(m_currentFile)
        disconnect(m_currentFile, SIGNAL(metadataChanged()), this, SLOT(onPrinterFileMetaDataChanged()));

    m_currentFile = m_printer->currentFile();

    if(m_filenameLabel)
        m_filenameLabel->setText(m_currentFile->filename());

    onPrinterFileMetaDataChanged();
    connect(m_currentFile, SIGNAL(metadataChanged()), this, SLOT(onPrinterFileMetaDataChanged()));
}

void PrintingPage::onPrinterFileMetaDataChanged()
{
    QKlipperFile *file = m_printer->currentFile();

    if(!file)
        return;

    if(m_materialRemainingLabel)
        m_materialRemainingLabel->setText(QString("Material Needed: %1mm").arg(QString::number(file->metadata().filamentTotal)));

    if(!m_currentFile->metadata().thumbnails.isEmpty())
    {
        //download and display thumbnail 0
        QByteArray data;
        QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(m_printer->parent());

        if(instance)
        {
            QKlipperError error;
            data = instance->console()->serverFileDownload(m_currentFile->metadata().thumbnails[0].relativePath, &error);

            if(error.type() != QKlipperError::NoError)
            {
                m_printPreviewPixmap = QPixmap(data);
                m_printPreviewLabel->setPixmap(m_printPreviewPixmap);
                return;
            }
        }
    }

    m_printPreviewPixmap = QPixmap(":/images/ui/filebrowser/no_gcode_thumbnail.png");
    m_printPreviewLabel->setPixmap(m_printPreviewPixmap);
}

void PrintingPage::onPrinterGCodeMoveChanged()
{
    if(m_printSpeedSlider)
        m_printSpeedSlider->setValue(m_printer->gcodeMove().speedFactor * 100);
}

void PrintingPage::onPrintJobChanged()
{
    if(m_printJob == m_printer->printJob())
        return;

    if(m_printJob)
    {
        disconnect(m_printJob, SIGNAL(totalLayersChanged()), this, SLOT(onPrintJobTotalLayerChanged()));
        disconnect(m_printJob, SIGNAL(currentLayerChanged()), this, SLOT(onPrintJobCurrentLayerChanged()));
        disconnect(m_printJob, SIGNAL(filamentUsedChanged()), this, SLOT(onPrintJobFilamentUsedChanged()));

        //connect(m_printJob, SIGNAL(), this, SLOT(onPrinterETAChanged()));
    }

    m_printJob = m_printer->printJob();
    connect(m_printJob, SIGNAL(totalLayersChanged()), this, SLOT(onPrintJobTotalLayerChanged()));
    connect(m_printJob, SIGNAL(currentLayerChanged()), this, SLOT(onPrintJobCurrentLayerChanged()));
    connect(m_printJob, SIGNAL(filamentUsedChanged()), this, SLOT(onPrintJobFilamentUsedChanged()));
}

void PrintingPage::onPrintJobCurrentLayerChanged()
{
    if(m_currentLayerLabel)
        m_currentLayerLabel->setText(QString("Current Layer: %1").arg(QString::number(m_printJob->currentLayer())));

    if(m_printProgressBar)
        m_printProgressBar->setValue(m_printJob->currentLayer());
}

void PrintingPage::onPrintJobTotalLayerChanged()
{
    if(m_totalLayerLabel)
        m_totalLayerLabel->setText(QString("Total Layers: %1").arg(QString::number(m_printJob->totalLayers())));

    if(m_printProgressBar)
        m_printProgressBar->setMaximum(m_printJob->totalLayers());
}

void PrintingPage::onPrintJobFilamentUsedChanged()
{
    if(m_materialUsedLabel)
        m_materialUsedLabel->setText(QString("Material Used: %1mm").arg(QString::number(m_printJob->filamentUsed())));
}

void PrintingPage::onExtruderTargetTemperatureChanged()
{
    if(!m_printer->toolhead()->currentExtruder())
        return;

    if(m_extruderTargetTempLabel)
        m_extruderTargetTempLabel->setText(QString("Extruder Temperature: %1°C").arg(QString::number(m_printer->toolhead()->currentExtruder()->targetTemp())));
}

void PrintingPage::onExtruderExtrusionSpeedChanged()
{
    if(!m_printer->toolhead()->currentExtruder())
        return;

    if(m_extrusionSpeedSlider)
        m_extrusionSpeedSlider->setValue(m_currentExtruder->extrusionFactor() * 100);
}

void PrintingPage::onBedTargetTemperatureChanged()
{
    if(m_bedTargetTempLabel)
        m_bedTargetTempLabel->setText(QString("Printbed Temperature: %1°C").arg(QString::number(m_printer->bed()->targetTemp())));
}

void PrintingPage::onToolheadCurrentExtruderChanged()
{
    if(m_currentExtruder == m_printer->toolhead()->currentExtruder())
        return;

    if(m_currentExtruder)
    {
        disconnect(m_currentExtruder, SIGNAL(targetTempChanged()), this, SLOT(onExtruderTargetTemperatureChanged()));
        disconnect(m_currentExtruder, SIGNAL(extrusionFactorChanged()), this, SLOT(onExtruderExtrusionSpeedChanged()));
    }

    m_currentExtruder = m_printer->toolhead()->currentExtruder();

    connect(m_currentExtruder, SIGNAL(targetTempChanged()), this, SLOT(onExtruderTargetTemperatureChanged()));
    connect(m_currentExtruder, SIGNAL(extrusionFactorChanged()), this, SLOT(onExtruderExtrusionSpeedChanged()));
}

void PrintingPage::initValues()
{
    onPrinterETAChanged();
    onPrinterFileChanged();
    onPrinterFileMetaDataChanged();
    onPrinterGCodeMoveChanged();
    onPrintJobChanged();
    onPrintJobCurrentLayerChanged();
    onPrintJobTotalLayerChanged();
    onPrintJobFilamentUsedChanged();
    onExtruderTargetTemperatureChanged();
    onExtruderExtrusionSpeedChanged();
    onBedTargetTemperatureChanged();
    onToolheadCurrentExtruderChanged();
}
