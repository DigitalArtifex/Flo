#include "editprinterdialog.h"
#include "flo/qklipperinstancepool.h"
#include "ui_editprinterdialog.h"

#include <flo/settings.h>

#include "validators/QHexColorValidator/qhexcolorvalidator.h"

EditPrinterDialog::EditPrinterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditPrinterDialog)
{
    ui->setupUi(this);
    connect(ui->printerInstanceLocationEdit, SIGNAL(textChanged(QString)), this, SLOT(on_printerInstanceLocationEdit_textChanged(QString)));

    ui->colorEdit->setValidator(new QHexColorValidator());
    ui->printerInstanceLocationEdit->setValidator(new QMoonrakerValidator());

    m_cancelButton = new QIconButton(ui->buttonBox);
    m_cancelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_cancelButton->setIcon(Settings::getThemeIcon("cancel"));
    m_cancelButton->setText("Cancel");
    ui->buttonBoxLayout->addWidget(m_cancelButton);

    m_applyButton = new QIconButton(ui->buttonBox);
    m_applyButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_applyButton->setIcon(Settings::getThemeIcon("accept"));
    m_applyButton->setText("Apply");
    ui->buttonBoxLayout->addWidget(m_applyButton);

    connect(m_resetButton, SIGNAL(clicked()), this, SLOT(onResetButtonClicked()));
    connect(m_applyButton, SIGNAL(clicked()), this, SLOT(onApplyButtonClicked()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));

    ui->chamberPowerSpinBox->setMaximum(1000);
    ui->bedPowerSpinBox->setMaximum(1000);
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
    if(m_newPrinter)
    {
        setWindowTitle("New Printer");

        ui->printerNameEdit->setText("");
        ui->printerInstanceLocationEdit->setText("");
        ui->bedPowerSpinBox->setValue(0);
        ui->chamberPowerSpinBox->setValue(0);
        ui->extruderCountSpinBox->setValue(1);

        QRandomGenerator64 colorGen(QDateTime::currentSecsSinceEpoch() / 2);
        int red = colorGen.bounded(0, 255);
        int green = colorGen.bounded(0, 255);
        int blue = colorGen.bounded(0, 255);

        QColor randomColor(red,green,blue);
        ui->colorEdit->setText(randomColor.name().toUpper());

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
                        extruder = m_instance->printer()->toolhead()->extruder(extruderName);

                    if(extruder)
                        edits[c]->setValue(0);
                }
            }
        }
    }
    else
    {
        setWindowTitle(m_instance->name());

        QStringList keys = m_instance->printer()->powerProfile().keys();

        QStringList extruderKeys = keys.filter(QRegularExpression("^extruder"));
        ui->extruderCountSpinBox->setValue(extruderKeys.count());

        //remove any previous heater labels/edits
        QList<QLabel*> heaterLabels = ui->heatersTab->findChildren<QLabel*>();
        QList<QDoubleSpinBox*> heaterSpinBoxes = ui->heatersTab->findChildren<QDoubleSpinBox*>();

        while(heaterLabels.count() > 0)
        {
            QLabel *heaterLabel = heaterLabels.takeAt(0);
            ui->heatersTab->layout()->removeWidget(heaterLabel);
            delete heaterLabel;
        }

        while(heaterSpinBoxes.count() > 0)
        {
            QDoubleSpinBox *heaterSpinBox = heaterSpinBoxes.takeAt(0);
            ui->heatersTab->layout()->removeWidget(heaterSpinBox);
            delete heaterSpinBox;
        }

        for(const QString &key : keys)
        {
            qreal value = m_instance->printer()->powerProfile().value(key);

            if(key == QString("bed"))
            {
                ui->heatedBedCheckbox->setChecked(m_instance->printer()->powerProfile().value(key) > 0);
                ui->bedPowerSpinBox->setValue(m_instance->printer()->powerProfile().value(key));
            }
            else if(key == QString("chamber"))
            {
                ui->heatedChamberCheckBox->setChecked(m_instance->printer()->powerProfile().value(key) > 0);
                ui->chamberPowerSpinBox->setValue(m_instance->printer()->powerProfile().value(key));
            }
            else if(key.startsWith("extruder"))
            {
                QList<QDoubleSpinBox*> edits = ui->profileTab->findChildren<QDoubleSpinBox*>();

                bool found = false;

                for(int c = 0; c < edits.count(); c++)
                {
                    if(edits[c] != nullptr)
                    {
                        if (edits[c]->property("extruder").isValid())
                        {
                            int index = edits[c]->property("extruder").toInt();

                            QString extruderName =QString("extruder") + ((index > 0) ? QString::number(index) : QString(""));

                            if(key == extruderName)
                            {
                                edits[c]->setValue(m_instance->printer()->powerProfile().value(key));
                                found = true;
                                break;
                            }
                        }
                    }
                }
            }
            else if(key.startsWith("heater_generic"))
            {
                QGridLayout *layout = (QGridLayout*)ui->heatersTab->layout();

                QString name = key;
                name.remove("heater_generic ");

                QLabel *heaterLabel = new QLabel(ui->heatersTab);
                heaterLabel->setText(name);

                QDoubleSpinBox *heaterSpinBox = new QDoubleSpinBox(ui->heatersTab);
                heaterSpinBox->setValue(m_instance->printer()->powerProfile().value(key));
                heaterSpinBox->setProperty("heater", key);
            }
        }

        ui->printerNameEdit->setText(m_instance->name());
        ui->printerInstanceLocationEdit->setText(m_instance->instanceLocation());
        ui->addressLineEdit->setText(m_instance->address());
        ui->printerKeyEdit->setText(m_instance->apiKey());
        ui->colorEdit->setText(m_instance->profileColor());
    }
}

void EditPrinterDialog::clear()
{
}

void EditPrinterDialog::apply()
{
    if(!m_instance)
        return;

    QList<QDoubleSpinBox*> edits = ui->extruderTab->findChildren<QDoubleSpinBox*>();

    for(int c = 0; c < edits.count(); c++)
    {
        if(edits[c] != nullptr)
        {
            if (edits[c]->property("extruder").isValid())
            {
                int index = edits[c]->property("extruder").toInt();
                qreal extruderPower = edits[c]->value();
                QString extruderName =QString("extruder") + ((index > 0) ? QString::number(index) : QString(""));

                m_instance->printer()->addPowerProfileData(extruderName, extruderPower);
            }
            else if (edits[c]->property("heater").isValid())
            {
                QString name = edits[c]->property("heater").toString();
                qreal power = edits[c]->value();

                m_instance->printer()->addPowerProfileData(name, power);
            }
        }
    }

    QList<QDoubleSpinBox*> heaterSpinBoxes = ui->heatersTab->findChildren<QDoubleSpinBox*>();

    for(int i = 0; i < heaterSpinBoxes.count(); i++)
    {
        if(heaterSpinBoxes[i]->property("heater").isValid())
        {
            QString heater = heaterSpinBoxes[i]->property("heater").toString();
            qreal power = heaterSpinBoxes[i]->value();

            m_instance->printer()->addPowerProfileData(heater, power);
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
        m_instance->printer()->addPowerProfileData(ui->chamberHeaterNameEdit->text(), ui->chamberPowerSpinBox->value());

    m_instance->printer()->addPowerProfileData("bed", ui->bedPowerSpinBox->value());

    m_instance->setAddress(ui->addressLineEdit->text());
    m_instance->setPort(ui->portSpinBox->value());
    m_instance->setApiKey(ui->printerKeyEdit->text());

    m_instance->setProfileColor(ui->colorEdit->text());

    done(QDialog::Accepted);
}


void EditPrinterDialog::on_extruderCountSpinBox_valueChanged(int arg1)
{
    QGridLayout *layout = (QGridLayout*)ui->extruderTab->layout();

    if(arg1 > m_extruderCount)
    {
        for(int i = m_extruderCount; i < arg1; i++)
        {
            int row = layout->rowCount();

            QLabel *m_extruderLabel = new QLabel(ui->extruderTab);
            m_extruderLabel->setProperty("extruder", i);
            m_extruderLabel->setText(QString("Extruder ") + ((i > 0) ? QString::number(i) : QString("")));

            QDoubleSpinBox *m_extruderWattEdit = new QDoubleSpinBox(ui->extruderTab);
            m_extruderWattEdit->setProperty("extruder", i);
            m_extruderWattEdit->setAlignment(Qt::AlignRight);

            if(m_instance)
                m_extruderWattEdit->setValue(m_instance->printer()->powerProfile()[(QString("extruder") + ((i > 0) ? QString::number(i) : QString("")))]);

            layout->addWidget(m_extruderLabel, row, 0, 1, 1);
            layout->addWidget(m_extruderWattEdit, row, 1, 1, 1);
        }
    }
    else
    {
        for(int i = m_extruderCount - 1; i >= arg1; i--)
        {
            QList<QLabel*> labels = ui->extruderTab->findChildren<QLabel*>();

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

            QList<QDoubleSpinBox*> edits = ui->extruderTab->findChildren<QDoubleSpinBox*>();

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

    m_extruderCount = arg1;
}

void EditPrinterDialog::on_printerInstanceLocationEdit_textChanged(QString text)
{
    Q_UNUSED(text)

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
    qDebug() << "Color" << arg1 << ui->colorEdit->hasAcceptableInput();

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
    ui->chamberHeaterNameEdit->setEnabled(checked);
    ui->chamberSensorNameEdit->setEnabled(checked);
}

void EditPrinterDialog::on_EditPrinterDialog_windowTitleChanged(const QString &title)
{
    ui->windowTitleLabel->setText(QString("<h2>%1</h2>").arg(title));
}

void EditPrinterDialog::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setIcons();
}

void EditPrinterDialog::setIcons()
{
    ui->printerBrowseFilesButton->setIcon(Settings::getThemeIcon("opened-folder"));
    ui->colorPickerButton->setIcon(Settings::getThemeIcon("color"));
}
