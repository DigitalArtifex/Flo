#include "addextruderspage.h"
#include "ui_addextruderspage.h"

AddExtrudersPage::AddExtrudersPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::AddExtrudersPage)
{
    ui->setupUi(this);
}

AddExtrudersPage::~AddExtrudersPage()
{
    delete ui;
}

void AddExtrudersPage::reset()
{
    QList<QDoubleSpinBox*> edits = findChildren<QDoubleSpinBox*>();

    for(int c = 0; c < edits.count(); c++)
    {
        if(edits[c] != nullptr)
        {
            if (edits[c]->property("extruder").isValid())
            {
                int extruder = edits[c]->property("extruder").toInt();
                edits[c]->setValue(_definition.powerProfile[(QString("extruder") + ((extruder > 0) ? QString::number(extruder) : QString("")))]);
            }
        }
    }
}

void AddExtrudersPage::apply()
{
    QList<QDoubleSpinBox*> edits = findChildren<QDoubleSpinBox*>();

    for(int c = 0; c < edits.count(); c++)
    {
        if(edits[c] != nullptr)
        {
            if (edits[c]->property("extruder").isValid())
            {
                int extruder = edits[c]->property("extruder").toInt();
                qreal extruderPower = edits[c]->text().toFloat();
                _definition.powerProfile[(QString("extruder") + ((extruder > 0) ? QString::number(extruder) : QString("")))] = extruderPower;
            }
        }
    }
}

void AddExtrudersPage::on_extruderCountSpinBox_valueChanged(int arg1)
{
    layout()->removeItem(ui->profileSpacer);
    layout()->removeItem(ui->profileSpacer_2);

    if(arg1 > _extruderCount)
    {
        for(int i = _extruderCount; i < arg1; i++)
        {
            QLabel *_extruderLabel = new QLabel();
            _extruderLabel->setProperty("extruder", i);
            _extruderLabel->setText(QString("Extruder ") + ((i > 0) ? QString::number(i) : QString("")));

            QDoubleSpinBox *_extruderWattEdit = new QDoubleSpinBox();
            _extruderWattEdit->setProperty("extruder", i);
            _extruderWattEdit->setAlignment(Qt::AlignRight);
            _extruderWattEdit->setValue(_definition.powerProfile[(QString("extruder") + ((i > 0) ? QString::number(i) : QString("")))]);

            layout()->addWidget(_extruderLabel);
            layout()->addWidget(_extruderWattEdit);
        }
    }
    else
    {
        for(int i = _extruderCount - 1; i >= arg1; i--)
        {
            QList<QLabel*> labels = findChildren<QLabel*>();

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

            QList<QDoubleSpinBox*> edits = findChildren<QDoubleSpinBox*>();

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

    layout()->addItem(ui->profileSpacer);
    layout()->addItem(ui->profileSpacer_2);

    _definition.extruderCount = arg1;
    _extruderCount = arg1;
}

PrinterDefinition AddExtrudersPage::definition() const
{
    return _definition;
}

void AddExtrudersPage::setDefinition(PrinterDefinition definition)
{
    _definition = definition;
    ui->extruderCountSpinBox->setValue(definition.extruderCount);
    reset();
}

bool AddExtrudersPage::validate()
{
    apply();
    return true;
}

