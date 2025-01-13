#include "printerbedtoolsdialog.h"

#include "system/settings.h"

PrinterBedToolsDialog::PrinterBedToolsDialog(QKlipperPrintBed *bed, QWidget *parent)
    : Dialog{parent}
{
    m_printerBed = bed;
    setupUi();

    connect(m_pidTuneButton, SIGNAL(clicked()), this, SLOT(onPidTuneButtonClicked()));
    connect(m_calibrateMeshButton, SIGNAL(clicked()), this, SLOT(onCalibrateMeshButtonClicked()));
    connect(m_calibrateScrewsButton, SIGNAL(clicked()), this, SLOT(onCalibrateScrewsButtonClicked()));
    connect(m_meshViewerButton, SIGNAL(clicked()), this, SLOT(onMeshViewerButtonClicked()));
}

void PrinterBedToolsDialog::onPidTuneButtonClicked()
{

}

void PrinterBedToolsDialog::onCalibrateMeshButtonClicked()
{

}

void PrinterBedToolsDialog::onCalibrateScrewsButtonClicked()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    ProgressDialog *bedMeshWidget = new ProgressDialog(this);

    bedMeshWidget->setFixedSize(screenGeometry.width() * 0.75, screenGeometry.height() * 0.75);
    bedMeshWidget->exec();

    bedMeshWidget->deleteLater();
}

void PrinterBedToolsDialog::onMeshViewerButtonClicked()
{

}

void PrinterBedToolsDialog::setupUi()
{
    m_centralLayout = new QGridLayout(this);
    setLayout(m_centralLayout);

    m_pidTuneButton = new QIconButton(this);
    m_pidTuneButton->setText("PID Auto Tune");
    m_pidTuneButton->setIcon(
        Settings::getThemeIcon("sine")
        );

    m_centralLayout->addWidget(m_pidTuneButton);

    m_calibrateMeshButton = new QIconButton(this);
    m_calibrateMeshButton->setText("Calibrate Bed Mesh");
    m_calibrateMeshButton->setIcon(
        Settings::getThemeIcon("mesh-calibrate")
        );

    m_centralLayout->addWidget(m_calibrateMeshButton);

    m_calibrateScrewsButton = new QIconButton(this);
    m_calibrateScrewsButton->setText("Calibrate Adjustment Screws");
    m_calibrateScrewsButton->setIcon(
        Settings::getThemeIcon("adjustment-screws-calibrate")
        );

    m_centralLayout->addWidget(m_calibrateScrewsButton);

    m_meshViewerButton = new QIconButton(this);
    m_meshViewerButton->setText("View Bed Mesh");
    m_meshViewerButton->setIcon(
        Settings::getThemeIcon("mesh-viewer")
        );

    m_centralLayout->addWidget(m_meshViewerButton);
}
