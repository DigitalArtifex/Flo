#include "qsteppermotor.h"

QStepperMotor::QStepperMotor(QObject *parent)
    : QObject{parent}
{}

QString QStepperMotor::name() const
{
    return m_name;
}

void QStepperMotor::setName(const QString &name)
{
    m_name = name;
}

qreal QStepperMotor::current() const
{
    return m_current;
}

void QStepperMotor::setCurrent(qreal current)
{
    m_current = current;
}

void QStepperMotor::setEnabled(bool enabled)
{
    m_enabled = enabled;
}

bool QStepperMotor::isEnabled() const
{
    return m_enabled;
}
