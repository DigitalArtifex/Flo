#ifndef QKLIPPERPOWERDEVICE_H
#define QKLIPPERPOWERDEVICE_H

#include <QObject>
#include <QList>

class QKlipperConsole;

class QKlipperPowerDevice : public QObject
{
        Q_OBJECT
        friend QKlipperConsole;
    public:
        enum Type
        {
            GPIO,
            KlipperDevice,
            RfDevice,
            TpLink,
            Tasmota,
            Shelly,
            Homeseer,
            HomeAssistant,
            Loxonevl,
            SmartThings,
            Mqtt,
            PhilipsHue,
            HttpDevice,
            UHubCtl
        };

        explicit QKlipperPowerDevice(QObject *parent = nullptr);
        QKlipperPowerDevice(QString name, Type type, bool isOn, bool lockedWhilePrinting);

        QString name() const;

        bool isOn() const;

        bool lockedWhilePrinting() const;

        QString typeString() const;

        Type type() const;

    public slots:
        Q_INVOKABLE void turnOn();
        Q_INVOKABLE void turnOff();

        void setType(Type type);

    private slots:
        void setName(const QString &name);
        void setIsOn(bool isOn);
        void setLockedWhilePrinting(bool lockedWhilePrinting);
        void setTypeString(const QString &typeString);

    signals:
        void nameChanged();
        void isOnChanged();
        void lockedWhilePrintingChanged();

        void typeStringChanged();

        void typeChanged();

    private:
        const static inline QStringList m_typeNames = QStringList
            {
                "gpio",
                "klipper_device",
                "rf",
                "tplink_smartplug",
                "tasmota",
                "shelly",
                "homeseer",
                "homeassistant",
                "loxonev1",
                "smartthings",
                "mqtt",
                "hue",
                "http",
                "uhubctl"
            };

        QString m_name;
        QString m_typeString;
        Type m_type;

        bool m_isOn = false;
        bool m_lockedWhilePrinting = true;

        Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
        Q_PROPERTY(bool isOn READ isOn WRITE setIsOn NOTIFY isOnChanged FINAL)
        Q_PROPERTY(bool lockedWhilePrinting READ lockedWhilePrinting WRITE setLockedWhilePrinting NOTIFY lockedWhilePrintingChanged FINAL)
        Q_PROPERTY(QString typeString READ typeString WRITE setTypeString NOTIFY typeStringChanged FINAL)
        Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged FINAL)
};

typedef QMap<QString, QKlipperPowerDevice*> QKlipperPowerDeviceList;
#endif // QKLIPPERPOWERDEVICE_H
