#include "qsteppermotor.h"

QStepperMotor::QStepperMotor(QObject *parent)
    : QObject{parent}
{}

QString QStepperMotor::name() const
{
    return _name;
}

void QStepperMotor::setName(const QString &name)
{
    _name = name;
}

qreal QStepperMotor::current() const
{
    return _current;
}

void QStepperMotor::setCurrent(qreal current)
{
    _current = current;
}

void QStepperMotor::setEnabled(bool enabled)
{
    _enabled = enabled;
}

bool QStepperMotor::isEnabled() const
{
    return _enabled;
}
