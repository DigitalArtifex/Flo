#include "adjustmentscrewframe.h"
#include "ui_adjustmentscrewframe.h"

AdjustmentScrewFrame::AdjustmentScrewFrame(Q3DPrintBed *bed, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::AdjustmentScrewFrame)
{
    ui->setupUi(this);
    m_printerBed = bed;

    setContentsMargins(0,0,0,0);

    connect(m_printerBed, SIGNAL(adjustmentScrewsCalibrated()), this, SLOT(on_printerBed_adjustmentScrewsCalibrated()));
    connect(m_printerBed, SIGNAL(adjustmentScrewsCalibrating()), this, SLOT(on_printerBed_adjustmentScrewsCalibrating()));

    connect(m_printerBed->printer()->toolhead(), SIGNAL(homing()), this, SLOT(on_toolhead_homing()));
    connect(m_printerBed->printer()->toolhead(), SIGNAL(homed()), this, SLOT(on_toolhead_homed()));

    m_emptyAdjustmentScrewFrame = new AdjustmentScrewEmptyFrame(m_printerBed, ui->dataFrame);
    ui->dataFrame->layout()->addWidget(m_emptyAdjustmentScrewFrame);
    ui->recalibrateButton->setHidden(true);
}

AdjustmentScrewFrame::~AdjustmentScrewFrame()
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

    delete ui;
}

void AdjustmentScrewFrame::showLoadingScreen()
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

void AdjustmentScrewFrame::hideLoadingScreen()
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

void AdjustmentScrewFrame::on_loadingAnimation_finished()
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

void AdjustmentScrewFrame::on_printerBed_calibrating()
{
    showLoadingScreen();
}

void AdjustmentScrewFrame::on_toolhead_homing()
{
    setEnabled(false);
}

void AdjustmentScrewFrame::on_toolhead_homed()
{
    setEnabled(true);
}

void AdjustmentScrewFrame::on_recalibrateButton_clicked()
{
    showLoadingScreen();

    QGridLayout *layout = (QGridLayout*)ui->dataFrame->layout();
    QList<AdjustmentScrewItemFrame*> frames = findChildren<AdjustmentScrewItemFrame*>();

    foreach(AdjustmentScrewItemFrame *frame, frames)
    {
        if(frame)
        {
            layout->removeWidget(frame);
            frame->deleteLater();
        }
    }

    ui->recalibrateButton->setEnabled(false);

    if(!m_emptyAdjustmentScrewFrame)
    {
        m_emptyAdjustmentScrewFrame = new AdjustmentScrewEmptyFrame(m_printerBed, ui->dataFrame);

        layout->addWidget(m_emptyAdjustmentScrewFrame, 0, 0, 1, layout->columnCount());
    }

    m_printerBed->calibrateAdjustmentScrews();
}

void AdjustmentScrewFrame::on_printerBed_adjustmentScrewsCalibrated()
{
    QGridLayout *layout = (QGridLayout*)ui->dataFrame->layout();

    QList<AdjustmentScrewItemFrame*> frames = ui->dataFrame->findChildren<AdjustmentScrewItemFrame*>();

    foreach(AdjustmentScrewItemFrame *frame, frames)
    {
        if(frame)
        {
            layout->removeWidget(frame);
            frame->deleteLater();
        }
    }

    QMap<QString,Q3DPrintBed::AdjustmentScrew*> adjustmentScrews = m_printerBed->adjustmentScrews();
    QStringList keys = adjustmentScrews.keys();
    bool colToggle = false;
    int row = 0;

    if(m_printerBed->hasAdjustmentScrewResult())
    {
        if(m_emptyAdjustmentScrewFrame)
        {
            layout->removeWidget(m_emptyAdjustmentScrewFrame);
            delete m_emptyAdjustmentScrewFrame;
            m_emptyAdjustmentScrewFrame = nullptr;
        }

        foreach(QString key, keys)
        {
            //Create the frame and set the data
            AdjustmentScrewItemFrame *frame = new AdjustmentScrewItemFrame(ui->dataFrame);
            frame->setAdjustmentScrew(adjustmentScrews[key]);

            //Add it to the layout
            if(colToggle)
                layout->addWidget(frame,row, 1);
            else
                layout->addWidget(frame, row, 0);

            //Increase indexes
            if(colToggle)
                row++;

            colToggle = !colToggle;
        }

        ui->recalibrateButton->setHidden(false);
        ui->recalibrateButton->setEnabled(true);
    }

    else
    {
        if(!m_emptyAdjustmentScrewFrame)
        {
            m_emptyAdjustmentScrewFrame = new AdjustmentScrewEmptyFrame(m_printerBed, ui->dataFrame);
            layout->addWidget(m_emptyAdjustmentScrewFrame);
        }

        ui->recalibrateButton->setHidden(true);
    }

    hideLoadingScreen();
}

void AdjustmentScrewFrame::on_printerBed_adjustmentScrewsCalibrating()
{
    showLoadingScreen();
}

