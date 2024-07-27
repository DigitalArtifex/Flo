#include "settings.h"

QMap<QString,QVariant> Settings::settings;
QMap<QString,QVariant> Settings::themeSettings;
QMap<QString,QString> Settings::themeMap;
QMap<QString,QIcon> Settings::iconMap;
PrinterDefinitionList Settings::m_printers;
Settings *Settings::m_instance = nullptr;
QString Settings::m_currentTheme = "";
QString Settings::m_digitalFontFamily = "";
QVariableStyleSheet Settings::m_theme;

void Settings::loadThemes()
{
    qDebug() << "Themes";
    QDir presetDir(QString(Settings::get("system.theme_location").toString()));

    if(!themeMap.isEmpty())
        themeMap.empty();

    if(presetDir.exists())
    {
        QDirIterator directoryIterator(presetDir.absolutePath(), QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

        while(directoryIterator.hasNext())
        {
            directoryIterator.next();

            QDir subdirectory(presetDir.absolutePath() + QDir::separator() + directoryIterator.fileName());
            QStringList subdirectoryFiles = subdirectory.entryList(QStringList() << "theme.json",QDir::Files);

            if(subdirectoryFiles.isEmpty())
                continue;

            foreach(QString subdirectoryFile, subdirectoryFiles)
            {
                //Load the JSON information
                QFile documentFile(subdirectory.absolutePath() + QDir::separator() + subdirectoryFile);

                qDebug() << ">> " + subdirectory.absolutePath() + QDir::separator() + subdirectoryFile;
                //Missing or corrupt files are just skipped for now
                if(!documentFile.open(QFile::ReadOnly))
                    continue;

                QJsonParseError documentError;
                QJsonDocument document = QJsonDocument::fromJson(documentFile.readAll(), &documentError);

                documentFile.close();

                //TODO: Error log
                if(documentError.error != QJsonParseError::NoError)
                    continue;

                QJsonObject documentObject = document.object();

                QString themeFileLocation = subdirectory.absolutePath() + QDir::separator() + "theme.css";
                themeMap[documentObject["name"].toString()] = themeFileLocation;
            }
        }
    }

    if(m_currentTheme.isEmpty())
        m_currentTheme = getTheme(get("system.theme").toString());
}

void Settings::load()
{
    int id = QFontDatabase::addApplicationFont(":/fonts/digital-7(mono).ttf");
    m_digitalFontFamily = QFontDatabase::applicationFontFamilies(id).at(0);

    qDebug() << "Settings File";
    QString settingsFileLocation = QDir::homePath() + QDir::separator() + QString(".local") +
                                   QDir::separator() + QString("share") + QDir::separator() +
                                   QString("flo") + QDir::separator();

    QDir settingsDirectory(settingsFileLocation);
    QFile settingsFile(settingsFileLocation + QString("config.json"));

    if(!settingsDirectory.exists())
    {
        settingsDirectory.mkpath(".");
        settingsDirectory.mkdir("presets");
    }

    if(!settingsFile.exists())
        reset();

    if(settingsFile.open(QFile::ReadOnly))
    {
        QByteArray settingsData = settingsFile.readAll();

        settingsFile.close();

        QJsonParseError settingsDataError;
        QJsonObject settingsObject = QJsonDocument::fromJson(settingsData, &settingsDataError).object();
        QJsonObject::Iterator settingsIterator;

        if(settingsDataError.error != QJsonParseError::NoError)
        {
            reset();
            loadThemes();
            return;
        }

        m_printers.clear();

        for(settingsIterator = settingsObject.begin(); settingsIterator != settingsObject.end(); settingsIterator++)
        {
            if(settingsIterator->isArray())
            {
                if(settingsIterator.key() == QString("printers"))
                {
                    QJsonArray settingsArray = settingsIterator->toArray();
                    for(int i = 0; i < settingsArray.count(); i++)
                    {
                        QJsonObject printerObject = settingsArray[i].toObject();
                        PrinterDefinition printer;
                        printer.id = printerObject["id"].toString();
                        printer.name = printerObject["name"].toString();
                        printer.instanceLocation = printerObject["instance_location"].toString();
                        printer.gcodeLocation = printerObject["gcode_location"].toString();
                        printer.configLocation = printerObject["config_location"].toString();
                        printer.klipperLocation = printerObject["klipper_location"].toString();
                        printer.moonrakerLocation = printerObject["moonraker_location"].toString();
                        printer.configFile = printerObject["config_file"].toString();
                        printer.defaultPrinter = printerObject["default_printer"].toBool();
                        printer.autoConnect = printerObject["auto_connect"].toBool();
                        printer.apiKey = printerObject["api_key"].toString();
                        printer.color = printerObject["color"].toString();
                        printer.extruderCount = printerObject["extruder_count"].toInt();

                        QJsonArray powerArray = printerObject["power_profile"].toArray();

                        for(int i = 0; i < powerArray.count(); i++)
                        {
                            QJsonObject powerObject = powerArray[i].toObject();
                            QString key = powerObject["key"].toString();
                            qreal value = powerObject["value"].toDouble();

                            printer.powerProfile[key] = value;
                        }

                        m_printers.append(printer);
                    }
                }
            }
            else
                set(settingsIterator.key(), settingsIterator.value().toVariant());

        }
    }

    loadThemes();
}

void Settings::save()
{
    QString settingsFileLocation = QDir::homePath() + QDir::separator() + QString(".local") +
                                   QDir::separator() + QString("share") + QDir::separator() +
                                   QString("flo") + QDir::separator() + QString("config.json");
    QJsonObject rootObject;
    QMap<QString,QVariant>::Iterator mapIterator = settings.begin();

    for(mapIterator = settings.begin(); mapIterator != settings.end(); mapIterator++)
        rootObject[mapIterator.key()] = QJsonValue::fromVariant(mapIterator.value());

    QJsonArray printerArray;
    //QJsonArray::fromVariantList(m_printers);

    for(int i = 0; i < m_printers.count(); i++)
    {
        QJsonArray powerArray;
        QStringList keys = m_printers[i].powerProfile.keys();

        foreach(QString key, keys)
        {
            QJsonObject powerObject;
            powerObject["key"] = key;
            powerObject["value"] = m_printers[i].powerProfile[key];
            powerArray.append(powerObject);
        }

        QJsonObject printerObject;
        printerObject["name"] = m_printers[i].name;
        printerObject["id"] = m_printers[i].id;
        printerObject["config_file"] = m_printers[i].configFile;
        printerObject["config_location"] = m_printers[i].configLocation;
        printerObject["gcode_location"] = m_printers[i].gcodeLocation;
        printerObject["instance_location"] = m_printers[i].instanceLocation;
        printerObject["auto_connect"] = m_printers[i].autoConnect;
        printerObject["default_printer"] = m_printers[i].defaultPrinter;
        printerObject["klipper_location"] = m_printers[i].klipperLocation;
        printerObject["moonraker_location"] = m_printers[i].moonrakerLocation;
        printerObject["api_key"] = m_printers[i].apiKey;
        printerObject["color"] = m_printers[i].color;
        printerObject["extruder_count"] = m_printers[i].extruderCount;
        printerObject["power_profile"] = powerArray;

        printerArray.append(printerObject);
    }

    rootObject["printers"] = printerArray;

    if(QFile(settingsFileLocation).exists())
    {
        QFile(settingsFileLocation).moveToTrash();
    }

    QJsonDocument document(rootObject);
    QFile settingsFile(settingsFileLocation);

    if(settingsFile.open(QFile::ReadWrite))
    {
        QByteArray data = document.toJson();
        qint64 written = settingsFile.write(data, data.length());
        settingsFile.flush();
        settingsFile.close();
    }
}

void Settings::reset()
{
    QString settingsFileLocation = QDir::homePath() + QDir::separator() + QString(".local") +
                                   QDir::separator() + QString("share") + QDir::separator() +
                                   QString("flo") + QDir::separator();

    QString klipperBaseLocation = QDir::homePath() + QDir::separator() + QString("printer_data") +
                                  QDir::separator();

    QString comLocation = klipperBaseLocation  + "comms" + QDir::separator();
    QString gcodeLocation = klipperBaseLocation + "gcodes" + QDir::separator();
    QString presetLocation = settingsFileLocation + QString("presets") + QDir::separator();
    QString themeLocation = settingsFileLocation + QString("themes") + QDir::separator();

    set("system.base_location", settingsFileLocation);
    set("system.preset_location", presetLocation);
    set("system.klipper.com_location", comLocation);
    set("system.klipper.gcode_location", gcodeLocation);
    set("system.klipper.protocol","moonraker");
    set("system.theme", "System Theme");
    set("system.theme_location", themeLocation);

    save();
}

QVariant Settings::get(QString key)
{
    return settings[key];
}

void Settings::set(QString key, QVariant value)
{
    settings[key] = value;
}

QString Settings::getTheme(QString key)
{
    qDebug() << "Theme Load (" + key + ")";

    QFile themeFile(themeMap[key]);

    //Missing or corrupt files are just skipped for now
    if(!themeFile.open(QFile::ReadOnly))
        return QString();

    QString theme = themeFile.readAll();
    themeFile.close();

    QVariableStyleSheet sheet(theme);
    theme = sheet.process();

    m_theme = sheet;

    QMap<QString,QString> themeVariables = sheet.variables();

    foreach(QString key, themeVariables.keys())
        settings[QString("theme-") + key] = themeVariables[key];

    //For Debug
#ifdef THEME_DEBUG
    QFile alteredFile(themeMap[key] + QString("_debug"));
    if(alteredFile.open(QFile::WriteOnly))
    {
        alteredFile.write(theme.toUtf8());
        alteredFile.close();
    }
#endif

    QString themeLocation = QString(themeMap[key]).remove("theme.css");
    QString themeIconLocation = themeLocation + QDir::separator() + "icons" + QDir::separator();
    QFile themeConfig(themeLocation + "theme.json");

    //Missing or corrupt files are just skipped for now
    if(!themeConfig.open(QFile::ReadOnly))
        return QString();

    QJsonParseError themeError;
    QJsonObject themeObject = QJsonDocument::fromJson(themeConfig.readAll(), &themeError).object();

    themeConfig.close();

    if(themeError.error != QJsonParseError::NoError)
    {
        qDebug() << "Theme document parsing error";
        return QString();
    }

    QJsonArray themeIcons = themeObject["icons"].toArray();
    iconMap.empty();

    for(int i = 0; i < themeIcons.count(); i++)
    {
        QJsonObject themeIcon = themeIcons[i].toObject();

        if(themeIcon.contains("name") && themeIcon.contains("icon"))
        {
            QIcon loadedIcon(themeIconLocation + themeIcon["icon"].toString());
            iconMap[themeIcon["name"].toString()] = loadedIcon;
        }
    }

    m_currentTheme = theme;
    return theme;
}

QIcon Settings::getThemeIcon(QString key)
{
    return iconMap[key];
}

QStringList Settings::getThemeList()
{
    QStringList themes = themeMap.keys();
    return themes;
}

void Settings::setTheme(QString key)
{
    set("system.theme", key);
}

void Settings::addPrinter(PrinterDefinition printer)
{
    m_printers.append(printer);
    save();
}

void Settings::removePrinter(PrinterDefinition printer)
{
    for(int i = 0; i < m_printers.count(); i++)
    {
        if(m_printers[i].id == printer.id)
        {
            m_printers.removeAt(i);
            save();
        }
    }
}

void Settings::setDefaultPrinter(PrinterDefinition printer)
{
    for(int i = 0; i < m_printers.count(); i++)
    {
        if(m_printers[i].id == printer.id)
            m_printers[i].defaultPrinter = true;
        else
            m_printers[i].defaultPrinter = false;
    }

    save();
}

void Settings::updatePrinter(PrinterDefinition printer)
{
    for(int i = 0; i < m_printers.count(); i++)
    {
        if(m_printers[i].id == printer.id)
        {
            m_printers[i] = printer;
            break;
        }
    }
}

PrinterDefinitionList Settings::printers()
{
    return m_printers;
}

Settings *Settings::instance()
{
    if(m_instance == nullptr)
        m_instance = new Settings();

    return m_instance;
}

QString Settings::currentTheme()
{
    return m_currentTheme;
}

QString Settings::digitalFontFamily()
{
    return m_digitalFontFamily;
}

bool Settings::contains(QString key)
{
    return settings.contains(key);
}

QVariableStyleSheet Settings::theme()
{
    return m_theme;
}
