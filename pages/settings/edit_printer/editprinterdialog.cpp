#include "editprinterdialog.h"
#include "system/qklipperinstancepool.h"
#include "ui_editprinterdialog.h"

#include <system/settings.h>

#include "../../../validators/QHexColorValidator/qhexcolorvalidator.h"

EditPrinterDialog::EditPrinterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditPrinterDialog)
{
    ui->setupUi(this);
    connect(ui->printerInstanceLocationEdit, SIGNAL(textChanged(QString)), this, SLOT(on_printerInstanceLocationEdit_textChanged(QString)));

    ui->colorEdit->setValidator(new QHexColorValidator());
    ui->printerInstanceLocationEdit->setValidator(new QMoonrakerValidator());

    m_resetButton = new QIconButton(ui->buttonBox);
    m_resetButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_resetButton->setIcon(Settings::getThemeIcon("refresh"));
    m_resetButton->setIconAlignment(Qt::AlignCenter);
    ui->buttonBoxLayout->addWidget(m_resetButton);

    m_applyButton = new QIconButton(ui->buttonBox);
    m_applyButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_applyButton->setIcon(Settings::getThemeIcon("accept"));
    m_applyButton->setText("Apply");
    ui->buttonBoxLayout->addWidget(m_applyButton);

    m_cancelButton = new QIconButton(ui->buttonBox);
    m_cancelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_cancelButton->setIcon(Settings::getThemeIcon("cancel"));
    m_cancelButton->setText("Cancel");
    ui->buttonBoxLayout->addWidget(m_cancelButton);

    connect(m_resetButton, SIGNAL(clicked()), this, SLOT(onResetButtonClicked()));
    connect(m_applyButton, SIGNAL(clicked()), this, SLOT(onApplyButtonClicked()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));

    reset();
}

EditPrinterDialog::~EditPrinterDialog()
{
    delete ui;
}

QKlipperInstance *EditPrinterDialog::printer() const
{
    return m_instance;
}

void EditPrinterDialog::setPrinter(QKlipperInstance *printer, bool newPrinter)
{
    m_instance = printer;
    setWindowTitle(m_instance->printer()->name());

    m_newPrinter = newPrinter;

    ui->extruderCountSpinBox->setValue(m_instance->printer()->toolhead()->extruderMap().count());
    reset();
}

void EditPrinterDialog::reset()
{
    if(!m_instance)
    {
        setWindowTitle("New Printer");

        ui->printerNameEdit->setText("");
        ui->printerInstanceLocationEdit->setText("");
        ui->bedPowerSpinBox->setValue(0);
        ui->chamberPowerSpinBox->setValue(0);
        ui->extruderCountSpinBox->setValue(1);

        QList<QDoubleSpinBox*> edits = ui->profileTab->findChildren<QDoubleSpinBox*>();

        for(int c = 0; c < edits.count(); c++)
        {
            if(edits[c] != nullptr)
            {
                if (edits[c]->property("extruder").isValid())
                {
                    int index = edits[c]->property("extruder").toInt();

                    QString extruderName =QString("extruder") + ((index > 0) ? QString::number(index) : QString(""));
                    QKlipperExtruder *extruder = nullptr;

                    if(m_instance)
                        m_instance->printer()->toolhead()->extruder(extruderName);

                    if(extruder)
                        edits[c]->setValue(0);
                }
            }
        }
    }
    else
    {
        setWindowTitle(m_instance->name());

        if(!m_instance->isConnected())
        {
            QSettings settings;

            //set group to power settings
            settings.beginGroup(m_instance->id() + "/power");

            m_instance->printer()->bed()->setMaxWatts(settings.value("bed", 360).toDouble());

            if(m_instance->printer()->toolhead()->extruderMap().count())
            {
                m_instance->printer()->toolhead()->extruder("extruder")->setMaxWatts(settings.value("extruder", 24).toDouble());

                for(int i = 1; i < m_instance->printer()->toolhead()->extruderMap().count(); i++)
                {
                    QString extruderName = QString("extruder%1").arg(QString::number(i));
                    m_instance->printer()->toolhead()->extruder(extruderName)->setMaxWatts(settings.value(extruderName, 24).toDouble());
                }
            }
        }

        ui->printerNameEdit->setText(m_instance->name());
        ui->printerInstanceLocationEdit->setText(m_instance->instanceLocation());
        ui->bedPowerSpinBox->setValue(m_instance->printer()->bed()->maxWatts());
        ui->extruderCountSpinBox->setValue(m_instance->printer()->toolhead()->extruderMap().count());
        ui->addressLineEdit->setText(m_instance->address());
        ui->chamberPowerSpinBox->setValue(m_instance->printer()->chamber()->maxWatts());
        ui->printerKeyEdit->setText(m_instance->apiKey());

        ui->heatedChamberCheckBox->setChecked(m_instance->printer()->hasChamber());
        ui->heatedChamberCheckBox->setChecked(m_instance->printer()->bed()->type() == QKlipperPrintBed::Heated);
        ui->colorEdit->setText(m_instance->profileColor());

        QList<QDoubleSpinBox*> edits = ui->profileTab->findChildren<QDoubleSpinBox*>();

        for(int c = 0; c < edits.count(); c++)
        {
            if(edits[c] != nullptr)
            {
                if (edits[c]->property("extruder").isValid())
                {
                    int index = edits[c]->property("extruder").toInt();

                    QString extruderName =QString("extruder") + ((index > 0) ? QString::number(index) : QString(""));
                    QKlipperExtruder *extruder = m_instance->printer()->toolhead()->extruder(extruderName);

                    if(extruder)
                        edits[c]->setValue(extruder->maxWatts());
                }
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
    if(!m_instance)
        return;

    QList<QDoubleSpinBox*> edits = ui->profileTab->findChildren<QDoubleSpinBox*>();

    for(int c = 0; c < edits.count(); c++)
    {
        if(edits[c] != nullptr)
        {
            if (edits[c]->property("extruder").isValid())
            {
                int index = edits[c]->property("extruder").toInt();
                qreal extruderPower = edits[c]->text().toFloat();

                QString extruderName =QString("extruder") + ((index > 0) ? QString::number(index) : QString(""));
                QKlipperExtruder *extruder = m_instance->printer()->toolhead()->extruder(extruderName);

                if(!extruder)
                {
                    extruder = new QKlipperExtruder(m_instance->printer()->toolhead());
                    m_instance->printer()->toolhead()->setExtruder(extruderName, extruder);
                }

                extruder->setMaxWatts(extruderPower);
            }
        }
    }

    m_instance->setName(ui->printerNameEdit->text());

    m_instance->setInstanceLocation(ui->printerInstanceLocationEdit->text());

    QString address = ui->addressLineEdit->text().toLower();

    if(address.startsWith("http://"))
        address.remove(0, 7);
    else if(address.startsWith("ws://"))
        address.remove(0,5);

    m_instance->printer()->setHasChamber(ui->heatedChamberCheckBox->isChecked());

    if(ui->heatedChamberCheckBox->isChecked())
        m_instance->printer()->chamber()->setMaxWatts(ui->chamberPowerSpinBox->value());
    else
        m_instance->printer()->chamber()->setMaxWatts(0);

    m_instance->setAddress(ui->addressLineEdit->text());
    m_instance->setPort(ui->portSpinBox->value());

    m_instance->printer()->bed()->setMaxWatts(ui->bedPowerSpinBox->value());
    m_instance->setApiKey(ui->printerKeyEdit->text());

    m_instance->setProfileColor(ui->colorEdit->text());

    done(QDialog::Accepted);
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

            if(m_instance)
                m_extruderWattEdit->setValue(m_instance->printer()->powerProfile()[(QString("extruder") + ((i > 0) ? QString::number(i) : QString("")))]);

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
                        labels[c]->deleteLater();
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
                        edits[c]->deleteLater();
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
        m_applyButton->setEnabled(true);
}


void EditPrinterDialog::on_colorEdit_textChanged(const QString &arg1)
{
    if(ui->colorEdit->hasAcceptableInput())
        ui->colorDisplayLabel->setStyleSheet(QString("background-color: ") + arg1 + QString(";"));
}

void EditPrinterDialog::on_colorPickerButton_clicked()
{
    QColor color = QColorDialog::getColor(QColor::fromString(ui->colorEdit->text()), this, ui->printerNameEdit->text(), QColorDialog::DontUseNativeDialog);

    if(color.isValid())
        ui->colorEdit->setText(color.name());
}


void EditPrinterDialog::on_printerNameEdit_textChanged(const QString &arg1)
{
    setWindowTitle(arg1);
}

void EditPrinterDialog::onResetButtonClicked()
{
    reset();
}

void EditPrinterDialog::onApplyButtonClicked()
{
    apply();
}

void EditPrinterDialog::onCancelButtonClicked()
{
    done(QDialog::Rejected);
}

void EditPrinterDialog::on_addressLineEdit_textChanged(const QString &arg1)
{
    if(arg1.length())
    {
        QRegularExpressionMatchIterator http = m_httpExpression.globalMatch(arg1);

        if(http.matchType() == QRegularExpression::NormalMatch)
        {
            m_remoteConnection = true;
            ui->printerInstanceLocationEdit->clear();
            ui->printerInstanceLocationEdit->setEnabled(false);
            ui->printerKeyEdit->setEnabled(true);
        }
        else
        {
            m_remoteConnection = false;
            ui->printerInstanceLocationEdit->setEnabled(true);
            ui->printerKeyEdit->clear();
            ui->printerKeyEdit->setEnabled(false);
        }
    }
}


void EditPrinterDialog::on_heatedBedCheckbox_toggled(bool checked)
{
    ui->bedPowerSpinBox->setEnabled(checked);
    ui->bedHeaterPowerLabel->setEnabled(checked);
}


void EditPrinterDialog::on_heatedChamberCheckBox_toggled(bool checked)
{
    ui->chamberPowerLabel->setEnabled(checked);
    ui->chamberPowerSpinBox->setEnabled(checked);
}

