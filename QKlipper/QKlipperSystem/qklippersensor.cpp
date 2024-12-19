#include "qklippersensor.h"

QKlipperSensor::QKlipperSensor(QObject *parent)
    : QObject{parent}
{}

QKlipperSensor::QKlipperSensor(QString id,
                               QString name,
                               QString type,
                               QMultiMap<QString, QVariant> values,
                               QMap<QString, QString> parameters,
                               QKlipperSensorDataMap history,
                               QObject *parent)
    : QObject(parent)
{
    m_id = id;
    m_friendlyName = name;
    m_type = type;
    m_values = values;
    m_parameterMap = parameters;
    m_history = history;
}

QString QKlipperSensor::id() const
{
    return m_id;
}

void QKlipperSensor::setId(const QString &id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged();
}

QString QKlipperSensor::friendlyName() const
{
    return m_friendlyName;
}

void QKlipperSensor::setFriendlyName(const QString &friendlyName)
{
    if (m_friendlyName == friendlyName)
        return;

    m_friendlyName = friendlyName;
    emit friendlyNameChanged();
}

QString QKlipperSensor::type() const
{
    return m_type;
}

void QKlipperSensor::setType(const QString &type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged();
}

void QKlipperSensor::addValue(QString name, QVariant value)
{
    m_values.insert(name, value);
    emit valuesChanged();
}

QKlipperSensorDataMap QKlipperSensor::history() const
{
    return m_history;
}

void QKlipperSensor::setHistory(const QKlipperSensorDataMap &history)
{
    if (m_history == history)
        return;

    m_history = history;
    emit historyChanged();
}

QMultiMap<QString, QVariant> QKlipperSensor::values() const
{
    return m_values;
}

void QKlipperSensor::setValues(const QMultiMap<QString, QVariant> &values)
{
    if (m_values == values)
        return;

    m_values = values;
    emit valuesChanged();
}

QMap<QString, QString> QKlipperSensor::parameterMap() const
{
    return m_parameterMap;
}

void QKlipperSensor::setParameterMap(const QMap<QString, QString> &parameterMap)
{
    if (m_parameterMap == parameterMap)
        return;

    m_parameterMap = parameterMap;
    emit parameterMapChanged();
}

void QKlipperSensor::addHistory(const QKlipperSensorData &data)
{
    if(m_history.contains(data.parameter()) && m_history[data.parameter()] == data)
        return;

    m_history.insert(data.parameter(), data);
    emit parameterMapChanged();
}

void QKlipperSensor::addParameter(const QString &name, const QString &units)
{
    if(m_parameterMap.contains(name) && m_parameterMap[name] == units)
        return;

    m_parameterMap.insert(name, units);
    emit parameterMapChanged();
}
