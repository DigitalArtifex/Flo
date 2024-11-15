#include "qklippersteppermotor.h"

QKlipperStepperMotor::QKlipperStepperMotor(QObject *parent)
    : QObject{parent}
{}

QString QKlipperStepperMotor::name() const
{
    return m_name;
}

void QKlipperStepperMotor::setName(const QString &name)
{
    if (m_name == name)
        return;
    m_name = name;
    emit nameChanged();
}

qreal QKlipperStepperMotor::current() const
{
    return m_current;
}

void QKlipperStepperMotor::setCurrent(qreal current)
{
    if (qFuzzyCompare(m_current, current))
        return;
    m_current = current;
    emit currentChanged();
}

bool QKlipperStepperMotor::enabled() const
{
    return m_enabled;
}

void QKlipperStepperMotor::setEnabled(bool enabled)
{
    if (m_enabled == enabled)
        return;
    m_enabled = enabled;
    emit enabledChanged();
}
