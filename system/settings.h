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

#include <QFontDatabase>

#include "../types/printer.h"
#include "QVariableSytleSheet/qvariablestylesheet.h"

class Settings
{
    static QMap<QString,QVariant> settings;
    static QMap<QString,QVariant> themeSettings;
    static QMap<QString, QString> themeMap;
    static QMap<QString,QIcon> iconMap;
    static QString m_loadedTheme;

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

    static Printer *defaultPrinter();
    static void addPrinter(PrinterDefinition printer);
    static void removePrinter(PrinterDefinition printer);
    static void setDefaultPrinter(PrinterDefinition printer);
    static void updatePrinter(PrinterDefinition printer);
    static PrinterDefinitionList printers();

    static Settings *instance();

    static QString currentTheme();

    static QString digitalFontFamily();
    static bool contains(QString key);

    static QVariableStyleSheet theme();

private:
    static Settings *m_instance;
    static QVariableStyleSheet m_theme;
    static PrinterDefinitionList m_printers;
    static QString m_currentTheme;

    static QString m_digitalFontFamily;
};

#endif // SETTINGS_H
