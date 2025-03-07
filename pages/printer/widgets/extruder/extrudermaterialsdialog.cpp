#include "extrudermaterialsdialog.h"

#include "flo/settings.h"

ExtruderMaterialsDialog::ExtruderMaterialsDialog(QWidget *parent)
    : Dialog{parent}
{
    setWindowTitle("Extrude Material");
    setupUi();
}

void ExtruderMaterialsDialog::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::StyleChange)
    {
        setupIcons();
    }

    Dialog::changeEvent(event);
}

void ExtruderMaterialsDialog::setupUi()
{
    m_centralLayout = new QGridLayout(this);
    setLayout(m_centralLayout);

    //setup distance group box
    m_distanceGroupBox = new QGroupBox(this);
    m_distanceGroupBox->setTitle("Distance");
    m_distanceGroupBox->setLayout(new QHBoxLayout(m_distanceGroupBox));

    m_distanceSpinBox = new QDoubleSpinBox(m_distanceGroupBox);
    m_distanceSpinBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
    m_distanceGroupBox->layout()->addWidget(m_distanceSpinBox);

    m_distanceUnitLabel = new QLabel(m_distanceGroupBox);
    m_distanceUnitLabel->setText("mm");
    m_distanceUnitLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
    m_distanceGroupBox->layout()->addWidget(m_distanceUnitLabel);

    m_centralLayout->addWidget(m_distanceGroupBox, 0, 0);

    connect(m_distanceSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setDistance(qreal)));

    //setup speed group box
    m_speedGroupBox = new QGroupBox(this);
    m_speedGroupBox->setTitle("Speed");
    m_speedGroupBox->setLayout(new QHBoxLayout(m_speedGroupBox));

    m_speedSpinBox = new QDoubleSpinBox(m_speedGroupBox);
    m_speedSpinBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
    m_speedGroupBox->layout()->addWidget(m_speedSpinBox);

    m_speedUnitLabel = new QLabel(m_speedGroupBox);
    m_speedUnitLabel->setText("mm/s");
    m_speedUnitLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
    m_speedGroupBox->layout()->addWidget(m_speedUnitLabel);

    m_centralLayout->addWidget(m_speedGroupBox, 1, 0);
    m_centralLayout->addItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 0);
    connect(m_speedSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setSpeed(qreal)));

    //setup footer
    m_footerWidget = new QWidget(this);
    m_footerWidget->setLayout(new QHBoxLayout(m_footerWidget));
    m_footerWidget->layout()->setContentsMargins(0,0,0,0);

    m_cancelButton = new QIconButton(m_footerWidget);
    m_cancelButton->setText("Cancel");
    m_cancelButton->setFixedHeight(50);
    m_cancelButton->setTextMargins(QMargins(34,0,0,0));
    m_cancelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_footerWidget->layout()->addWidget(m_cancelButton);

    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    m_extrudeButton = new QIconButton(m_footerWidget);
    m_extrudeButton->setText("Extrude");
    m_extrudeButton->setFixedHeight(50);
    m_extrudeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_footerWidget->layout()->addWidget(m_extrudeButton);

    m_centralLayout->addItem(new QSpacerItem(QSizePolicy::Expanding, QSizePolicy::Expanding),2,0);
    m_centralLayout->addWidget(m_footerWidget, 3, 0, 1, 1);

    connect(m_extrudeButton, SIGNAL(clicked()), this, SLOT(accept()));

    setupIcons();
}

void ExtruderMaterialsDialog::setupIcons()
{
    switch(m_materialDirection)
    {
        case MaterialExtrude:
            m_extrudeButton->setIcon(Settings::getThemeIcon(QString("material-extrude")));
            break;
        case MaterialRetract:
            m_extrudeButton->setIcon(Settings::getThemeIcon(QString("material-retract")));
            break;
        case None:
        default:
            break;
    }

    m_cancelButton->setIcon(Settings::getThemeIcon(QString("cancel")));
}

qreal ExtruderMaterialsDialog::speed() const
{
    return m_speed;
}

void ExtruderMaterialsDialog::setSpeed(qreal speed)
{
    if (qFuzzyCompare(m_speed, speed))
        return;

    m_speed = speed;
    emit speedChanged();
}

qreal ExtruderMaterialsDialog::distance() const
{
    return m_distance;
}

void ExtruderMaterialsDialog::setDistance(qreal distance)
{
    if (qFuzzyCompare(m_distance, distance))
        return;

    m_distance = distance;
    emit distanceChanged();
}

ExtruderMaterialsDialog::MaterialDirection ExtruderMaterialsDialog::materialDirection() const
{
    return m_materialDirection;
}

void ExtruderMaterialsDialog::setMaterialDirection(MaterialDirection materialDirection)
{
    if (m_materialDirection == materialDirection)
        return;

    m_materialDirection = materialDirection;

    switch(m_materialDirection)
    {
        case MaterialExtrude:
            m_extrudeButton->setText("Extrude");
            setWindowTitle("Extrude Material");
            break;
        case MaterialRetract:
            m_extrudeButton->setText("Retract");
            setWindowTitle("Retract Material");
            break;
        case None:
        default:
            break;
    }

    setupIcons();

    emit materialDirectionChanged();
}
