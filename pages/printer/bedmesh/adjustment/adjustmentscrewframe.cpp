#include "adjustmentscrewframe.h"

#include "flo/settings.h"

AdjustmentScrewFrame::AdjustmentScrewFrame(QKlipperPrintBed *bed, QWidget *parent)
    : CardWidget(CardType::Widget, parent)
{
    m_printerBed = bed;

    connect(m_printerBed, SIGNAL(adjustmentScrewsCalibrating()), this, SLOT(onPrinterBedCalibrating()));
    connect(m_printerBed, SIGNAL(adjustmentScrewsCalibratingFinished()), this, SLOT(onPrinterBedCalibratingFinished()));
    connect(m_printerBed, SIGNAL(adjustmentScrewsChanged()), this, SLOT(onAdjustmentScrewsChanged()));
    connect(m_printerBed, SIGNAL(hasAdjustmentScrewResultChanged()), this, SLOT(onAdjustmentScrewsChanged()));
    connect(m_printerBed->printer()->toolhead(), SIGNAL(homing()), this, SLOT(onToolheadHoming()));
    connect(m_printerBed->printer()->toolhead(), SIGNAL(homingFinished()), this, SLOT(onToolheadHomed()));

    m_emptyAdjustmentScrewFrame = new AdjustmentScrewEmptyFrame(m_printerBed, m_dataFrame);
    m_dataFrame = new QFrame(this);
    m_dataLayout = new QGridLayout(m_dataFrame);
    m_dataFrame->setLayout(m_dataLayout);

    setCentralWidget(m_dataFrame);

    m_dataFrame->layout()->addWidget(m_emptyAdjustmentScrewFrame);
    setTitle("Adjustment Screws");
    setupIcons();
}

AdjustmentScrewFrame::~AdjustmentScrewFrame()
{
    // if(m_loadingGif)
    // {
    //      m_loadingGif->deleteLater();
    // }

    // if(m_loadingLabel)
    // {
    //      m_loadingLabel->deleteLater();
    // }

    // if(m_loadingAnimation)
    // {
    //      m_loadingAnimation->deleteLater();
    // }

    // if(m_loadingFrameLayout)
    // {
    //      m_loadingFrameLayout->deleteLater();
    // }

    // if(m_loadingFrame)
    // {
    //      m_loadingFrame->deleteLater();
    // }
}

void AdjustmentScrewFrame::showLoadingScreen()
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

    m_loadingFrameLayout = new QHBoxLayout(m_loadingFrame);
    m_loadingFrame = new QFrame(this);
    m_loadingFrame->setLayout(m_loadingFrameLayout);
    m_loadingFrame->setMinimumWidth(this->width());
    m_loadingFrame->setMinimumHeight(this->height());
    m_loadingFrame->show();
    m_loadingFrame->raise();

    m_loadingFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "LoadingOverlayFrame"));

    m_loadingGif = new QMovie(":/images/loading.gif");

    m_loadingLabel = new QLabel(m_loadingFrame);
    m_loadingLabel->setFixedSize(100,100);
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

void AdjustmentScrewFrame::setStyleSheet(const QString &styleSheet)
{
    setupIcons();

    if(m_emptyAdjustmentScrewFrame)
        m_emptyAdjustmentScrewFrame->setStyleSheet(styleSheet);

    QList<AdjustmentScrewItemFrame*> frames = m_dataFrame->findChildren<AdjustmentScrewItemFrame*>();

    foreach(AdjustmentScrewItemFrame *frame, frames)
    {
        if(frame)
            frame->setStyleSheet(styleSheet);
    }

    QFrame::setStyleSheet(styleSheet);
}

void AdjustmentScrewFrame::setupIcons()
{
    setIcon(Settings::getThemeIcon("adjustment-screw"));
}

void AdjustmentScrewFrame::on_loadingAnimation_finished()
{
    m_loadingGif->stop();

    if(m_loadingFrameLayout)
        m_loadingFrameLayout->deleteLater();

    if(m_loadingFrame)
        m_loadingFrame->deleteLater();
}

void AdjustmentScrewFrame::onToolheadHoming()
{
    setEnabled(false);
}

void AdjustmentScrewFrame::onToolheadHomed()
{
    setEnabled(true);
}

void AdjustmentScrewFrame::clearLayout()
{
    QGridLayout *layout = (QGridLayout*)m_dataFrame->layout();

    QList<AdjustmentScrewItemFrame*> frames = m_dataFrame->findChildren<AdjustmentScrewItemFrame*>();

    foreach(AdjustmentScrewItemFrame *frame, frames)
    {
        if(frame)
        {
            layout->removeWidget(frame);
            frame->deleteLater();
        }
    }
}

void AdjustmentScrewFrame::on_recalibrateButton_clicked()
{
    clearLayout();
    showLoadingScreen();

    //ui->recalibrateButton->setEnabled(false);

    if(!m_emptyAdjustmentScrewFrame)
    {
        QGridLayout *layout = (QGridLayout*)m_dataFrame->layout();
        m_emptyAdjustmentScrewFrame = new AdjustmentScrewEmptyFrame(m_printerBed, m_dataFrame);

        layout->addWidget(m_emptyAdjustmentScrewFrame, 0, 0, 1, layout->columnCount());
    }

    m_printerBed->calibrateAdjustmentScrews();
}

void AdjustmentScrewFrame::onPrinterBedCalibrating()
{
    showLoadingScreen();
}

void AdjustmentScrewFrame::onPrinterBedCalibratingFinished()
{
    hideLoadingScreen();
}

void AdjustmentScrewFrame::onAdjustmentScrewsChanged()
{
    QGridLayout *layout = (QGridLayout*)m_dataFrame->layout();
    QMap<QString, QKlipperAdjustmentScrew*> adjustmentScrews = m_printerBed->adjustmentScrews();
    QStringList keys = adjustmentScrews.keys();
    bool colToggle = false;
    int row = 0;

    clearLayout();

    if(m_printerBed->hasAdjustmentScrewResult())
    {

        if(m_emptyAdjustmentScrewFrame)
        {
            layout->removeWidget(m_emptyAdjustmentScrewFrame);
             m_emptyAdjustmentScrewFrame->deleteLater();
            m_emptyAdjustmentScrewFrame = nullptr;
        }

        foreach(QString key, keys)
        {
            //Create the frame and set the data
            AdjustmentScrewItemFrame *frame = new AdjustmentScrewItemFrame(m_dataFrame);
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

        // ui->recalibrateButton->setHidden(false);
        // ui->recalibrateButton->setEnabled(true);
    }

    else
    {
        if(!m_emptyAdjustmentScrewFrame)
        {
            m_emptyAdjustmentScrewFrame = new AdjustmentScrewEmptyFrame(m_printerBed, m_dataFrame);
            layout->addWidget(m_emptyAdjustmentScrewFrame);
        }

        // ui->recalibrateButton->setHidden(true);
    }
}

