#include "qklippersafezhome.h"

QKlipperSafeZHome::QKlipperSafeZHome(QObject *parent)
    : QObject{parent}
{}

bool QKlipperSafeZHome::operator==(const QKlipperSafeZHome &value)
{
    if(m_homeXPosition != value.m_homeXPosition) return false;
    if(m_homeYPosition != value.m_homeYPosition) return false;
    if(m_speed != value.m_speed) return false;
    if(m_zHop != value.m_zHop) return false;
    if(m_zHopSpeed != value.m_zHopSpeed) return false;

    if(m_moveToPrevious != value.m_moveToPrevious) return false;

    return true;
}

bool QKlipperSafeZHome::operator==(QKlipperSafeZHome &&value)
{
    if(m_homeXPosition != value.m_homeXPosition) return false;
    if(m_homeYPosition != value.m_homeYPosition) return false;
    if(m_speed != value.m_speed) return false;
    if(m_zHop != value.m_zHop) return false;
    if(m_zHopSpeed != value.m_zHopSpeed) return false;

    if(m_moveToPrevious != value.m_moveToPrevious) return false;

    return true;
}

bool QKlipperSafeZHome::operator!=(const QKlipperSafeZHome &value)
{
    if(m_homeXPosition == value.m_homeXPosition &&
        m_homeYPosition == value.m_homeYPosition &&
        m_speed == value.m_speed &&
        m_zHop == value.m_zHop &&
        m_zHopSpeed == value.m_zHopSpeed &&
        m_moveToPrevious == value.m_moveToPrevious)
        return false;

    return true;
}

bool QKlipperSafeZHome::operator!=(QKlipperSafeZHome &&value)
{
    if(m_homeXPosition == value.m_homeXPosition &&
        m_homeYPosition == value.m_homeYPosition &&
        m_speed == value.m_speed &&
        m_zHop == value.m_zHop &&
        m_zHopSpeed == value.m_zHopSpeed &&
        m_moveToPrevious == value.m_moveToPrevious)
        return false;

    return true;
}

qreal QKlipperSafeZHome::homeXPosition() const
{
    return m_homeXPosition;
}

void QKlipperSafeZHome::setHomeXPosition(qreal homeXPosition)
{
    if (qFuzzyCompare(m_homeXPosition, homeXPosition))
        return;
    m_homeXPosition = homeXPosition;
    emit homeXPositionChanged();
}

qreal QKlipperSafeZHome::homeYPosition() const
{
    return m_homeYPosition;
}

void QKlipperSafeZHome::setHomeYPosition(qreal homeYPosition)
{
    if (qFuzzyCompare(m_homeYPosition, homeYPosition))
        return;
    m_homeYPosition = homeYPosition;
    emit homeYPositionChanged();
}

qreal QKlipperSafeZHome::speed() const
{
    return m_speed;
}

void QKlipperSafeZHome::setSpeed(qreal speed)
{
    if (qFuzzyCompare(m_speed, speed))
        return;
    m_speed = speed;
    emit speedChanged();
}

qreal QKlipperSafeZHome::zHop() const
{
    return m_zHop;
}

void QKlipperSafeZHome::setZHop(qreal zHop)
{
    if (qFuzzyCompare(m_zHop, zHop))
        return;
    m_zHop = zHop;
    emit zHopChanged();
}

qreal QKlipperSafeZHome::zHopSpeed() const
{
    return m_zHopSpeed;
}

void QKlipperSafeZHome::setZHopSpeed(qreal zHopSpeed)
{
    if (qFuzzyCompare(m_zHopSpeed, zHopSpeed))
        return;
    m_zHopSpeed = zHopSpeed;
    emit zHopSpeedChanged();
}

bool QKlipperSafeZHome::moveToPrevious() const
{
    return m_moveToPrevious;
}

void QKlipperSafeZHome::setMoveToPrevious(bool moveToPrevious)
{
    if (m_moveToPrevious == moveToPrevious)
        return;
    m_moveToPrevious = moveToPrevious;
    emit moveToPreviousChanged();
}
