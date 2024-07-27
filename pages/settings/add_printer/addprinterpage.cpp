#include "addprinterpage.h"
#include "ui_addprinterpage.h"

#include "../../../system/settings.h"
#include "../../../validators/QHexColorValidator/qhexcolorvalidator.h"

AddPrinterPage::AddPrinterPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::AddPrinterPage)
{
    ui->setupUi(this);
    QPixmap pixmap = Settings::getThemeIcon("printer").pixmap(200,200);
    ui->printerIconLabel->setPixmap(pixmap);
    ui->printerIconLabel->setScaledContents(true);

    ui->colorEdit->setValidator(new QHexColorValidator());

    QString randomColor("#");

    for(int i = 0; i < 6; i++)
        randomColor += hexCodes.at(QRandomGenerator::global()->bounded(15));

    ui->colorEdit->setText(randomColor);
}

AddPrinterPage::~AddPrinterPage()
{
    delete ui;
}

bool AddPrinterPage::validatePage()
{
    if(ui->nameEdit->text().isEmpty())
        return false;

    if(ui->instanceEdit->text().isEmpty())
        return false;

    if(ui->keyEdit->isEnabled() && ui->keyEdit->text().isEmpty())
        return false;

    if(!ui->colorEdit->hasAcceptableInput())
        return false;

    return true;
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
    definition.color = ui->colorEdit->text();

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
        QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks | QFileDialog::DontUseNativeDialog
    );

    if(!dir.isEmpty())
        ui->instanceEdit->setText(dir);
}


void AddPrinterPage::on_colorPickerButton_clicked()
{
    QColorDialog *colorDialog = new QColorDialog;
    colorDialog->setWindowFlags(Qt::Window);
    colorDialog->setOptions(
        /* do not use native dialog */
        QColorDialog::DontUseNativeDialog
        );

    QColor color = QColorDialog::getColor(QColor::fromString(ui->colorEdit->text()), this, ui->nameEdit->text(), QColorDialog::DontUseNativeDialog);

    if(color.isValid())
        ui->colorEdit->setText(color.name());
}


void AddPrinterPage::on_colorEdit_textChanged(const QString &arg1)
{
    if(ui->colorEdit->hasAcceptableInput())
    {
        ui->colorDisplayLabel->setStyleSheet(QString("background-color: ") + ui->colorEdit->text() + QString(";"));
    }
}

