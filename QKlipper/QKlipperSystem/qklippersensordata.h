#ifndef QKLIPPERSENSORDATA_H
#define QKLIPPERSENSORDATA_H

#include <QQmlEngine>
#include <QVariant>

class QKlipperConsole;

class QKlipperSensorData
{
        friend QKlipperConsole;
    public:
        QKlipperSensorData() = default;
        ~QKlipperSensorData() = default;
        QKlipperSensorData(const QKlipperSensorData &data);
        QKlipperSensorData(const QString &field,
                           const QString &provider,
                           const QString &description,
                           const QString &strategy,
                           const QString &units,
                           const QString &parameter,
                           const bool &initTracker = false,
                           const bool &excludePaused = false,
                           const bool &reportTotal = false,
                           const bool &reportMaximum = false,
                           const qint32 &precision = 0);

        bool operator == (const QKlipperSensorData &data) const;
        bool operator != (const QKlipperSensorData &data) const;
        QKlipperSensorData &operator=(const QKlipperSensorData &data);

        QString field() const;
        QString provider() const;
        QString description() const;
        QString strategy() const;
        QString units() const;
        QString parameter() const;
        bool initTracker() const;
        bool excludePaused() const;
        bool reportTotal() const;
        bool reportMaximum() const;
        qint32 precision() const;

        bool isValid() const;
        void setIsValid(bool isValid);

    protected:
        void setPrecision(qint32 precision);
        void setReportMaximum(bool reportMaximum);
        void setReportTotal(bool reportTotal);
        void setExcludePaused(bool excludePaused);
        void setInitTracker(bool initTracker);
        void setParameter(const QString &parameter);
        void setUnits(const QString &units);
        void setStrategy(const QString &strategy);
        void setDescription(const QString &description);
        void setProvider(const QString &provider);
        void setField(const QString &field);

    private:
        QString m_field;
        QString m_provider;
        QString m_description;
        QString m_strategy;
        QString m_units;
        QString m_parameter;

        bool m_initTracker = false;
        bool m_excludePaused = false;
        bool m_reportTotal = false;
        bool m_reportMaximum = false;
        bool m_isValid = false;

        qint32 m_precision = 0;
};

typedef QMap<QString, QKlipperSensorData> QKlipperSensorDataMap;

Q_DECLARE_METATYPE(QKlipperSensorData)
#endif // QKLIPPERSENSORDATA_H
