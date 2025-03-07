#include "piddialog.h"
#include "flo/settings.h"

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
    QString text = "<h1>PID Calibration</h1>\n\nPID (Proportional-Integral-Derivative) calibration for a heater is the process \
of tuning the three control parameters to achieve optimal temperature regulation. \
The proportional term (P) controls the heater output based on the current temperature \
error, providing immediate correction but potentially leading to steady-state error. \
The integral term (I) accumulates past errors to eliminate steady-state deviation, but \
excessive tuning can cause overshoot and instability. The derivative term (D) anticipates \
future errors by reacting to the rate of temperature change, helping to dampen oscillations \
but making the system sensitive to noise. Proper calibration balances these three terms to \
ensure fast response, minimal overshoot, and stable temperature control.";

    m_pidText = new QLabel(this);
    m_pidText->setWordWrap(true);
    m_pidText->setText(text);

    m_centralLayout->addWidget(m_pidText, 0, 0);
    m_centralLayout->addItem(new QSpacerItem(40, 40, QSizePolicy::Fixed, QSizePolicy::Fixed), 1, 0);

    //setup distance group box
    m_targetGroupBox = new QGroupBox(this);
    m_targetGroupBox->setTitle("Calibration Target");
    m_targetGroupBox->setLayout(new QHBoxLayout(m_targetGroupBox));

    m_targetSpinBox = new QDoubleSpinBox(m_targetGroupBox);
    m_targetSpinBox->setMaximum(300);
    m_targetGroupBox->layout()->addWidget(m_targetSpinBox);

    m_centralLayout->addWidget(m_targetGroupBox, 2, 0);
    m_centralLayout->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding), 3, 0);

    connect(m_targetSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setTarget(qreal)));

    //setup footer
    m_footerWidget = new QWidget(this);
    m_footerWidget->setLayout(new QHBoxLayout(m_footerWidget));
    m_footerWidget->layout()->setContentsMargins(0,0,0,0);
    m_centralLayout->addWidget(m_footerWidget, 4, 0);

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
