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
    qreal m_speed;
    qreal m_rpm;

    Printer *m_printer;
};

#endif // FAN_H
