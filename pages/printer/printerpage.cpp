#include "printerpage.h"
#include "ui_printerpage.h"
#include "../../system/settings.h"

PrinterPage::PrinterPage(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PrinterPage)
{
    ui->setupUi(this);
    setupUiClasses();
    ui->TitleBar->setHidden(true);

    _bedTemperatureBar = new CircularProgressBar(this);
    _chamberTemperatureBar = new CircularProgressBar(this);
    //_extruderTemperatureBar = new CircularProgressBar(this);

    ui->chamberLayout->addWidget(_chamberTemperatureBar);
    ui->chamberWidget->setHidden(true);
    ui->bedLayout->addWidget(_bedTemperatureBar);

    ui->tabWidget->setTabVisible(0, false);
    ui->tabWidget->setTabVisible(1, false);
    ui->tabWidget->setTabVisible(2, false);
    ui->tabWidget->setTabVisible(3, false);
    ui->tabWidget->setTabVisible(4, false);
    ui->tabWidget->setCurrentIndex(0);
}

PrinterPage::~PrinterPage()
{
    delete ui;
}

void PrinterPage::addExtruder(Extruder *extruder, QString name)
{
    if(name == QString("Extruder") && _extruderMap.count() >= 1)
        name = QString("Extruder #") + QString::number(_extruderMap.count() + 1);

    int index = _extruderMap.count();

    _extruderMap[index] = new ExtruderWidget(this);
    _extruderMap[index]->setExtruder(extruder);
    ui->extruderTabWidget->addTab(_extruderMap[index], name);
}

void PrinterPage::setStyleSheet(QString style)
{
    for(int i = 0; i < _extruderMap.count(); i++)
    {
        _extruderMap[i]->setStyleSheet(style);
    }
    QPixmap pixmap = Settings::getThemeIcon(QString("printer")).pixmap(50,50);
    ui->printerIconLabel->setPixmap(pixmap);

}

void PrinterPage::setupUiClasses()
{
    ui->filePageTitle->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageTitle"));
    ui->actionBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageActionBar"));
    ui->pageContents->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageContents"));
    ui->TitleBar->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PageTitleBar"));
    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->tabWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->bedWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget"));
    ui->chamberWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget"));
    ui->toolheadWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget"));
    ui->fanFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget"));
    ui->currentPositionFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));
    ui->destinationPositionFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardSubWidget" << "PrinterSubWidget"));
    ui->settingsFrame->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget"));
    ui->extruderTabWidget->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "DashboardWidget" << "PrinterWidget"));
}

void PrinterPage::on_xPosDecreaseButton_clicked()
{

}

void PrinterPage::on_terminalButton_toggled(bool checked)
{
    if(checked)
        ui->tabWidget->setCurrentIndex(1);
}


void PrinterPage::on_overviewButton_toggled(bool checked)
{
    if(checked)
        ui->tabWidget->setCurrentIndex(0);
}


void PrinterPage::on_filesButton_toggled(bool checked)
{
    if(checked)
        ui->tabWidget->setCurrentIndex(2);
}


void PrinterPage::on_bedMeshButton_toggled(bool checked)
{
    if(checked)
        ui->tabWidget->setCurrentIndex(3);
}


void PrinterPage::on_settingsButton_toggled(bool checked)
{
    if(checked)
        ui->tabWidget->setCurrentIndex(4);
}

void PrinterPage::on_printerUpdate(Printer *printer)
{

    if(_extruderMap.count() == 0)
    {
        for(int i = 0; i < printer->extruderCount(); i++)
            addExtruder(printer->extruder(i));
    }

    for(int i = 0; i < _extruderMap.count(); i++)
    {
        _extruderMap[i]->update();
        /*_extruderMap[i]->setCurrentTemp(printer->extruder(i)->currentTemp());
        _extruderMap[i]->setTargetTemp(printer->extruder(i)->targetTemp());
        _extruderMap[i]->setPower(printer->extruder(i)->power());
        _extruderMap[i]->setPressureAdvance(printer->extruder(i)->pressureAdvance());*/
    }

    /*ui->extruderPressureAdvanceEdit->setText(QString::number(printer->extruder(0)->pressureAdvance()));
    ui->extruderSmoothTimeEdit->setText(QString::number(printer->extruder(0)->smoothTime()));
    //ui->extruderPo->setText(QString::number(power));
    ui->materialWidget->setEnabled(printer->extruder(0)->canExtrude());*/

    _bedTemperatureBar->setProgress(printer->bed()->currentTemp());
    ui->bedTargetTempLabel->setText(QString::number(printer->bed()->targetTemp()) + QString("C"));
    ui->bedPowerLabel->setText(QString::number(printer->bed()->power()) + QString(""));

    ui->xLabel->setText(QString("X: ") + QString::number(printer->toolhead()->position().x()));
    ui->yLabel->setText(QString("Y: ") + QString::number(printer->toolhead()->position().y()));
    ui->zLabel->setText(QString("Z: ") + QString::number(printer->toolhead()->position().z()));

    ui->xDestinationLabel->setText(QString("X: ") + QString::number(printer->toolhead()->destination().x()));
    ui->yDestinationLabel->setText(QString("Y: ") + QString::number(printer->toolhead()->destination().y()));
    ui->zDestination->setText(QString("Z: ") + QString::number(printer->toolhead()->destination().z()));

    ui->etaLabel->setText(QString("ETA: ") + printer->printEndTime().toString());

    if(printer->toolhead()->homedAxes().isEmpty())
        ui->homedLabel->setText(QString("none"));
    else
        ui->homedLabel->setText(printer->toolhead()->homedAxes());

    ui->statusMessageLabel->setText(printer->statusMessage());
    QString status;

    switch(printer->status())
    {
    case Printer::Ready:
        status = QString("Ready");
        break;
    case Printer::Error:
        status = QString("Error");
        break;
    case Printer::Cancelled:
        status = QString("Cancelled");
        break;
    case Printer::Printing:
        status = QString("Printing");
        break;
    case Printer::Paused:
        status = QString("Paused");
        break;
    default:
        status = QString("Unknown");
        break;
    }

    ui->printStatusLabel->setText(QString("State: ") + status);

    if(printer->status() != Printer::Printing)
    {
        ui->xPosDecreaseButton->setEnabled(printer->toolhead()->isXHomed());
        ui->xPosIncreaseButton->setEnabled(printer->toolhead()->isXHomed());
        ui->yPosDecreaseButton->setEnabled(printer->toolhead()->isYHomed());
        ui->yPosIncreaseButton->setEnabled(printer->toolhead()->isYHomed());
        ui->zPosDecreaseButton->setEnabled(printer->toolhead()->isZHomed());
        ui->zPosIncreaseButton->setEnabled(printer->toolhead()->isZHomed());
    }
    else
    {
        ui->xPosDecreaseButton->setEnabled(false);
        ui->xPosIncreaseButton->setEnabled(false);
        ui->yPosDecreaseButton->setEnabled(false);
        ui->yPosIncreaseButton->setEnabled(false);
        ui->zPosDecreaseButton->setEnabled(false);
        ui->zPosIncreaseButton->setEnabled(false);
    }

    //ui->pa->setText(QString::number(printer->toolhead()->fan()->speed()));
}

Printer *PrinterPage::printer() const
{
    return _printer;
}

void PrinterPage::setPrinter(Printer *printer)
{
    if(_printer)
        disconnect(_printer, SIGNAL(printerUpdate(Printer*)), this, SLOT(on_printerUpdate(Printer*)));

    _printer = printer;
    connect(_printer, SIGNAL(printerUpdate(Printer*)), this, SLOT(on_printerUpdate(Printer*)));
}

