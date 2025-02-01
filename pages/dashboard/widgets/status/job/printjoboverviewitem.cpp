#include "printjoboverviewitem.h"
#include "flo/settings.h"
#include <flo/qklipperinstancepool.h>

PrintJobOverviewItem::PrintJobOverviewItem(QWidget *parent) :
    QAnimatedListItem(parent)
{
    setupUi();
}

PrintJobOverviewItem::~PrintJobOverviewItem()
{
    m_iconLabel->deleteLater();
    m_iconContainer->deleteLater();
    m_jobNameLabel->deleteLater();
    m_printerNameLabel->deleteLater();
    m_timeRemainingLabel->deleteLater();
    m_timeRunningLabel->deleteLater();
    m_progressBar->deleteLater();

    if(m_closeButton)
        m_closeButton->deleteLater();
}

void PrintJobOverviewItem::setupUi()
{
    QGridLayout *layout = new QGridLayout();

    m_iconContainer = new QWidget(this);
    m_iconContainer->setLayout(new QVBoxLayout(m_iconContainer));
    m_iconContainer->setBaseSize(100,100);
    m_iconContainer->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum));
    layout->addWidget(m_iconContainer,0,0,3,1);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(32,32);
    m_iconLabel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setText(QString("Icon"));
    m_iconContainer->layout()->addWidget(m_iconLabel);

    m_jobNameLabel = new QLabel(this);
    m_jobNameLabel->setText(QString("Name"));
    layout->addWidget(m_jobNameLabel,0,1,1,2);

    m_closeButton = new QToolButton(this);
    m_closeButton->setIcon(Settings::getThemeIcon(QString("close")));
    connect(m_closeButton, SIGNAL(clicked(bool)), this, SLOT(closeButtonClickEvent()));
    layout->addWidget(m_closeButton,0,3,1,1);

    m_printerNameLabel = new QLabel(this);
    m_printerNameLabel->setText(QString("Printer"));
    layout->addWidget(m_printerNameLabel,1,1,1,2);

    m_timeRemainingLabel = new QLabel(this);
    m_timeRemainingLabel->setText(QString("Time Remaining"));
    layout->addWidget(m_timeRemainingLabel,2,1,1,1);

    m_timeRunningLabel = new QLabel(this);
    m_timeRunningLabel->setText(QString("Time Running"));
    layout->addWidget(m_timeRunningLabel,2,2,1,2);

    m_progressBar = new QProgressBar(this);
    m_progressBar->setMaximum(100);
    m_progressBar->setMinimum(0);
    m_progressBar->setValue(0);
    m_progressBar->setTextVisible(false);
    layout->addWidget(m_progressBar,3,0,1,3);

    setLayout(layout);
}

QKlipperPrintJob *PrintJobOverviewItem::printJob()
{
    return m_job;
}

void PrintJobOverviewItem::setPrintJob(QKlipperPrintJob *job)
{
    m_job = job;
    m_jobNameLabel->setText(job->filename());

    //sort through parent objects until we get to the instance
    QKlipperJobQueue *jobQueue = qobject_cast<QKlipperJobQueue*>(job->parent());

    if(jobQueue)
    {
        QKlipperServer *server = qobject_cast<QKlipperServer*>(jobQueue->parent());

        if(server)
        {
            QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(server->parent());

            if(instance)
            {
                m_printerNameLabel->setText(instance->name());
                connect(instance, SIGNAL(nameChanged()), this, SLOT(onInstanceNameChanged()));
            }
        }
    }

    QPixmap pixmap;

    switch (m_job->state())
    {
    case QKlipperPrintJob::Standby:
        break;
    case QKlipperPrintJob::Printing:
        pixmap = Settings::getThemeIcon(QString("printjob-printing")).pixmap(m_iconLabel->size());
        m_iconLabel->setPixmap(pixmap);
        break;
    case QKlipperPrintJob::Paused:
        pixmap = Settings::getThemeIcon(QString("printjob-paused")).pixmap(m_iconLabel->size());
        m_iconLabel->setPixmap(pixmap);
        break;
    case QKlipperPrintJob::Complete:
        pixmap = Settings::getThemeIcon(QString("printjob-completed")).pixmap(m_iconLabel->size());
        m_iconLabel->setPixmap(pixmap);
        break;
    case QKlipperPrintJob::Cancelled:
        pixmap = Settings::getThemeIcon(QString("printjob-cancelled")).pixmap(m_iconLabel->size());
        m_iconLabel->setPixmap(pixmap);
        break;
    case QKlipperPrintJob::Error:
        pixmap = Settings::getThemeIcon(QString("printjob-error")).pixmap(m_iconLabel->size());
        m_iconLabel->setPixmap(pixmap);
        break;
    }

    connect(m_job, SIGNAL(stateChanged()), this, SLOT(onPrintJobStateChanged()));
    connect(m_job, SIGNAL(currentLayerChanged()), this, SLOT(onPrintJobCurrentLayerChanged()));
    connect(m_job, SIGNAL(totalLayersChanged()), this, SLOT(onPrintJobTotalLayersChanged()));
}

void PrintJobOverviewItem::setStyleSheet(const QString &styleSheet)
{
    QFrame::setStyleSheet(styleSheet);
}

void PrintJobOverviewItem::onPrintJobStateChanged()
{
    QPixmap pixmap;

    switch (m_job->state())
    {
    case QKlipperPrintJob::Standby:
        break;

    case QKlipperPrintJob::Printing:
        pixmap = Settings::getThemeIcon(QString("printjob-printing")).pixmap(m_iconLabel->size());
        m_iconLabel->setPixmap(pixmap);
        break;

    case QKlipperPrintJob::Paused:
        pixmap = Settings::getThemeIcon(QString("printjob-paused")).pixmap(m_iconLabel->size());
        m_iconLabel->setPixmap(pixmap);
        break;

    case QKlipperPrintJob::Complete:
        pixmap = Settings::getThemeIcon(QString("printjob-completed")).pixmap(m_iconLabel->size());
        m_iconLabel->setPixmap(pixmap);

        if(!m_autoRemoveTimer)
        {
            m_autoRemoveTimer = new QTimer(this);
            m_autoRemoveTimer->setInterval(10000);
            connect(m_autoRemoveTimer, SIGNAL(timeout()), this, SLOT(autoRemoveTimerTimeoutEvent()));
            m_autoRemoveTimer->start();
        }
        break;

    case QKlipperPrintJob::Cancelled:
        pixmap = Settings::getThemeIcon(QString("printjob-cancelled")).pixmap(m_iconLabel->size());
        m_iconLabel->setPixmap(pixmap);

        if(!m_autoRemoveTimer)
        {
            m_autoRemoveTimer = new QTimer(this);
            m_autoRemoveTimer->setInterval(10000);
            connect(m_autoRemoveTimer, SIGNAL(timeout()), this, SLOT(autoRemoveTimerTimeoutEvent()));
            m_autoRemoveTimer->start();
        }

        break;

    case QKlipperPrintJob::Error:
        pixmap = Settings::getThemeIcon(QString("printjob-error")).pixmap(m_iconLabel->size());
        m_iconLabel->setPixmap(pixmap);
        break;
    }
}

void PrintJobOverviewItem::onPrintJobCurrentLayerChanged()
{
    m_timeRemainingLabel->setText(QString("Current Layer: ") + QString::number(m_job->currentLayer()));

    qreal progress = (qreal)m_job->currentLayer() / (qreal)m_job->totalLayers();
    progress *= 100;

    m_progressBar->setValue((int)progress);
}

void PrintJobOverviewItem::onPrintJobTotalLayersChanged()
{
    m_timeRunningLabel->setText(QString("Total Layers: ") + QString::number(m_job->totalLayers()));

    qreal progress = (qreal)m_job->currentLayer() / (qreal)m_job->totalLayers();
    progress *= 100;

    m_progressBar->setValue((int)progress);
}

void PrintJobOverviewItem::onInstanceNameChanged()
{
    QKlipperJobQueue *jobQueue = qobject_cast<QKlipperJobQueue*>(m_job->parent());

    if(jobQueue)
    {
        QKlipperServer *server = qobject_cast<QKlipperServer*>(jobQueue->parent());

        if(server)
        {
            QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(server->parent());

            if(instance)
                m_printerNameLabel->setText(instance->name());
        }
    }
}

void PrintJobOverviewItem::closeButtonClickEvent()
{
    emit removeRequest(this);
}

void PrintJobOverviewItem::autoRemoveTimerTimeoutEvent()
{
    if(m_autoRemoveTimer)
    {
        delete m_autoRemoveTimer;
        m_autoRemoveTimer = nullptr;
    }

    emit removeRequest(this);
}
