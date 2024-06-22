#ifndef QSTEPPERMOTOR_H
#define QSTEPPERMOTOR_H

#include <QObject>

class QStepperMotor : public QObject
{
    Q_OBJECT
public:
    explicit QStepperMotor(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    qreal current() const;
    void setCurrent(qreal current);

    void setEnabled(bool enabled);
    bool isEnabled() const;

signals:
    void enabled(QStepperMotor *motor);
    void disabled(QStepperMotor *motor);

private:
    QString m_name;
    qreal m_current;
    bool m_enabled;
};

#endif // QSTEPPERMOTOR_H
