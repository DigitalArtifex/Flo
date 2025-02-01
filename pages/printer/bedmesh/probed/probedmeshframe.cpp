#include "probedmeshframe.h"

#include "flo/settings.h"

ProbedMeshFrame::ProbedMeshFrame(QKlipperPrintBed *bed, QWidget *parent)
    : CardWidget(CardType::Widget, parent)
{
    setTitle("Probed Data");

    m_printerBed = bed;

    m_centralWidget = new QWidget(this);

    m_centralLayout = new QGridLayout(this);
    m_centralLayout->setContentsMargins(4,4,4,4);
    m_centralLayout->setSpacing(4);
    m_centralWidget->setLayout(m_centralLayout);

    setCentralWidget(m_centralWidget);

    m_emptyFrame = new ProbedMeshEmptyFrame(m_printerBed, this);
    m_centralLayout->addWidget(m_emptyFrame);

    setupIcons();
    onBedMeshCalibratingFinished();

    //a non-fatal race condition can occur between these 2 signals, so connect to them both
    connect(m_printerBed, SIGNAL(hasBedMeshResultChanged()), this, SLOT(onBedMeshCalibratingFinished()));
    connect(m_printerBed->bedMesh(), SIGNAL(probedChanged()), this, SLOT(onBedMeshCalibratingFinished()));
}

ProbedMeshFrame::~ProbedMeshFrame()
{
    //delete ui;
}

void ProbedMeshFrame::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::StyleChange)
    {
        setupIcons();
    }

    QWidget::changeEvent(event);
}

void ProbedMeshFrame::setupIcons()
{
    setIcon(Settings::getThemeIcon("bed-mesh"));
}

void ProbedMeshFrame::onBedMeshCalibratingFinished()
{
    //probed is often returning a single empty row, so we need to check the row and col count
    if(m_printerBed->bedMesh()->probed().count() > 0 && m_printerBed->bedMesh()->probed()[0].count() > 0)
    {
        clearLayout();

        for(QList<qreal> &row : m_printerBed->bedMesh()->probed())
        {
            int rowNumber = m_centralLayout->rowCount();

            for(int i = 0; i < row.count(); i++)
            {
                ProbedMeshItemFrame *itemFrame = new ProbedMeshItemFrame(this);
                itemFrame->setValue(row[i]);

                m_centralLayout->addWidget(itemFrame, rowNumber, i, Qt::AlignCenter);
            }
        }
    }

    //show empty frame
    else if(!m_emptyFrame)
    {
        m_emptyFrame = new ProbedMeshEmptyFrame(m_printerBed, this);
        m_centralLayout->addWidget(m_emptyFrame);
    }
}

void ProbedMeshFrame::clearLayout()
{
    if(m_emptyFrame)
    {
        m_centralLayout->removeWidget(m_emptyFrame);
        delete m_emptyFrame;
        m_emptyFrame = nullptr;
    }

    //remove results
    QList<ProbedMeshItemFrame*> itemFrames = findChildren<ProbedMeshItemFrame*>();

    for(ProbedMeshItemFrame *itemFrame : itemFrames)
    {
        m_centralLayout->removeWidget(itemFrame);
        itemFrame->deleteLater();
    }
}
