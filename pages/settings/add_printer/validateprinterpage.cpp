#include "validateprinterpage.h"
#include "ui_validateprinterpage.h"

#include "../../../system/printerpool.h"

ValidatePrinterPage::ValidatePrinterPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::ValidatePrinterPage)
{
    ui->setupUi(this);
}

ValidatePrinterPage::~ValidatePrinterPage()
{
    delete ui;
    delete m_printer;
}

bool ValidatePrinterPage::validatePage()
{
    return m_validated;
}

void ValidatePrinterPage::setDefinition(PrinterDefinition definition)
{
    m_definition = definition;
    ui->textEdit->clear();

    //Validate directory structure
    QDir instanceDirectory(m_definition.instanceLocation);
    if(instanceDirectory.exists())
    {
        bool valid = true;
        ui->textEdit->append(QString("Scanning directory"));
        QStringList subDirs = instanceDirectory.entryList(QDir::Dirs);

        if(!subDirs.contains(QString("comms")))
            valid = false;
        else
        {
            QString location = m_definition.instanceLocation;
            location += QDir::separator() + QString("comms") + QDir::separator();

            if(QFile::exists(location + QString("klippy.sock")))
                m_definition.klipperLocation = location + QString("klippy.sock");
            else
                valid = false;

            if(QFile::exists(location + QString("moonraker.sock")))
                m_definition.moonrakerLocation = location + QString("moonraker.sock");
            else
                valid = false;
        }

        if(!subDirs.contains(QString("gcodes")))
            valid = false;
        else
        {
            QString location = m_definition.instanceLocation;
            location += QDir::separator() + QString("gcodes") + QDir::separator();
            m_definition.gcodeLocation = location;
        }

        if(!subDirs.contains(QString("logs")))
            valid = false;

        if(!subDirs.contains(QString("config")))
            valid = false;
        else
        {
            QString location = m_definition.instanceLocation;
            location += QDir::separator() + QString("config") + QDir::separator();
            m_definition.configLocation = location;
        }

        if(!valid)
        {
            ui->textEdit->append(QString("Invalid directory"));
            return;
        }
    }

    if(PrinterPool::printersAvailable() == 0)
        m_definition.defaultPrinter = true;

    m_printer = new Printer(m_definition);

    if(m_printer->isAutoConnect())
    {
        ui->textEdit->append(QString("Connecting to ") + m_printer->name());

        connect(m_printer, SIGNAL(moonrakerConnected(Printer*)), this, SLOT(on_moonrakerConnected(Printer*)));
        connect(m_printer, SIGNAL(printerOnline(Printer*)), this, SLOT(on_printerOnline(Printer*)));
        connect(m_printer, SIGNAL(klipperConnected(Printer*)), this, SLOT(on_klipperConnected(Printer*)));

        m_printer->console()->connectToMoonraker();
    }
    else
    {
        ui->textEdit->append(QString("Printer \'") + m_printer->name() + QString("\' is ready"));
        m_validated = true;
    }
}

PrinterDefinition ValidatePrinterPage::definition()
{
    return m_definition;
}

void ValidatePrinterPage::on_klipperConnected(Printer *printer)
{
    ui->textEdit->append(QString("--Klipper Connected"));
    m_validated = true;
}

void ValidatePrinterPage::on_printerOnline(Printer *printer)
{
    ui->textEdit->append(QString("Printer ") + m_printer->name() + QString(" Online"));
    m_validated = true;
}

void ValidatePrinterPage::on_moonrakerConnected(Printer *printer)
{
    ui->textEdit->append(QString("--Moonraker Connected"));
}
