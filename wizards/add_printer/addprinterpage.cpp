#include "addprinterpage.h"
#include "ui_addprinterpage.h"

#include "../../settings.h"

AddPrinterPage::AddPrinterPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::AddPrinterPage)
{
    ui->setupUi(this);
    QPixmap pixmap = Settings::getThemeIcon("printer").pixmap(200,200);
    ui->printerIconLabel->setPixmap(pixmap);
    ui->printerIconLabel->setScaledContents(true);
}

AddPrinterPage::~AddPrinterPage()
{
    delete ui;
}

bool AddPrinterPage::isComplete()
{
    if(ui->nameEdit->text().isEmpty())
        return false;

    if(ui->instanceEdit->text().isEmpty())
        return false;

    if(ui->keyEdit->isEnabled() && ui->keyEdit->text().isEmpty())
        return false;

    return true;
}

bool AddPrinterPage::validatePage()
{
    return isComplete();
}

PrinterDefinition AddPrinterPage::definition()
{
    PrinterDefinition definition;
    definition.name = ui->nameEdit->text();
    definition.instanceLocation = ui->instanceEdit->text();
    definition.apiKey = ui->keyEdit->text();
    definition.autoConnect = ui->autoConnectCheckBox->isChecked();
    definition.defaultPrinter = ui->defaultPrinterCheckBox->isChecked();
    definition.id = QUuid::createUuid().toString();

    return definition;
}

void AddPrinterPage::on_instanceEdit_textChanged(const QString &arg1)
{
    if(arg1.contains(QRegularExpression("^\\s*(http|https)\\:\\/\\/")))
        ui->keyEdit->setEnabled(true);
    else
        ui->keyEdit->setEnabled(false);
}


void AddPrinterPage::on_browseFilesButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory
    (
        this,
        tr("Open Directory"),
        QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    if(!dir.isEmpty())
        ui->instanceEdit->setText(dir);
}

