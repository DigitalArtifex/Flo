#include "bedmeshframe.h"

#include "system/settings.h"

BedMeshFrame::BedMeshFrame(QKlipperPrintBed *bed, QWidget *parent)
    : CardWidget(CardWidget::Widget, parent)
{
    setTitle("Probed Data");

    m_printerBed = bed;

    m_centralWidget = new QWidget(this);

    m_centralLayout = new QGridLayout(this);
    m_centralLayout->setContentsMargins(4,4,4,4);
    m_centralLayout->setSpacing(4);
    m_centralWidget->setLayout(m_centralLayout);

    setCentralWidget(m_centralWidget);

    setupIcons();
    onBedMeshCalibratingFinished();

    connect(m_printerBed, SIGNAL(hasBedMeshResultChanged()), this, SLOT(onBedMeshCalibratingFinished()));
    connect(m_printerBed->bedMesh(), SIGNAL(probedChanged()), this, SLOT(onBedMeshCalibratingFinished()));
}

BedMeshFrame::~BedMeshFrame()
{
    //delete ui;
}

void BedMeshFrame::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::StyleChange)
    {
        setupIcons();
    }

    QWidget::changeEvent(event);
}

void BedMeshFrame::setupIcons()
{
    setIcon(Settings::getThemeIcon("bed-mesh"));
}

void BedMeshFrame::onBedMeshCalibratingFinished()
{
    if(m_printerBed->hasBedMeshResult() && m_printerBed->bedMesh()->probed().count() > 0)
    {
        clearLayout();

        for(QList<qreal> &row : m_printerBed->bedMesh()->probed())
        {
            int rowNumber = m_centralLayout->rowCount();

            for(int i = 0; i < row.count(); i++)
            {
                BedMeshItemFrame *itemFrame = new BedMeshItemFrame(this);
                itemFrame->setValue(row[i]);

                m_centralLayout->addWidget(itemFrame, rowNumber, i, Qt::AlignCenter);
            }
        }
    }

    //show empty frame
    else if(!m_emptyFrame)
    {
        m_emptyFrame = new BedMeshEmptyFrame(m_printerBed, this);
        m_centralLayout->addWidget(m_emptyFrame);
    }
}

void BedMeshFrame::clearLayout()
{
    if(m_emptyFrame)
    {
        m_centralLayout->removeWidget(m_emptyFrame);
        delete m_emptyFrame;
        m_emptyFrame = nullptr;
    }

    //remove results
    QList<BedMeshItemFrame*> itemFrames = findChildren<BedMeshItemFrame*>();

    for(BedMeshItemFrame *itemFrame : itemFrames)
    {
        m_centralLayout->removeWidget(itemFrame);
        itemFrame->deleteLater();
    }
}
