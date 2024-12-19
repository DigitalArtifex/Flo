#include "piddialog.h"
#include "system/settings.h"

PidDialog::PidDialog(QWidget *parent)
    : Dialog{parent}
{
    setupUi();
    setWindowTitle("PID Calibration Target");
}

void PidDialog::setupUi()
{
    m_centralLayout = new QGridLayout(this);
    setLayout(m_centralLayout);

    //setup distance group box
    m_targetGroupBox = new QGroupBox(this);
    m_targetGroupBox->setTitle("Calibration Target");
    m_targetGroupBox->setLayout(new QHBoxLayout(m_targetGroupBox));

    m_targetSpinBox = new QDoubleSpinBox(m_targetGroupBox);
    m_targetSpinBox->setMaximum(300);
    m_targetGroupBox->layout()->addWidget(m_targetSpinBox);

    m_centralLayout->addWidget(m_targetGroupBox, 0, 0);

    connect(m_targetSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setTarget(qreal)));

    //setup footer
    m_footerWidget = new QWidget(this);
    m_footerWidget->setLayout(new QHBoxLayout(m_footerWidget));
    m_footerWidget->layout()->setContentsMargins(0,0,0,0);
    m_centralLayout->addWidget(m_footerWidget);

    m_rejectButton = new QIconButton(m_footerWidget);
    m_rejectButton->setText("Cancel");
    m_rejectButton->setFixedHeight(50);
    m_rejectButton->setIcon(Settings::getThemeIcon("cancel"));
    m_rejectButton->setTextMargins(QMargins(34,0,0,0));
    m_rejectButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_footerWidget->layout()->addWidget(m_rejectButton);

    connect(m_rejectButton, SIGNAL(clicked()), this, SLOT(reject()));

    m_acceptButton = new QIconButton(m_footerWidget);
    m_acceptButton->setText("Accept");
    m_acceptButton->setFixedHeight(50);
    m_acceptButton->setIcon(Settings::getThemeIcon("accept"));
    m_acceptButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_footerWidget->layout()->addWidget(m_acceptButton);

    connect(m_acceptButton, SIGNAL(clicked()), this, SLOT(accept()));

    setupIcons();
}

void PidDialog::setupIcons()
{
    m_acceptButton->setIcon(Settings::getThemeIcon("accept"));
    m_rejectButton->setIcon(Settings::getThemeIcon("cancel"));
}

qreal PidDialog::target() const
{
    return m_target;
}

void PidDialog::setTarget(qreal target)
{
    if (qFuzzyCompare(m_target, target))
        return;

    m_target = target;
    emit targetChanged();
}

void PidDialog::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::StyleChange)
    {
        setupIcons();
    }

    QWidget::changeEvent(event);
}
