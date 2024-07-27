#include "printerservicewidget.h"

#include "system/settings.h"

PrinterServiceWidget::PrinterServiceWidget(System *system, System::ServiceState service, QWidget *parent)
    : CardWidget{CardWidget::SubWidget, parent}
{
    m_system = system;
    m_service = service;

    setupUi();

    connect(m_system, SIGNAL(serviceStatesUpdate()), this, SLOT(serviceStatesUpdateEvent()));
}

void PrinterServiceWidget::setupUi()
{
    setFixedSize(160,175);
    setTitle(m_service.name);

    QString serviceText = QString("Active State: %1").arg(m_service.activeState);
    QString stateText = QString("Sub State: %1").arg(m_service.subState);

    m_centralWidget = new QWidget(this);
    m_centralLayout = new QVBoxLayout(m_centralWidget);
    m_centralWidget->setLayout(m_centralLayout);

    m_stateLabel = new QLabel(m_centralWidget);
    m_stateLabel->setText(serviceText);
    m_centralLayout->addWidget(m_stateLabel);

    m_subStateLabel = new QLabel(m_centralWidget);
    m_subStateLabel->setText(stateText);
    m_centralLayout->addWidget(m_subStateLabel);

    m_spacerItem = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_centralLayout->addSpacerItem(m_spacerItem);

    setCentralWidget(m_centralWidget);

    //setup footer
    m_stopButton = new QToolButton(this);
    m_stopButton->setIcon(Settings::getThemeIcon("stop-icon"));
    m_stopButton->setFixedSize(32,32);

    m_startButton = new QToolButton(this);
    m_startButton->setIcon(Settings::getThemeIcon("start-icon"));
    m_startButton->setFixedSize(32,32);

    m_restartButton = new QToolButton(this);
    m_restartButton->setIcon(Settings::getThemeIcon("refresh-icon"));
    m_restartButton->setFixedSize(32,32);

    connect(m_stopButton, SIGNAL(clicked(bool)), this, SLOT(stopButtonClickEvent(bool)));
    connect(m_startButton, SIGNAL(clicked(bool)), this, SLOT(startButtonClickEvent(bool)));
    connect(m_restartButton, SIGNAL(clicked(bool)), this, SLOT(restartButtonClickEvent(bool)));

    addFooterItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    addFooterWidget(m_stopButton);
    addFooterWidget(m_startButton);
    addFooterWidget(m_restartButton);
    addFooterItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    serviceStatesUpdateEvent();
}

void PrinterServiceWidget::serviceStatesUpdateEvent()
{
    m_service = m_system->serviceStates()[m_service.name];

    QString serviceText = QString("Active State: %1").arg(m_service.activeState);
    QString stateText = QString("Sub State: %1").arg(m_service.subState);

    m_stateLabel->setText(serviceText);
    m_subStateLabel->setText(stateText);

    if(m_service.activeState == QString("active"))
    {
        m_restartButton->setEnabled(true);
        m_startButton->setEnabled(false);
        m_stopButton->setEnabled(true);
    }
    else if(m_service.activeState == QString("deactivating"))
    {
        m_restartButton->setEnabled(false);
        m_startButton->setEnabled(false);
        m_stopButton->setEnabled(false);

        m_system->updateServices();
    }
    else
    {
        m_restartButton->setEnabled(false);
        m_startButton->setEnabled(true);
        m_stopButton->setEnabled(false);
    }
}

void PrinterServiceWidget::stopButtonClickEvent(bool checked)
{
    Q_UNUSED(checked);

    m_restartButton->setEnabled(false);
    m_startButton->setEnabled(false);
    m_stopButton->setEnabled(false);

    m_system->stopService(m_service.name);
}

void PrinterServiceWidget::startButtonClickEvent(bool checked)
{
    Q_UNUSED(checked);

    m_restartButton->setEnabled(false);
    m_startButton->setEnabled(false);
    m_stopButton->setEnabled(false);

    m_system->startService(m_service.name);
}

void PrinterServiceWidget::restartButtonClickEvent(bool checked)
{
    Q_UNUSED(checked);

    m_restartButton->setEnabled(false);
    m_startButton->setEnabled(false);
    m_stopButton->setEnabled(false);

    m_system->restartService(m_service.name);
}
