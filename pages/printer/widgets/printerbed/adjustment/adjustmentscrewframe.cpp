#include "adjustmentscrewframe.h"
#include "ui_adjustmentscrewframe.h"

AdjustmentScrewFrame::AdjustmentScrewFrame(Q3DPrintBed *bed, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::AdjustmentScrewFrame)
{
    ui->setupUi(this);
    _printerBed = bed;

    setContentsMargins(0,0,0,0);

    connect(_printerBed, SIGNAL(adjustmentScrewsCalibrated()), this, SLOT(on_printerBed_adjustmentScrewsCalibrated()));
    connect(_printerBed, SIGNAL(adjustmentScrewsCalibrating()), this, SLOT(on_printerBed_adjustmentScrewsCalibrating()));

    connect(_printerBed->printer()->toolhead(), SIGNAL(homing()), this, SLOT(on_toolhead_homing()));
    connect(_printerBed->printer()->toolhead(), SIGNAL(homed()), this, SLOT(on_toolhead_homed()));

    _emptyAdjustmentScrewFrame = new AdjustmentScrewEmptyFrame(_printerBed, ui->dataFrame);
    ui->dataFrame->layout()->addWidget(_emptyAdjustmentScrewFrame);
    ui->recalibrateButton->setHidden(true);
}

AdjustmentScrewFrame::~AdjustmentScrewFrame()
{
    if(_loadingGif)
    {
        delete _loadingGif;
        _loadingGif = nullptr;
    }

    if(_loadingLabel)
    {
        delete _loadingLabel;
        _loadingLabel = nullptr;
    }

    if(_loadingAnimation)
    {
        delete _loadingAnimation;
        _loadingAnimation = nullptr;
    }

    if(_loadingFrameLayout)
    {
        delete _loadingFrameLayout;
        _loadingFrameLayout = nullptr;
    }

    if(_loadingFrame)
    {
        delete _loadingFrame;
        _loadingFrame = nullptr;
    }

    delete ui;
}

void AdjustmentScrewFrame::showLoadingScreen()
{
    if(_loadingGif)
    {
        delete _loadingGif;
        _loadingGif = nullptr;
    }

    if(_loadingLabel)
    {
        delete _loadingLabel;
        _loadingLabel = nullptr;
    }

    if(_loadingAnimation)
    {
        delete _loadingAnimation;
        _loadingAnimation = nullptr;
    }

    if(_loadingFrameLayout)
    {
        delete _loadingFrameLayout;
        _loadingFrameLayout = nullptr;
    }

    if(_loadingFrame)
    {
        delete _loadingFrame;
        _loadingFrame = nullptr;
    }

    _loadingFrameLayout = new QHBoxLayout(_loadingFrame);
    _loadingFrame = new QFrame(this);
    _loadingFrame->setLayout(_loadingFrameLayout);
    _loadingFrame->setMinimumWidth(this->width());
    _loadingFrame->setMinimumHeight(this->height());
    _loadingFrame->show();
    _loadingFrame->raise();

    _loadingFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "LoadingOverlayFrame"));

    _loadingGif = new QMovie(":/images/loading_small_1a87c5.gif");

    _loadingLabel = new QLabel(_loadingFrame);
    _loadingLabel->setFixedSize(50,50);
    _loadingLabel->setScaledContents(true);
    _loadingLabel->setMovie(_loadingGif);
    _loadingFrameLayout->addWidget(_loadingLabel);

    _loadingAnimation = new QWidgetAnimation(_loadingFrame);
    _loadingAnimation->setDuration(100);
    _loadingAnimation->setStartOpacity(0);
    _loadingAnimation->setEndOpacity(1);

    _loadingGif->start();
    _loadingAnimation->start();

    this->style()->polish(_loadingFrame);
}

void AdjustmentScrewFrame::hideLoadingScreen()
{
    if(_loadingGif)
    {
        connect(_loadingAnimation, SIGNAL(finished()), this, SLOT(on_loadingAnimation_finished()));
        _loadingAnimation->setStartOpacity(1);
        _loadingAnimation->setEndOpacity(0);
        _loadingAnimation->setDuration(100);
        _loadingAnimation->start();
    }
}

void AdjustmentScrewFrame::on_loadingAnimation_finished()
{
    _loadingGif->stop();

    if(_loadingGif)
    {
        delete _loadingGif;
        _loadingGif = nullptr;
    }

    if(_loadingLabel)
    {
        delete _loadingLabel;
        _loadingLabel = nullptr;
    }

    if(_loadingAnimation)
    {
        delete _loadingAnimation;
        _loadingAnimation = nullptr;
    }

    if(_loadingFrameLayout)
    {
        delete _loadingFrameLayout;
        _loadingFrameLayout = nullptr;
    }

    if(_loadingFrame)
    {
        delete _loadingFrame;
        _loadingFrame = nullptr;
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

    if(!_emptyAdjustmentScrewFrame)
    {
        _emptyAdjustmentScrewFrame = new AdjustmentScrewEmptyFrame(_printerBed, ui->dataFrame);

        layout->addWidget(_emptyAdjustmentScrewFrame, 0, 0, 1, layout->columnCount());
    }

    _printerBed->calibrateAdjustmentScrews();
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

    QMap<QString,Q3DPrintBed::AdjustmentScrew*> adjustmentScrews = _printerBed->adjustmentScrews();
    QStringList keys = adjustmentScrews.keys();
    bool colToggle = false;
    int row = 0;

    if(_printerBed->hasAdjustmentScrewResult())
    {
        if(_emptyAdjustmentScrewFrame)
        {
            layout->removeWidget(_emptyAdjustmentScrewFrame);
            delete _emptyAdjustmentScrewFrame;
            _emptyAdjustmentScrewFrame = nullptr;
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
        if(!_emptyAdjustmentScrewFrame)
        {
            _emptyAdjustmentScrewFrame = new AdjustmentScrewEmptyFrame(_printerBed, ui->dataFrame);
            layout->addWidget(_emptyAdjustmentScrewFrame);
        }

        ui->recalibrateButton->setHidden(true);
    }

    hideLoadingScreen();
}

void AdjustmentScrewFrame::on_printerBed_adjustmentScrewsCalibrating()
{
    showLoadingScreen();
}

