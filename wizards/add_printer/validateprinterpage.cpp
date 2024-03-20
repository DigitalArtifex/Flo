#include "validateprinterpage.h"
#include "ui_validateprinterpage.h"

ValidatePrinterPage::ValidatePrinterPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::ValidatePrinterPage)
{
    ui->setupUi(this);
}

ValidatePrinterPage::~ValidatePrinterPage()
{
    delete ui;
    delete _printer;
}

bool ValidatePrinterPage::validatePage()
{
    return _validated;
}

void ValidatePrinterPage::setDefinition(PrinterDefinition definition)
{
    ui->textEdit->clear();

    //Validate directory structure
    QDir instanceDirectory(definition.instanceLocation);
    if(instanceDirectory.exists())
    {
        bool valid = true;
        ui->textEdit->append(QString("Scanning directory"));
        QStringList subDirs = instanceDirectory.entryList(QDir::Dirs);

        if(!subDirs.contains(QString("comms")))
            valid = false;
        else
        {
            QString location = definition.instanceLocation;
            location += QDir::separator() + QString("comms") + QDir::separator();

            if(QFile::exists(location + QString("klippy.sock")))
                definition.klipperLocation = location + QString("klippy.sock");
            else
                valid = false;

            if(QFile::exists(location + QString("moonraker.sock")))
                definition.moonrakerLocation = location + QString("moonraker.sock");
            else
                valid = false;
        }

        if(!subDirs.contains(QString("gcodes")))
            valid = false;
        else
        {
            QString location = definition.instanceLocation;
            location += QDir::separator() + QString("gcodes") + QDir::separator();
            definition.gcodeLocation = location;
        }

        if(!subDirs.contains(QString("logs")))
            valid = false;

        if(!subDirs.contains(QString("config")))
            valid = false;
        else
        {
            QString location = definition.instanceLocation;
            location += QDir::separator() + QString("config") + QDir::separator();
            definition.configLocation = location;
        }

        if(!valid)
        {
            ui->textEdit->append(QString("Invalid directory"));
            return;
        }
    }

    _printer = new Printer(definition);

    ui->textEdit->append(QString("Connecting to ") + _printer->name());
    connect(_printer, SIGNAL(moonrakerConnected(Printer *)), this, SLOT(on_moonrakerConnected(Printer *)));
    connect(_printer, SIGNAL(printerOnline(Printer *)), this, SLOT(on_printerOnline(Printer *)));
    connect(_printer, SIGNAL(klipperConnected(Printer *)), this, SLOT(on_klipperConnected(Printer *)));
    _printer->console()->connectKlipper();
}

PrinterDefinition ValidatePrinterPage::definition()
{
    return _printer->definition();
}

void ValidatePrinterPage::on_klipperConnected(Printer *printer)
{
    ui->textEdit->append(QString("--Klipper Connected"));
    _validated = true;
}

void ValidatePrinterPage::on_printerOnline(Printer *printer)
{
    ui->textEdit->append(QString("Printer ") + _printer->name() + QString(" Online"));
    _validated = true;
}

void ValidatePrinterPage::on_moonrakerConnected(Printer *printer)
{
    ui->textEdit->append(QString("--Moonraker Connected"));
}
