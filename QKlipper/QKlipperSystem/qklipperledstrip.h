#ifndef QKLIPPERLEDSTRIP_H
#define QKLIPPERLEDSTRIP_H

#include <QObject>
#include <QQmlEngine>
#include <QMap>

class QKlipperConsole;

class QKlipperLedStrip : public QObject
{
        Q_OBJECT
        QML_ELEMENT

        friend QKlipperConsole;
    public:
        explicit QKlipperLedStrip(QObject *parent = nullptr);

        QString name() const;

        QString status() const;

        QString error() const;

        qint32 chainCount() const;

        qint32 preset() const;

        qint8 brightness() const;

        qint8 intensity() const;

        qint8 speed() const;

        bool isOn() const;

    public slots:
        void setIsOn(bool isOn);

        void setName(const QString &name);

        void setStatus(const QString &status);

        void setError(const QString &error);

        void setChainCount(qint32 chainCount);

        void setPreset(qint32 preset);

        void setBrightness(qint8 brightness);

        void setIntensity(qint8 intensity);

        void setSpeed(qint8 speed);

        void saveState();

    signals:

        void nameChanged();

        void statusChanged();

        void errorChanged();

        void chainCountChanged();

        void presetChanged();

        void brightnessChanged();

        void intensityChanged();

        void speedChanged();

        void isOnChanged();

    private:
        QString m_name;
        QString m_status;
        QString m_error;
        qint32 m_chainCount;
        qint32 m_preset;
        qint8 m_brightness;
        qint8 m_intensity;
        qint8 m_speed;
        bool m_isOn = false;

        Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
        Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged FINAL)
        Q_PROPERTY(QString error READ error WRITE setError NOTIFY errorChanged FINAL)
        Q_PROPERTY(qint32 chainCount READ chainCount WRITE setChainCount NOTIFY chainCountChanged FINAL)
        Q_PROPERTY(qint32 preset READ preset WRITE setPreset NOTIFY presetChanged FINAL)
        Q_PROPERTY(qint8 brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged FINAL)
        Q_PROPERTY(qint8 intensity READ intensity WRITE setIntensity NOTIFY intensityChanged FINAL)
        Q_PROPERTY(qint8 speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)
        Q_PROPERTY(bool isOn READ isOn WRITE setIsOn NOTIFY isOnChanged FINAL)
};

typedef QMap<QString, QKlipperLedStrip*> QKlipperLedStripList;
#endif // QKLIPPERLEDSTRIP_H
