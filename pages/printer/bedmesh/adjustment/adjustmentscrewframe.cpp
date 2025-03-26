#include "adjustmentscrewframe.h"

#include "flo/settings.h"

AdjustmentScrewFrame::AdjustmentScrewFrame(QKlipperPrintBed *bed, QWidget *parent)
    : CardWidget(CardType::Widget, parent)
{
    setupUi();
    setPrinterBed(bed);
}

AdjustmentScrewFrame::AdjustmentScrewFrame(QWidget *parent)
    : CardWidget(CardType::Widget, parent)
{
    setupUi();
    onAdjustmentScrewsChanged();
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

void AdjustmentScrewFrame::setIcons()
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

void AdjustmentScrewFrame::setPrinterBed(QKlipperPrintBed *printerBed)
{
    if(m_printerBed == printerBed)
        return;

    if(m_printerBed)
    {
        disconnect(m_printerBed, SIGNAL(adjustmentScrewsCalibrating()), this, SLOT(onPrinterBedCalibrating()));
        disconnect(m_printerBed, SIGNAL(adjustmentScrewsCalibratingFinished()), this, SLOT(onPrinterBedCalibratingFinished()));
        disconnect(m_printerBed, SIGNAL(adjustmentScrewsChanged()), this, SLOT(onAdjustmentScrewsChanged()));
        disconnect(m_printerBed, SIGNAL(hasAdjustmentScrewResultChanged()), this, SLOT(onAdjustmentScrewsChanged()));
    }

    m_printerBed = printerBed;

    connect(m_printerBed, SIGNAL(adjustmentScrewsCalibrating()), this, SLOT(onPrinterBedCalibrating()));
    connect(m_printerBed, SIGNAL(adjustmentScrewsCalibratingFinished()), this, SLOT(onPrinterBedCalibratingFinished()));
    connect(m_printerBed, SIGNAL(adjustmentScrewsChanged()), this, SLOT(onAdjustmentScrewsChanged()));
    connect(m_printerBed, SIGNAL(hasAdjustmentScrewResultChanged()), this, SLOT(onAdjustmentScrewsChanged()));

    onAdjustmentScrewsChanged();
}

void AdjustmentScrewFrame::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setIcons();
}

void AdjustmentScrewFrame::setupUi()
{
    m_dataFrame = new QFrame(this);
    m_dataLayout = new QGridLayout(m_dataFrame);
    m_dataFrame->setLayout(m_dataLayout);

    setCentralWidget(m_dataFrame);

    setTitle("Adjustment Screws");
    setIcons();
}

void AdjustmentScrewFrame::on_recalibrateButton_clicked()
{
    clearLayout();

    //ui->recalibrateButton->setEnabled(false);

    if(!m_emptyAdjustmentScrewFrame)
    {
        QGridLayout *layout = (QGridLayout*)m_dataFrame->layout();
        m_emptyAdjustmentScrewFrame = new AdjustmentScrewEmptyFrame(m_dataFrame);

        layout->addWidget(m_emptyAdjustmentScrewFrame, 0, 0, 1, layout->columnCount());
    }

    m_printerBed->calibrateAdjustmentScrews();
}

void AdjustmentScrewFrame::onAdjustmentScrewsChanged()
{
    QGridLayout *layout = (QGridLayout*)m_dataFrame->layout();

    clearLayout();

    if(m_printerBed && m_printerBed->hasAdjustmentScrewResult())
    {
        QMap<QString, QKlipperAdjustmentScrew*> adjustmentScrews = m_printerBed->adjustmentScrews();
        QStringList keys = adjustmentScrews.keys();
        bool colToggle = false;
        int row = 0;

        if(m_emptyAdjustmentScrewFrame)
        {
            layout->removeWidget(m_emptyAdjustmentScrewFrame);
             m_emptyAdjustmentScrewFrame->deleteLater();
            m_emptyAdjustmentScrewFrame = nullptr;
        }

        foreach(QString key, keys)
        {
            //Create the frame and set the data
            AdjustmentScrewItemFrame *frame = new AdjustmentScrewItemFrame(adjustmentScrews[key], m_dataFrame);
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
    }

    else
    {
        if(!m_emptyAdjustmentScrewFrame)
        {
            m_emptyAdjustmentScrewFrame = new AdjustmentScrewEmptyFrame(m_dataFrame);
            layout->addWidget(m_emptyAdjustmentScrewFrame);
        }
    }
}

