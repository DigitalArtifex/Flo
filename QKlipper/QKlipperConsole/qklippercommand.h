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

class QKlipperCommand : public QVariant
{
public:
    QKlipperCommand(QString command = QString());
    static bool isKlipperCommand(const QString &command);

    QString command() const;
    QString help() const;
    QStringList parameters() const;

    void setCommand(const QString &command);
    void setHelp(const QString &help);
    void setParameter(const QString &key);

private:
    static QMap<QString, QKlipperCommand*> m_commands;
    static bool m_isInitialized;

    QString m_command;
    QString m_help;
    QStringList m_parameters;
};

#endif // QKLIPPERCOMMAND_H
