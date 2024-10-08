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
                edits[c]->setValue(m_definition.powerProfile[(QString("extruder") + ((extruder > 0) ? QString::number(extruder) : QString("")))]);
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
                m_definition.powerProfile[(QString("extruder") + ((extruder > 0) ? QString::number(extruder) : QString("")))] = extruderPower;
            }
        }
    }

    qDebug() << "Extruder page " << m_definition.powerProfile;
}

void AddExtrudersPage::on_extruderCountSpinBox_valueChanged(int arg1)
{
    layout()->removeItem(ui->profileSpacer);
    layout()->removeItem(ui->profileSpacer_2);

    if(arg1 > m_extruderCount)
    {
        for(int i = m_extruderCount; i < arg1; i++)
        {
            QLabel *m_extruderLabel = new QLabel();
            m_extruderLabel->setProperty("extruder", i);
            m_extruderLabel->setText(QString("Extruder ") + ((i > 0) ? QString::number(i) : QString("")));

            QDoubleSpinBox *m_extruderWattEdit = new QDoubleSpinBox();
            m_extruderWattEdit->setProperty("extruder", i);
            m_extruderWattEdit->setAlignment(Qt::AlignRight);
            m_extruderWattEdit->setValue(m_definition.powerProfile[(QString("extruder") + ((i > 0) ? QString::number(i) : QString("")))]);

            layout()->addWidget(m_extruderLabel);
            layout()->addWidget(m_extruderWattEdit);
        }
    }
    else
    {
        for(int i = m_extruderCount - 1; i >= arg1; i--)
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

    m_definition.extruderCount = arg1;
    m_extruderCount = arg1;
}

PrinterDefinition AddExtrudersPage::definition() const
{
    return m_definition;
}

void AddExtrudersPage::setDefinition(PrinterDefinition definition)
{
    m_definition = definition;
    ui->extruderCountSpinBox->setValue(definition.extruderCount);
    reset();
}

bool AddExtrudersPage::validate()
{
    apply();
    return true;
}

