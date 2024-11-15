#include "bedmeshframe.h"
#include "ui_bedmeshframe.h"

#include "../../../../../system/settings.h"

BedMeshFrame::BedMeshFrame(QKlipperPrintBed *bed, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::BedMeshFrame)
{
    ui->setupUi(this);

    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(4,4,4,4);
    m_layout->setSpacing(4);
    ui->bedMeshFrame->setLayout(m_layout);

    ui->recalibrateButton->setHidden(true);

    m_printerBed = bed;
    connect(m_printerBed, SIGNAL(bedMeshCalibrating()), this, SLOT(onBedMeshCalibrating()));
    connect(m_printerBed, SIGNAL(bedMeshCalibratingFinished()), this, SLOT(onBedMeshCalibratingFinished()));
    connect(m_printerBed->bedMesh(), SIGNAL(matrixChanged()), this, SLOT(onBedMeshCalibratingFinished()));

    connect(m_printerBed->printer()->toolhead(), SIGNAL(homingFinished()), this, SLOT(onToolheadHomed()));
    //connect(m_printerBed->printer()->toolhead(), SIGNAL(isHomedChanged()), this, SLOT(onToolheadHomed()));
    connect(m_printerBed->printer()->toolhead(), SIGNAL(homing()), this, SLOT(onToolheadHoming()));
    setupIcons();
    onBedMeshCalibratingFinished();
}

BedMeshFrame::~BedMeshFrame()
{
    delete ui;
}

void BedMeshFrame::setupIcons()
{
}

void BedMeshFrame::setupUiClasses()
{

}

void BedMeshFrame::showLoadingScreen()
{
    if(m_loadingGif)
    {
        m_loadingGif->deleteLater();
        m_loadingGif = nullptr;
    }

    if(m_loadingLabel)
    {
        m_loadingLabel->deleteLater();
        m_loadingLabel = nullptr;
    }

    if(m_loadingAnimation)
    {
        m_loadingAnimation->deleteLater();
        m_loadingAnimation = nullptr;
    }

    if(m_loadingFrame)
    {
        m_loadingFrame->deleteLater();
        m_loadingFrame = nullptr;
    }

    if(m_loadingFrameLayout)
    {
        m_loadingFrameLayout->deleteLater();
        m_loadingFrameLayout = nullptr;
    }

    m_loadingFrameLayout = new QHBoxLayout(m_loadingFrame);
    m_loadingFrame = new QFrame(this);
    m_loadingFrame->setLayout(m_loadingFrameLayout);
    m_loadingFrame->setMinimumWidth(this->width());
    m_loadingFrame->setMinimumHeight(this->height());
    m_loadingFrame->show();
    m_loadingFrame->raise();

    m_loadingFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "LoadingOverlayFrame"));

    m_loadingGif = new QMovie(":/images/loading_small_1a87c5.gif");

    m_loadingLabel = new QLabel(m_loadingFrame);
    m_loadingLabel->setFixedSize(50,50);
    m_loadingLabel->setScaledContents(true);
    m_loadingLabel->setMovie(m_loadingGif);
    m_loadingFrameLayout->addWidget(m_loadingLabel);

    m_loadingAnimation = new QWidgetAnimation(m_loadingFrame);
    m_loadingAnimation->setDuration(100);
    m_loadingAnimation->setStartOpacity(0);
    m_loadingAnimation->setEndOpacity(1);

    m_loadingGif->start();
    m_loadingAnimation->start();

    this->style()->polish(m_loadingFrame);
}

void BedMeshFrame::hideLoadingScreen()
{
    if(m_loadingGif)
    {
        connect(m_loadingAnimation, SIGNAL(finished()), this, SLOT(on_loadingAnimation_finished()));
        m_loadingAnimation->setStartOpacity(1);
        m_loadingAnimation->setEndOpacity(0);
        m_loadingAnimation->setDuration(100);
        m_loadingAnimation->start();
    }
}

void BedMeshFrame::setStyleSheet(const QString &styleSheet)
{
    setupIcons();

    if(m_emptyFrame)
        m_emptyFrame->setStyleSheet(styleSheet);

    QFrame::setStyleSheet(styleSheet);
}

void BedMeshFrame::on_loadingAnimation_finished()
{
    //m_loadingGif->stop();

    if(m_loadingGif)
    {
        m_loadingGif->deleteLater();
        m_loadingGif = nullptr;
    }

    if(m_loadingLabel)
    {
        m_loadingLabel->deleteLater();
        m_loadingLabel = nullptr;
    }

    if(m_loadingAnimation)
    {
        m_loadingAnimation->deleteLater();
        m_loadingAnimation = nullptr;
    }

    if(m_loadingFrameLayout)
    {
        m_loadingFrameLayout->deleteLater();
        m_loadingFrameLayout = nullptr;
    }

    if(m_loadingFrame)
    {
        m_loadingFrame->deleteLater();
        m_loadingFrame = nullptr;
    }
}

void BedMeshFrame::onToolheadHoming()
{
    setEnabled(false);
}

void BedMeshFrame::onToolheadHomed()
{
    setEnabled(true);
}

void BedMeshFrame::onBedMeshCalibratingFinished()
{
    clearLayout();

    if(m_printerBed->hasBedMeshResult())
    {
        //remove empty frame
        if(m_emptyFrame)
        {
            m_layout->removeWidget(m_emptyFrame);
            m_emptyFrame->deleteLater();
            m_emptyFrame = nullptr;

            //unhide recalibrate ui
            ui->recalibrateButton->setHidden(false);
        }

        foreach(QList<qreal> row, m_printerBed->bedMesh()->probed())
        {
            int rowNumber = m_layout->rowCount();

            for(int i = 0; i < row.count(); i++)
            {

                BedMeshItemFrame *itemFrame = new BedMeshItemFrame(this);
                itemFrame->setValue(row[i]);

                m_layout->addWidget(itemFrame, rowNumber, i, Qt::AlignCenter);
            }
        }
    }

    //show empty frame
    else
    {
        if(!m_emptyFrame)
        {
            m_emptyFrame = new BedMeshEmptyFrame(m_printerBed, this);
            m_layout->addWidget(m_emptyFrame);

            //hide recalibrate ui
            ui->recalibrateButton->setHidden(true);
        }
    }

    hideLoadingScreen();
}

void BedMeshFrame::onBedMeshCalibrating()
{
    clearLayout();
    showLoadingScreen();
}

void BedMeshFrame::clearLayout()
{
    if(m_emptyFrame)
    {
        m_emptyFrame->deleteLater();
        m_emptyFrame = nullptr;
    }

    //remove results
    QList<BedMeshItemFrame*> itemFrames = findChildren<BedMeshItemFrame*>();

    foreach(BedMeshItemFrame *itemFrame, itemFrames)
    {
        m_layout->removeWidget(itemFrame);
        itemFrame->deleteLater();
    }
}
