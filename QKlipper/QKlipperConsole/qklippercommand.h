#ifndef QKLIPPERCOMMAND_H
#define QKLIPPERCOMMAND_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

#ifndef QKLIPPERCOMMAND_OPTIONAL_DELIMETER
#define QKLIPPERCOMMAND_OPTIONAL_DELIMETER = "$"
#endif

#ifndef QKLIPPERCOMMAND_REQUIRED_DELIMETER
#define QKLIPPERCOMMAND_REQUIRED_DELIMETER = "!"
#endif

class QKlipperCommand
{
    public:
        QKlipperCommand(QString command = QString());
        ~QKlipperCommand() = default;

        QKlipperCommand(const QKlipperCommand &value);
        QKlipperCommand &operator=(const QKlipperCommand &value);

        bool operator==(const QKlipperCommand &value) const;
        bool operator!=(const QKlipperCommand &value) const { return !(*this == value); }

        static bool isKlipperCommand(const QString &command);

        QString command() const { return m_command; }
        QString help() const { return m_help; }
        QStringList parameters() const { return m_parameters; }

        void setCommand(const QString &command) { m_command = command; }
        void setHelp(const QString &help) { m_help = help; }
        void setParameter(const QString &key) { m_parameters += key; }

    private:
        static void initialize();

        inline static QMap<QString, QKlipperCommand*> m_commands;
        inline static bool m_isInitialized = false;
        inline static bool m_isInitializing = false;

        QString m_command;
        QString m_help;
        QStringList m_parameters;
};

Q_DECLARE_METATYPE(QKlipperCommand)
#endif // QKLIPPERCOMMAND_H
