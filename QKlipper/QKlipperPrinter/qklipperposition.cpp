#include "qklipperposition.h"

qreal &QKlipperPosition::operator [](const QString &name)
{
    return m_position[name];
}

bool QKlipperPosition::operator==(const QKlipperPosition &value)
{
    QStringList keys = value.m_position.keys();

    foreach(QString key, keys)
    {
        if(!m_position.contains(key))
            return false;
        else if(m_position[key] != value.position(key))
            return false;
    }

    return true;
}

bool QKlipperPosition::operator==(QKlipperPosition &&value)
{
    QStringList keys = value.m_position.keys();

    foreach(QString key, keys)
    {
        if(!m_position.contains(key))
            return false;
        else if(m_position[key] != value.position(key))
            return false;
    }

    return true;
}

bool QKlipperPosition::operator!=(const QKlipperPosition &value)
{
    QStringList keys = value.m_position.keys();

    foreach(QString key, keys)
    {
        if(!m_position.contains(key))
            return true;
        else if(m_position[key] != value.position(key))
            return true;
    }

    return true;
}

bool QKlipperPosition::operator!=(QKlipperPosition &&value)
{
    QStringList keys = value.m_position.keys();

    foreach(QString key, keys)
    {
        if(!m_position.contains(key))
            return true;
        else if(m_position[key] != value.position(key))
            return true;
    }

    return true;
}

qreal QKlipperPosition::x() const
{
    return m_position["x"];
}

qreal QKlipperPosition::y() const
{
    return m_position["y"];
}

qreal QKlipperPosition::z() const
{
    return m_position["z"];
}

qreal QKlipperPosition::position(const QString &name) const
{
    if(m_position.contains(name))
        return m_position[name];

    return 0.0;
}

qreal QKlipperPosition::e() const
{
    return m_position["e"];
}
