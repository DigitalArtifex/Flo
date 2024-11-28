#include "qklipperledstrip.h"
#include "qklippersystem.h"
#include "../QKlipperInstance/qklipperinstance.h"

QKlipperLedStrip::QKlipperLedStrip(QObject *parent)
    : QObject{parent}
{

}

QString QKlipperLedStrip::name() const
{
    return m_name;
}

void QKlipperLedStrip::setName(const QString &name)
{
    if (m_name == name)
        return;
    m_name = name;
    emit nameChanged();
}

QString QKlipperLedStrip::status() const
{
    return m_status;
}

void QKlipperLedStrip::setStatus(const QString &status)
{
    if (m_status == status)
        return;

    m_status = status;
    emit statusChanged();

    setIsOn((m_status == "on"));
}

QString QKlipperLedStrip::error() const
{
    return m_error;
}

void QKlipperLedStrip::setError(const QString &error)
{
    if (m_error == error)
        return;
    m_error = error;
    emit errorChanged();
}

qint32 QKlipperLedStrip::chainCount() const
{
    return m_chainCount;
}

void QKlipperLedStrip::setChainCount(qint32 chainCount)
{
    if (m_chainCount == chainCount)
        return;
    m_chainCount = chainCount;
    emit chainCountChanged();
}

qint32 QKlipperLedStrip::preset() const
{
    return m_preset;
}

void QKlipperLedStrip::setPreset(qint32 preset)
{
    if (m_preset == preset)
        return;
    m_preset = preset;
    emit presetChanged();
}

qint8 QKlipperLedStrip::brightness() const
{
    return m_brightness;
}

void QKlipperLedStrip::setBrightness(qint8 brightness)
{
    if (m_brightness == brightness)
        return;

    m_brightness = brightness;
    emit brightnessChanged();
}

qint8 QKlipperLedStrip::intensity() const
{
    return m_intensity;
}

void QKlipperLedStrip::setIntensity(qint8 intensity)
{
    if (m_intensity == intensity)
        return;
    m_intensity = intensity;
    emit intensityChanged();
}

qint8 QKlipperLedStrip::speed() const
{
    return m_speed;
}

void QKlipperLedStrip::setSpeed(qint8 speed)
{
    if (m_speed == speed)
        return;

    m_speed = speed;
    emit speedChanged();
}

void QKlipperLedStrip::saveState()
{
    QKlipperSystem *system = qobject_cast<QKlipperSystem*>(parent());

    if(system)
    {
        QKlipperInstance *instance = qobject_cast<QKlipperInstance*>(system->parent());

        if(instance && instance->isConnected())
            instance->console()->machineSetLedStrip(this);
    }
}

bool QKlipperLedStrip::isOn() const
{
    return m_isOn;
}

void QKlipperLedStrip::setIsOn(bool isOn)
{
    if (m_isOn == isOn)
        return;
    m_isOn = isOn;
    emit isOnChanged();
}
