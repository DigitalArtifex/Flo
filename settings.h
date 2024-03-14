#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QVariant>
#include <QMap>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>

#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QRegularExpression>

#include <QIcon>

class Settings
{
    static QMap<QString,QVariant> settings;
    static QMap<QString,QVariant> themeSettings;
    static QMap<QString, QString> themeMap;
    static QMap<QString,QIcon> iconMap;
    static QString _loadedTheme;

    static void loadThemes();

public:
    static void load();
    static void save();
    static void reset();

    static QVariant get(QString key);
    static void set(QString key, QVariant value);

    static QString getTheme(QString key);
    static QIcon getThemeIcon(QString key);
    static QStringList getThemeList();
    static void setTheme(QString key);
};

#endif // SETTINGS_H
