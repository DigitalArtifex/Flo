#ifndef QKLIPPERSENSOR_H
#define QKLIPPERSENSOR_H

#include <QObject>
#include <QQmlEngine>
#include "qklippersensordata.h"

class QKlipperConsole;

class QKlipperSensor : public QObject
{
        Q_OBJECT
        QML_ELEMENT

        friend QKlipperConsole;
    public:
        explicit QKlipperSensor(QObject *parent = nullptr);
        QKlipperSensor(QString id,
                       QString name,
                       QString type,
                       QMultiMap<QString, QVariant> values = QMultiMap<QString,QVariant>(),
                       QMap<QString, QString> parameters = QMap<QString,QString>(),
                       QKlipperSensorDataMap history = QKlipperSensorDataMap(),
                       QObject *parent = nullptr);

        QString id() const;

        QString friendlyName() const;

        QString type() const;

        QMap<QString, QString> parameterMap() const;

        QKlipperSensorDataMap history() const;

        QMultiMap<QString, QVariant> values() const;

    protected slots:
        void setId(const QString &id);

        void setFriendlyName(const QString &friendlyName);

        void setType(const QString &type);

        void addValue(QString name, QVariant value);
        void setValues(const QMultiMap<QString, QVariant> &values);

        void addParameter(const QString &name, const QString &units);
        void setParameterMap(const QMap<QString, QString> &parameterMap);

        void addHistory(const QKlipperSensorData &data);
        void setHistory(const QKlipperSensorDataMap &history);

    signals:
        void idChanged();
        void friendlyNameChanged();
        void typeChanged();
        void parameterMapChanged();
        void historyChanged();

        void valuesChanged();

    private:
        QString m_id;
        QString m_friendlyName;
        QString m_type;
        QMultiMap<QString, QVariant> m_values;
        QMap<QString, QString> m_parameterMap;
        QKlipperSensorDataMap m_history;

        Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged FINAL)
        Q_PROPERTY(QString friendlyName READ friendlyName WRITE setFriendlyName NOTIFY friendlyNameChanged FINAL)
        Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged FINAL)
        Q_PROPERTY(QMap<QString, QString> parameterMap READ parameterMap WRITE setParameterMap NOTIFY parameterMapChanged FINAL)
        Q_PROPERTY(QKlipperSensorDataMap history READ history WRITE setHistory NOTIFY historyChanged FINAL)
        Q_PROPERTY(QMultiMap<QString, QVariant> values READ values WRITE setValues NOTIFY valuesChanged FINAL)
};
typedef QMap<QString, QKlipperSensor*> QKlipperSensorMap;
#endif // QKLIPPERSENSOR_H
