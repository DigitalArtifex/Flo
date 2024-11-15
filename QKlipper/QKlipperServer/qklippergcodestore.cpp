#include "qklippergcodestore.h"

QKlipperGCodeStore::QKlipperGCodeStore(QObject *parent)
    : QObject{parent}
{}

QList<QKlipperGCodeStoreValue> QKlipperGCodeStore::values() const
{
    return m_values;
}

QKlipperGCodeStoreValue QKlipperGCodeStore::value(qint32 index) const
{
    if(m_values.count() > index)
        return m_values[index];

    return QKlipperGCodeStoreValue();
}

void QKlipperGCodeStore::setValues(const QList<QKlipperGCodeStoreValue> &values)
{
    m_values.clear();
    m_values.append(values);

    emit valuesChanged();
}

void QKlipperGCodeStore::setValue(const QKlipperGCodeStoreValue &value)
{
    if(m_values.contains(value))
        return;

    m_values.append(value);
    emit valuesChanged();
}
