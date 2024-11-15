#include "filepreviewwindow.h"

#include "system/settings.h"

FilePreviewWindow::FilePreviewWindow(QKlipperFile *file, QKlipperInstance *instance, QWidget *parent) :
    Dialog(parent)
{
    m_file = file;
    m_instance = instance;

    connect(m_file, SIGNAL(metadataChanged()), this, SLOT(onFileMetaDataChanged()));
    setupUi();

    showLoadingScreen();
    m_instance->console()->serverFilesMetadata(file);
}

FilePreviewWindow::~FilePreviewWindow()
{
    if(m_contentLayout)
        m_contentLayout->deleteLater();

    if(m_contentWidget)
        m_contentWidget->deleteLater();
}

void FilePreviewWindow::setupUi()
{
    //Setup main layout with no margins and spacing
    //Allow that to be controlled in the content and footer layouts
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);
    setLayout(m_layout);

    //Setup content widget
    m_contentWidget = new QWidget(this);
    m_contentLayout = new QGridLayout(m_contentWidget);
    m_contentWidget->setLayout(m_contentLayout);
    m_layout->addWidget(m_contentWidget);

    //setup name label
    m_nameLabel = new QLabel(this);
    m_nameLabel->setText(QString("%1\n").arg(tr(m_file->filename().toStdString().c_str())));
    m_nameLabel->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "DialogHeading"));
    m_contentLayout->addWidget(m_nameLabel, 0, 0, 1, 2);

    //setup thumbnail label
    QPixmap thumbnail(":/images/ui/filebrowser/no_gcode_thumbnail.png");

    m_thumbnailLabel = new QLabel(this);
    m_thumbnailLabel->setFixedSize(300,300);
    m_thumbnailLabel->setScaledContents(true);
    m_thumbnailLabel->setPixmap(thumbnail);
    m_thumbnailLabel->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "Thumbnail"));
    m_contentLayout->addWidget(m_thumbnailLabel, 1, 0, 11, 1);

    //setup top spacer
    m_contentTopSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_contentLayout->addItem(m_contentTopSpacer, 1, 1, 1, 1);

    //setup profile label
    m_FilamentNameLabel = new QLabel(this);
    m_FilamentNameLabel->setText(QString("Profile: ") + QString::number(m_file->metadata().layerHeight));
    m_FilamentNameLabel->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "DialogInfo"));
    m_contentLayout->addWidget(m_FilamentNameLabel, 2, 1, 1, 1);

    //setup nozzle temp label
    m_nozzleTemperatureLabel = new QLabel(this);
    m_nozzleTemperatureLabel->setText(QString("Extruder Temperature: ") + QString::number(m_file->metadata().layerHeight));
    m_nozzleTemperatureLabel->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "DialogInfo"));
    m_contentLayout->addWidget(m_nozzleTemperatureLabel, 3, 1, 1, 1);

    //setup bed temp label
    m_bedTemperatureLabel = new QLabel(this);
    m_bedTemperatureLabel->setText(QString("Bed Temperature: ") + QString::number(m_file->metadata().layerHeight));
    m_bedTemperatureLabel->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "DialogInfo"));
    m_contentLayout->addWidget(m_bedTemperatureLabel, 4, 1, 1, 1);

    //setup layer height label
    m_layerHeightLabel = new QLabel(this);
    m_layerHeightLabel->setText(QString("Layer height: ") + QString::number(m_file->metadata().layerHeight));
    m_layerHeightLabel->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "DialogInfo"));
    m_contentLayout->addWidget(m_layerHeightLabel, 5, 1, 1, 1);

    //setup object height label
    m_objectHeightLabel = new QLabel(this);
    m_objectHeightLabel->setText(QString("Object height: ") + QString::number(m_file->metadata().objectHeight));
    m_objectHeightLabel->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "DialogInfo"));
    m_contentLayout->addWidget(m_objectHeightLabel, 6, 1, 1, 1);

    //setup filament use label
    m_filamentTotalLabel = new QLabel(this);
    m_filamentTotalLabel->setText(QString("Filament Total: %1").arg(m_file->metadata().filamentTotal));
    m_filamentTotalLabel->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "DialogInfo"));
    m_contentLayout->addWidget(m_filamentTotalLabel, 7, 1, 1, 1);

    //setup nozzle diameter label
    m_nozzleDiameterLabel = new QLabel(this);
    m_nozzleDiameterLabel->setText(QString("Nozzle Diameter: %1").arg(m_file->metadata().filamentTotal));
    m_nozzleDiameterLabel->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "DialogInfo"));
    m_contentLayout->addWidget(m_nozzleDiameterLabel, 8, 1, 1, 1);

    //setup estimated time label
    m_estimatedTimeLabel = new QLabel(this);
    m_estimatedTimeLabel->setText(QString("Estimated Print Time: ") + QString::number(m_file->metadata().estimatedTime));
    m_estimatedTimeLabel->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "DialogInfo"));
    m_contentLayout->addWidget(m_estimatedTimeLabel, 9, 1, 1, 1);

    //setup slicer details label
    m_slicerVersionLabel = new QLabel(this);
    m_slicerVersionLabel->setText(QString("%1 (%2)").arg(m_file->metadata().slicer).arg(m_file->metadata().slicerVersion));
    m_slicerVersionLabel->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "DialogInfo"));
    m_contentLayout->addWidget(m_slicerVersionLabel, 10, 1, 1, 1);

    //setup bottom spacer
    m_contentBottomSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_contentLayout->addItem(m_contentBottomSpacer, 11, 1, 1, 1);

    //Setup footer
    m_footerWidget = new QWidget(this);
    m_footerLayout = new QHBoxLayout(m_footerWidget);
    m_layout->addWidget(m_footerWidget);

    m_cancelButton = new QIconButton(this);
    m_cancelButton->setIcon(Settings::getThemeIcon(QString("cancel-icon")));
    m_cancelButton->setText(QString("Cancel"));
    m_cancelButton->setFixedHeight(50);
    m_cancelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_footerLayout->addWidget(m_cancelButton);

    m_applyButton = new QIconButton(this);
    m_applyButton->setIcon(Settings::getThemeIcon(QString("print-icon")));
    m_applyButton->setText(QString("Print"));
    m_applyButton->setFixedHeight(50);
    m_applyButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_footerLayout->addWidget(m_applyButton);

    connect(m_applyButton, SIGNAL(clicked()), this, SLOT(applyButtonClickEvent()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClickEvent()));
}

void FilePreviewWindow::setStyleSheet(QString &styleSheet)
{
    QDialog::setStyleSheet(styleSheet);

    if(m_applyButton)
        m_applyButton->setStyleSheet(styleSheet);

    if(m_cancelButton)
        m_cancelButton->setStyleSheet(styleSheet);

    style()->polish(this);
}

void FilePreviewWindow::applyButtonClickEvent()
{
    done(QDialog::Accepted);
}

void FilePreviewWindow::cancelButtonClickEvent()
{
    done(QDialog::Rejected);
}

void FilePreviewWindow::onFileMetaDataChanged()
{
    //Filename is stored without the path data
    QString name;

    if(!m_file->path().isEmpty())
        name = QString("%1/%2").arg(m_file->path()).arg(m_file->filename());
    else
        name = QString("%1").arg(m_file->filename());

    if(!m_file->metadata().thumbnails.isEmpty())
    {
        QString url = m_instance->system()->hostname() + QString("/");
        url += m_file->metadata().thumbnails[0].relativePath;

        QPixmap pixmap(url);

        if(m_thumbnailLabel)
            m_thumbnailLabel->setPixmap(url);
    }

    if(m_layerHeightLabel)
        m_layerHeightLabel->setText(QString("Layer height:    %1 mm").arg(m_file->metadata().layerHeight));

    if(m_objectHeightLabel)
        m_objectHeightLabel->setText(QString("Object height:    %1 mm").arg(m_file->metadata().objectHeight));

    if(m_FilamentNameLabel)
        m_FilamentNameLabel->setText(QString("Profile:    %1").arg(m_file->metadata().filamentName));

    if(m_bedTemperatureLabel)
        m_bedTemperatureLabel->setText(QString("Bed Temperature:    %1 C").arg(m_file->metadata().firstLayerBedTemp));

    if(m_nozzleTemperatureLabel)
        m_nozzleTemperatureLabel->setText(QString("Extruder Temperature:    %1 C").arg(m_file->metadata().firstLayerExtruderTemp));

    if(m_nozzleDiameterLabel)
        m_nozzleDiameterLabel->setText(QString("Extrusion Diameter:    %1 mm").arg(m_file->metadata().nozzleDiameter));

    if(m_slicerVersionLabel)
        m_slicerVersionLabel->setText(QString("Slicer:    %1 (%2)").arg(m_file->metadata().slicer).arg(m_file->metadata().slicerVersion));

    if(m_filamentTotalLabel)
    {
        qreal total = m_file->metadata().filamentTotal;
        qreal weight = m_file->metadata().filamentTotalWeight;
        QString unit("mm");
        QString weightUnit("g");

        if(total > 1000)
        {
            total /= 1000;
            unit = QString("m");

            if(total > 1000)
            {
                total /= 1000;
                unit = QString("km");
            }
        }

        if(weight > 1000)
        {
            weight /= 1000;
            weightUnit = QString("kg");
        }

        m_filamentTotalLabel->setText(QString("Filament Total:    %1 %2 (%3 %4)").arg(total, 0, 'f', 2).arg(unit).arg(weight).arg(weightUnit));
    }

    if(m_estimatedTimeLabel)
    {
        qint64 timeInSeconds = m_file->metadata().estimatedTime;

        const qint64 secondsPerDay = 86400;
        qint64 days = timeInSeconds / secondsPerDay;
        QTime timeSpan = QTime(0,0).addSecs(timeInSeconds % secondsPerDay);

        //Build time label
        QString timeLabel;

        if(days > 0)
        {
            if(days == 1)
                timeLabel += QString("%1 Day, ").arg(days);
            else
                timeLabel += QString("%1 Days, ").arg(days);
        }

        if(timeSpan.hour() > 0)
        {
            if(timeSpan.hour() == 1)
                timeLabel += QString("%1 Hour, ").arg(timeSpan.hour());
            else
                timeLabel += QString("%1 Hours, ").arg(timeSpan.hour());
        }

        if(timeSpan.minute() > 0)
        {
            if(timeSpan.minute() == 1)
                timeLabel += QString("%1 Minute, ").arg(timeSpan.minute());
            else
                timeLabel += QString("%1 Minutes, ").arg(timeSpan.minute());
        }

        if(timeSpan.second() > 0)
        {
            if(timeSpan.second() == 1)
                timeLabel += QString("%1 Second").arg(timeSpan.second());
            else
                timeLabel += QString("%1 Seconds").arg(timeSpan.second());
        }

        if(timeLabel.endsWith(", "))
            timeLabel = timeLabel.mid(0, timeLabel.length() - 2);

        m_estimatedTimeLabel->setText(QString("Estimated Print Time:    ") + timeLabel);
    }

    if(isLoadingScreenVisible())
        hideLoadingScreen();
}

QKlipperFile *FilePreviewWindow::file() const
{
    return m_file;
}
