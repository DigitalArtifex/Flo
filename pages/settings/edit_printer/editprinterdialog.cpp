#include "editprinterdialog.h"
#include "ui_editprinterdialog.h"

#include "../../../system/printerpool.h"

EditPrinterDialog::EditPrinterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditPrinterDialog)
{
    ui->setupUi(this);
    ui->printerInstanceLocationEdit->setValidator(new QMoonrakerValidator());
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
    connect(ui->printerInstanceLocationEdit, SIGNAL(textChanged(QString)), this, SLOT(on_printerInstanceLocationEdit_textChanged(QString)));
}

EditPrinterDialog::~EditPrinterDialog()
{
    delete ui;
}

Printer *EditPrinterDialog::printer() const
{
    return _printer;
}

void EditPrinterDialog::setPrinter(Printer *printer)
{
    _printer = printer;
    setWindowTitle(_printer->name());

    ui->extruderCountSpinBox->setValue(_printer->toolhead()->extruderCount());
    reset();
}

void EditPrinterDialog::reset()
{
    setWindowTitle(_printer->name());

    ui->printerNameEdit->setText(_printer->name());
    ui->printerInstanceLocationEdit->setText(_printer->instanceLocation());
    ui->bedPowerSpinBox->setValue(_printer->bed()->watts());

    ui->printerAutoConnectCheckBox->setChecked(_printer->isAutoConnect());
    ui->printerDefaultPrinterCheckBox->setChecked(_printer->isDefaultPrinter());

    QList<QDoubleSpinBox*> edits = ui->profileTab->findChildren<QDoubleSpinBox*>();

    for(int c = 0; c < edits.count(); c++)
    {
        if(edits[c] != nullptr)
        {
            if (edits[c]->property("extruder").isValid())
            {
                int extruder = edits[c]->property("extruder").toInt();
                edits[c]->setValue(_printer->powerProfile()[(QString("extruder") + ((extruder > 0) ? QString::number(extruder) : QString("")))]);
            }
        }
    }
}

void EditPrinterDialog::clear()
{
    ui->extruderCountSpinBox->setValue(0);
    ui->bedPowerSpinBox->setValue(0);
    ui->chamberPowerSpinBox->setValue(0);
}

void EditPrinterDialog::apply()
{
    QList<QDoubleSpinBox*> edits = ui->profileTab->findChildren<QDoubleSpinBox*>();

    for(int c = 0; c < edits.count(); c++)
    {
        if(edits[c] != nullptr)
        {
            if (edits[c]->property("extruder").isValid())
            {
                int extruder = edits[c]->property("extruder").toInt();
                qreal extruderPower = edits[c]->text().toFloat();

                _printer->toolhead()->setExtruderMaxWatts(extruder,extruderPower);
            }
        }
    }

    if(ui->printerNameEdit->isModified())
        _printer->setName(ui->printerNameEdit->text());

    if(ui->printerInstanceLocationEdit->isModified())
        _printer->setInstanceLocation(ui->printerInstanceLocationEdit->text());

    _printer->bed()->setWatts(ui->bedPowerSpinBox->value());
    _printer->setApiKey(ui->printerKeyEdit->text());

    PrinterPool::updatePrinter(_printer->definition());
    clear();
    close();
}


void EditPrinterDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch(ui->buttonBox->buttonRole(button))
    {
    case QDialogButtonBox::ApplyRole:
        apply();
        break;
    case QDialogButtonBox::ResetRole:
        reset();
        break;
    case QDialogButtonBox::RejectRole:
    default:
        clear();
        break;
    }
}


void EditPrinterDialog::on_extruderCountSpinBox_valueChanged(int arg1)
{
    if(arg1 > _extruderCount)
    {
        for(int i = _extruderCount; i < arg1; i++)
        {
            QLabel *_extruderLabel = new QLabel(ui->profileTab);
            _extruderLabel->setProperty("extruder", i);
            _extruderLabel->setText(QString("Extruder ") + ((i > 0) ? QString::number(i) : QString("")));

            QDoubleSpinBox *_extruderWattEdit = new QDoubleSpinBox(ui->profileTab);
            _extruderWattEdit->setProperty("extruder", i);
            _extruderWattEdit->setAlignment(Qt::AlignRight);
            _extruderWattEdit->setValue(_printer->powerProfile()[(QString("extruder") + ((i > 0) ? QString::number(i) : QString("")))]);

            ui->profileTab->layout()->addWidget(_extruderLabel);
            ui->profileTab->layout()->addWidget(_extruderWattEdit);
        }
    }
    else
    {
        for(int i = _extruderCount - 1; i >= arg1; i--)
        {
            QList<QLabel*> labels = ui->profileTab->findChildren<QLabel*>();

            for(int c = 0; c < labels.count(); c++)
            {
                if(labels[c] != nullptr)
                {
                    if (labels[c]->property("extruder") == i)
                    {
                        delete labels[c];
                    }
                }
            }

            QList<QDoubleSpinBox*> edits = ui->profileTab->findChildren<QDoubleSpinBox*>();

            for(int c = 0; c < edits.count(); c++)
            {
                if(edits[c] != nullptr)
                {
                    if (edits[c]->property("extruder") == i)
                    {
                        delete edits[c];
                    }
                }
            }
        }
    }

    ui->profileTab->layout()->removeItem(ui->profileSpacer);
    ui->profileTab->layout()->addItem(ui->profileSpacer);
    ui->profileTab->layout()->addItem(ui->profileSpacer);
    _extruderCount = arg1;
}

void EditPrinterDialog::on_printerInstanceLocationEdit_textChanged(QString text)
{
    if(text.contains(_httpExpression))
    {
        ui->printerKeyEdit->setEnabled(true);
    }
    else
        ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(ui->printerInstanceLocationEdit->hasAcceptableInput());
}


void EditPrinterDialog::on_printerBrowseFilesButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory
    (
        this,
        tr("Open Directory"),
        QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    if(!dir.isEmpty())
        ui->printerInstanceLocationEdit->setText(dir);
}


void EditPrinterDialog::on_printerKeyEdit_textChanged(const QString &arg1)
{
    if(ui->printerInstanceLocationEdit->hasAcceptableInput())
        ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
}

