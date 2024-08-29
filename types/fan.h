#ifndef FAN_H
#define FAN_H

#include <QObject>

class Printer;

class Fan
{
    Q_GADGET
public:
    Fan(Printer *printer);
    ~Fan();

    qreal speed() const;
    void setSpeed(qreal speed);

    qreal rpm() const;
    void setRpm(qreal rpm);

    Printer *printer() const;
    void setPrinter(Printer *printer);

private:
    qreal m_speed = 0;
    qreal m_rpm = 0;
    bool m_isControllable = 0;

    Printer *m_printer;
};

#endif // FAN_H
