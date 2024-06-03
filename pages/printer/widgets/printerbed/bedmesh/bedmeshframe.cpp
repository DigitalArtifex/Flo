#include "bedmeshframe.h"
#include "ui_bedmeshframe.h"

#include "../../../../../system/settings.h"

BedMeshFrame::BedMeshFrame(Q3DPrintBed *bed, QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::BedMeshFrame)
{
    ui->setupUi(this);

    _layout = new QGridLayout(this);
    ui->bedMeshFrame->setLayout(_layout);

    _emptyFrame = new BedMeshEmptyFrame(bed, this);
    _layout->addWidget(_emptyFrame);

    ui->addProfileButton->setHidden(true);
    ui->removeProfileButton->setHidden(true);
    ui->profileComboBox->setHidden(true);
    ui->recalibrateButton->setHidden(true);

    _printerBed = bed;
    connect(_printerBed, SIGNAL(updated(Q3DPrintBed*)), this, SLOT(on_printBed_updated(Q3DPrintBed*)));
    connect(_printerBed, SIGNAL(calibrating()), this, SLOT(on_printerBed_calibrating()));
    connect(_printerBed->printer()->toolhead(), SIGNAL(homing()), this, SLOT(on_toolhead_homing()));
    connect(_printerBed->printer()->toolhead(), SIGNAL(homed()), this, SLOT(on_toolhead_homed()));

    setupIcons();
}

BedMeshFrame::~BedMeshFrame()
{
    delete ui;
}

void BedMeshFrame::setupIcons()
{
    ui->removeProfileButton->setIcon(Settings::getThemeIcon(QString("remove-icon")));
    ui->addProfileButton->setIcon(Settings::getThemeIcon(QString("add-icon")));
}

void BedMeshFrame::setupUiClasses()
{

}

void BedMeshFrame::on_printBed_updated(Q3DPrintBed *bed)
{
    Q_UNUSED(bed);

    //remove results
    QList<BedMeshItemFrame*> itemFrames = findChildren<BedMeshItemFrame*>();

    foreach(BedMeshItemFrame *itemFrame, itemFrames)
    {
        _layout->removeWidget(itemFrame);
        itemFrame->deleteLater();
    }

    if(_printerBed->bedMesh().matrix.count() > 0)
    {

        foreach(QList<qreal> row, _printerBed->bedMesh().matrix)
        {
            for(int i = 0; i < row.count(); i++)
            {
                //remove empty frame
                if(_emptyFrame)
                {
                    _layout->removeWidget(_emptyFrame);
                    delete _emptyFrame;
                    _emptyFrame = nullptr;

                    //unhide recalibrate ui
                    ui->addProfileButton->setHidden(false);
                    ui->removeProfileButton->setHidden(false);
                    ui->profileComboBox->setHidden(false);
                    ui->recalibrateButton->setHidden(false);
                }

                BedMeshItemFrame *itemFrame = new BedMeshItemFrame(this);
                itemFrame->setValue(row[i]);

                _layout->addWidget(itemFrame, _layout->rowCount(), i, Qt::AlignCenter);
            }
        }
    }
    //show empty frame
    else
    {
        if(!_emptyFrame)
        {
            _emptyFrame = new BedMeshEmptyFrame(bed, this);
            _layout->addWidget(_emptyFrame);

            //unhide recalibrate ui
            ui->addProfileButton->setHidden(true);
            ui->removeProfileButton->setHidden(true);
            ui->profileComboBox->setHidden(true);
            ui->recalibrateButton->setHidden(true);
        }
    }
}



void BedMeshFrame::showLoadingScreen()
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

    _loadingGif = new QMovie(":/images/images/loading_small_1a87c5.gif");

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

void BedMeshFrame::hideLoadingScreen()
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

void BedMeshFrame::on_loadingAnimation_finished()
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

void BedMeshFrame::on_printerBed_calibrating()
{
    showLoadingScreen();
}

void BedMeshFrame::on_toolhead_homing()
{
    showLoadingScreen();
}

void BedMeshFrame::on_toolhead_homed()
{
    hideLoadingScreen();
}
