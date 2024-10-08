#include "editprinterdialog.h"
#include "ui_editprinterdialog.h"

#include "../../../system/printerpool.h"
#include "../../../validators/QHexColorValidator/qhexcolorvalidator.h"

EditPrinterDialog::EditPrinterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditPrinterDialog)
{
    ui->setupUi(this);
    ui->printerInstanceLocationEdit->setValidator(new QMoonrakerValidator());
    ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
    connect(ui->printerInstanceLocationEdit, SIGNAL(textChanged(QString)), this, SLOT(on_printerInstanceLocationEdit_textChanged(QString)));

    ui->colorEdit->setValidator(new QHexColorValidator());
}

EditPrinterDialog::~EditPrinterDialog()
{
    delete ui;
}

Printer *EditPrinterDialog::printer() const
{
    return m_printer;
}

void EditPrinterDialog::setPrinter(Printer *printer)
{
    m_printer = printer;
    setWindowTitle(m_printer->name());

    ui->extruderCountSpinBox->setValue(m_printer->toolhead()->extruderCount());
    reset();
}

void EditPrinterDialog::reset()
{
    setWindowTitle(m_printer->name());

    ui->printerNameEdit->setText(m_printer->name());
    ui->printerInstanceLocationEdit->setText(m_printer->instanceLocation());
    ui->bedPowerSpinBox->setValue(m_printer->bed()->watts());

    ui->printerAutoConnectCheckBox->setChecked(m_printer->isAutoConnect());
    ui->printerDefaultPrinterCheckBox->setChecked(m_printer->isDefaultPrinter());

    QList<QDoubleSpinBox*> edits = ui->profileTab->findChildren<QDoubleSpinBox*>();

    for(int c = 0; c < edits.count(); c++)
    {
        if(edits[c] != nullptr)
        {
            if (edits[c]->property("extruder").isValid())
            {
                int extruder = edits[c]->property("extruder").toInt();
                edits[c]->setValue(m_printer->powerProfile()[(QString("extruder") + ((extruder > 0) ? QString::number(extruder) : QString("")))]);
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

                m_printer->toolhead()->setExtruderMaxWatts(extruder,extruderPower);
            }
        }
    }

    if(ui->printerNameEdit->isModified())
        m_printer->setName(ui->printerNameEdit->text());

    if(ui->printerInstanceLocationEdit->isModified())
        m_printer->setInstanceLocation(ui->printerInstanceLocationEdit->text());

    m_printer->bed()->setMaxWatts(ui->bedPowerSpinBox->value());
    m_printer->setApiKey(ui->printerKeyEdit->text());

    PrinterPool::updatePrinter(m_printer->definition());
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
    QGridLayout *layout = (QGridLayout*)ui->profileTab->layout();
    layout->removeItem(ui->profileSpacer);

    if(arg1 > m_extruderCount)
    {

        for(int i = m_extruderCount; i < arg1; i++)
        {
            int row = layout->rowCount();

            QLabel *m_extruderLabel = new QLabel(ui->profileTab);
            m_extruderLabel->setProperty("extruder", i);
            m_extruderLabel->setText(QString("Extruder ") + ((i > 0) ? QString::number(i) : QString("")));

            QDoubleSpinBox *m_extruderWattEdit = new QDoubleSpinBox(ui->profileTab);
            m_extruderWattEdit->setProperty("extruder", i);
            m_extruderWattEdit->setAlignment(Qt::AlignRight);
            m_extruderWattEdit->setValue(m_printer->powerProfile()[(QString("extruder") + ((i > 0) ? QString::number(i) : QString("")))]);

            layout->addWidget(m_extruderLabel, row, 0, 1, 1);
            layout->addWidget(m_extruderWattEdit, row, 1, 1, 3);
        }
    }
    else
    {
        for(int i = m_extruderCount - 1; i >= arg1; i--)
        {
            QList<QLabel*> labels = ui->profileTab->findChildren<QLabel*>();

            for(int c = 0; c < labels.count(); c++)
            {
                if(labels[c] != nullptr)
                {
                    if (labels[c]->property("extruder") == i)
                    {
                        layout->removeWidget(labels[c]);
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
                        layout->removeWidget(edits[c]);
                        delete edits[c];
                    }
                }
            }
        }
    }

    layout->addItem(ui->profileSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    m_extruderCount = arg1;
}

void EditPrinterDialog::on_printerInstanceLocationEdit_textChanged(QString text)
{
    if(text.contains(m_httpExpression))
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
        QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks | QFileDialog::DontUseNativeDialog
    );

    if(!dir.isEmpty())
        ui->printerInstanceLocationEdit->setText(dir);
}


void EditPrinterDialog::on_printerKeyEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    if(ui->printerInstanceLocationEdit->hasAcceptableInput())
        ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);
}


void EditPrinterDialog::on_colorEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)

    if(ui->colorEdit->hasAcceptableInput())
        ui->colorDisplayLabel->setStyleSheet(QString("background-color: ") + ui->colorEdit->text() + QString(";"));
}


void EditPrinterDialog::on_colorPickerButton_clicked()
{
    QColor color = QColorDialog::getColor(QColor::fromString(ui->colorEdit->text()), this, ui->printerNameEdit->text(), QColorDialog::DontUseNativeDialog);

    if(color.isValid())
        ui->colorEdit->setText(color.name());
}

