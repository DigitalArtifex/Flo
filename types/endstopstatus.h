#ifndef ENDSTOPSTATUS_H
#define ENDSTOPSTATUS_H

#include <QObject>

class EndstopStatus
{
    Q_GADGET
public:
    explicit EndstopStatus(QObject *parent = nullptr);

    bool x() const;
    void setX(bool x);

    bool y() const;
    void setY(bool y);

    bool z() const;
    void setZ(bool z);

private:
    bool m_x = false;
    bool m_y = false;
    bool m_z = false;
};

#endif // ENDSTOPSTATUS_H
