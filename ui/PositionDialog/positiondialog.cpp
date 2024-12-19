#include "positiondialog.h"

#include "system/settings.h"

PositionDialog::PositionDialog(QWidget *parent)
    : Dialog{parent}
{
    setupUi();
}

void PositionDialog::setupUi()
{
    setWindowTitle("Position Editor");
    m_centralLayout = new QGridLayout(this);
    setLayout(m_centralLayout);

    //setup x group box
    m_xGroupBox = new QGroupBox(this);
    m_xGroupBox->setTitle("X");
    m_xGroupBox->setLayout(new QHBoxLayout(m_xGroupBox));

    m_xSpinBox = new QDoubleSpinBox(m_xGroupBox);
    m_xGroupBox->layout()->addWidget(m_xSpinBox);

    m_xUnitLabel = new QLabel(m_xGroupBox);
    m_xUnitLabel->setText("mm");
    m_xUnitLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
    m_xGroupBox->layout()->addWidget(m_xUnitLabel);

    m_centralLayout->addWidget(m_xGroupBox, 0, 0);

    connect(m_xSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setX(qreal)));

    //setup y group box
    m_yGroupBox = new QGroupBox(this);
    m_yGroupBox->setTitle("Y");
    m_yGroupBox->setLayout(new QHBoxLayout(m_yGroupBox));

    m_ySpinBox = new QDoubleSpinBox(m_yGroupBox);
    m_yGroupBox->layout()->addWidget(m_ySpinBox);

    m_yUnitLabel = new QLabel(m_yGroupBox);
    m_yUnitLabel->setText("mm");
    m_yUnitLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
    m_yGroupBox->layout()->addWidget(m_yUnitLabel);

    m_centralLayout->addWidget(m_yGroupBox, 0, 1);

    connect(m_ySpinBox, SIGNAL(valueChanged(double)), this, SLOT(setY(qreal)));

    //setup y group box
    m_zGroupBox = new QGroupBox(this);
    m_zGroupBox->setTitle("Z");
    m_zGroupBox->setLayout(new QHBoxLayout(m_zGroupBox));

    m_zSpinBox = new QDoubleSpinBox(m_zGroupBox);
    m_zGroupBox->layout()->addWidget(m_zSpinBox);

    m_zUnitLabel = new QLabel(m_zGroupBox);
    m_zUnitLabel->setText("mm");
    m_zUnitLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
    m_zGroupBox->layout()->addWidget(m_zUnitLabel);

    m_centralLayout->addWidget(m_zGroupBox, 0, 2);

    connect(m_zSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setZ(qreal)));

    //setup footer
    m_footerWidget = new QWidget(this);
    m_footerWidget->setLayout(new QHBoxLayout(m_footerWidget));
    m_footerWidget->layout()->setContentsMargins(0,0,0,0);

    m_cancelButton = new QIconButton(m_footerWidget);
    m_cancelButton->setText("Cancel");
    m_cancelButton->setFixedHeight(50);
    m_cancelButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_footerWidget->layout()->addWidget(m_cancelButton);

    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    m_applyButton = new QIconButton(m_footerWidget);
    m_applyButton->setText("Accept");
    m_applyButton->setFixedHeight(50);
    m_applyButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_footerWidget->layout()->addWidget(m_applyButton);

    connect(m_applyButton, SIGNAL(clicked()), this, SLOT(accept()));

    m_centralLayout->addItem(new QSpacerItem(QSizePolicy::Expanding, QSizePolicy::Expanding),1,0);
    m_centralLayout->addWidget(m_footerWidget, 2, 0, 1, 3);

    m_applyButton->setIcon(Settings::getThemeIcon(QString("accept")));
    m_cancelButton->setIcon(Settings::getThemeIcon(QString("cancel")));
}

qreal PositionDialog::z() const
{
    return m_z;
}

void PositionDialog::setZ(qreal z)
{
    if (qFuzzyCompare(m_z, z))
        return;

    m_z = z;
    emit zChanged();
}

qreal PositionDialog::y() const
{
    return m_y;
}

void PositionDialog::setY(qreal y)
{
    if (qFuzzyCompare(m_y, y))
        return;

    m_y = y;
    emit yChanged();
}

qreal PositionDialog::x() const
{
    return m_x;
}

void PositionDialog::setX(qreal x)
{
    if (qFuzzyCompare(m_x, x))
        return;

    m_x = x;
    emit xChanged();
}
