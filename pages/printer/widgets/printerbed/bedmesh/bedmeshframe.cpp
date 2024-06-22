#include "bedmeshframe.h"
#include "ui_bedmeshframe.h"

#include "../../../../../system/settings.h"

BedMeshFrame::BedMeshFrame(Q3DPrintBed *bed, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::BedMeshFrame)
{
    ui->setupUi(this);

    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(4,4,4,4);
    m_layout->setSpacing(4);
    ui->bedMeshFrame->setLayout(m_layout);

    m_emptyFrame = new BedMeshEmptyFrame(bed, this);
    m_layout->addWidget(m_emptyFrame);

    ui->recalibrateButton->setHidden(true);

    m_printerBed = bed;
    connect(m_printerBed, SIGNAL(bedMeshCalibrating()), this, SLOT(on_printerBed_bedMeshCalibrating()));
    connect(m_printerBed, SIGNAL(bedMeshCalibrated()), this, SLOT(on_printerBed_bedMeshCalibrated()));
    connect(m_printerBed->printer()->toolhead(), SIGNAL(homing()), this, SLOT(on_toolhead_homing()));
    connect(m_printerBed->printer()->toolhead(), SIGNAL(homed()), this, SLOT(on_toolhead_homed()));

    setupIcons();
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
        delete m_loadingGif;
        m_loadingGif = nullptr;
    }

    if(m_loadingLabel)
    {
        delete m_loadingLabel;
        m_loadingLabel = nullptr;
    }

    if(m_loadingAnimation)
    {
        delete m_loadingAnimation;
        m_loadingAnimation = nullptr;
    }

    if(m_loadingFrameLayout)
    {
        delete m_loadingFrameLayout;
        m_loadingFrameLayout = nullptr;
    }

    if(m_loadingFrame)
    {
        delete m_loadingFrame;
        m_loadingFrame = nullptr;
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

void BedMeshFrame::on_loadingAnimation_finished()
{
    m_loadingGif->stop();

    if(m_loadingGif)
    {
        delete m_loadingGif;
        m_loadingGif = nullptr;
    }

    if(m_loadingLabel)
    {
        delete m_loadingLabel;
        m_loadingLabel = nullptr;
    }

    if(m_loadingAnimation)
    {
        delete m_loadingAnimation;
        m_loadingAnimation = nullptr;
    }

    if(m_loadingFrameLayout)
    {
        delete m_loadingFrameLayout;
        m_loadingFrameLayout = nullptr;
    }

    if(m_loadingFrame)
    {
        delete m_loadingFrame;
        m_loadingFrame = nullptr;
    }
}

void BedMeshFrame::on_printerBed_calibrating()
{
    showLoadingScreen();
}

void BedMeshFrame::on_toolhead_homing()
{
    setEnabled(false);
}

void BedMeshFrame::on_toolhead_homed()
{
    setEnabled(true);
}

void BedMeshFrame::on_printerBed_bedMeshCalibrated()
{
    //remove results
    QList<BedMeshItemFrame*> itemFrames = findChildren<BedMeshItemFrame*>();

    foreach(BedMeshItemFrame *itemFrame, itemFrames)
    {
        m_layout->removeWidget(itemFrame);
        itemFrame->deleteLater();
    }

    if(m_printerBed->bedMesh().probed.count() > 0)
    {
        foreach(QList<qreal> row, m_printerBed->bedMesh().probed)
        {
            int rowNumber = m_layout->rowCount();

            for(int i = 0; i < row.count(); i++)
            {
                //remove empty frame
                if(m_emptyFrame)
                {
                    m_layout->removeWidget(m_emptyFrame);
                    delete m_emptyFrame;
                    m_emptyFrame = nullptr;

                    //unhide recalibrate ui
                    ui->recalibrateButton->setHidden(false);
                }

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

            //unhide recalibrate ui
            ui->recalibrateButton->setHidden(true);
        }
    }

    hideLoadingScreen();
}

void BedMeshFrame::on_printerBed_bedMeshCalibrating()
{
    showLoadingScreen();
}
