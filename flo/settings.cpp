#include "settings.h"
#include "qpainter.h"
#include "qpainterpath.h"
#include "qstandardpaths.h"
#include "flo/qklipperinstancepool.h"

QMap<QString,QVariant> Settings::themeSettings;
QMap<QString,QString> Settings::themeMap;
QMap<QString,QString> Settings::m_iconSetMap;
QMap<QString,QString> Settings::m_iconLocationMap;
QMap<QString,QIcon> Settings::m_iconMap;
QList<QKlipperInstance*> Settings::m_instances;
Settings *Settings::m_instance = nullptr;
bool Settings::m_instanceCreated = false;
QString Settings::m_currentTheme = "";
QString Settings::m_digitalFontFamily = "";
QString Settings::m_currentIconSetName = "";
QString Settings::m_currentThemeName = "";
QVariableStyleSheet Settings::m_theme;
Settings::AnimationStyle Settings::m_animationOutStyle = Settings::SlideBottom;
Settings::AnimationStyle Settings::m_animationInStyle = Settings::SlideTop;
bool Settings::m_isAnimationEnabled = true;
Settings::EffectsStyle Settings::m_animationEffectOutStyle = Settings::Opacity;
Settings::EffectsStyle Settings::m_animationEffectInStyle = Settings::Opacity;
bool Settings::m_isAnimationEffectsEnabled = true;
qint16 Settings::m_animationDuration = 500;

QStringList Settings::m_requestedIcons = QStringList();
QMap<QString,QString> Settings::m_iconNames = QMap<QString,QString>();

void Settings::loadThemes()
{
    QString themeLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + QDir::separator() + "themes";

    qDebug() << "Loading Themes" << themeLocation;
    QDir presetDir(themeLocation);

    if(!themeMap.isEmpty())
        themeMap.clear();

    if(presetDir.exists())
    {
        QStringList themeFiles = presetDir.entryList(QStringList() << "*.css", QDir::Files);

        for(QString themeFileEntry : themeFiles)
        {
            QString name = themeFileEntry;
            name.remove(".css");
            themeMap[name] = presetDir.absolutePath() + QDir::separator() + themeFileEntry;
        }
    }

    if(m_currentTheme.isEmpty())
    {
        m_currentThemeName = get("theme_name", "default").toString();
        m_currentTheme = getTheme(get("theme_name", "default").toString());
    }
}

void Settings::loadIconSets()
{
    QString iconsLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + QDir::separator() + "icons";

    qDebug() << "Loading Icons" << iconsLocation;
    QDir iconsDir(iconsLocation);

    if(!m_iconSetMap.isEmpty())
        m_iconSetMap.empty();

    if(iconsDir.exists())
    {
        QStringList iconSetDirectories = iconsDir.entryList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::NoSymLinks);

        for(const QString &dirLocation : iconSetDirectories)
        {
            QDir iconSetDirectory(iconsDir.absolutePath() + QDir::separator() + dirLocation);
            QStringList iconSetFiles = iconSetDirectory.entryList(QStringList() << "icons.json", QDir::Files | QDir::NoDotAndDotDot);

            for(const QString &iconSetEntry : iconSetFiles)
            {
                QString name = iconSetDirectory.dirName();
                m_iconSetMap[name] = iconSetDirectory.absolutePath() + QDir::separator() + iconSetEntry;
            }
        }

        if(m_currentIconSetName.isEmpty() && !iconSetDirectories.isEmpty())
            m_currentIconSetName = iconSetDirectories.contains("default") ? "default" : iconSetDirectories[0];
    }
}

void Settings::loadIcons()
{
    QMap<QString,QString> themeVariables = m_theme.variables();
    QString iconsLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + QDir::separator() + "icons";

    QString iconSetLocation = iconsLocation + QDir::separator() + m_currentIconSetName + QDir::separator();
    QFile iconSetConfig(iconSetLocation + "icons.json");

    //Missing or corrupt files are just skipped for now
    if(!iconSetConfig.open(QFile::ReadOnly))
    {
        QString warning = QString("Could not open icons file %1").arg(iconSetConfig.fileName());
        qWarning() << warning;
        return;
    }

    QJsonParseError themeError;
    QJsonObject themeObject = QJsonDocument::fromJson(iconSetConfig.readAll(), &themeError).object();

    iconSetConfig.close();

    if(themeError.error != QJsonParseError::NoError)
    {
        QString warning = QString("Could not parse icons file %1").arg(iconSetConfig.fileName());
        qWarning() << warning;
        return;
    }

    QJsonArray themeIcons = themeObject["icons"].toArray();
    m_iconMap.empty();

    for(int i = 0; i < themeIcons.count(); i++)
    {
        QJsonObject themeIcon = themeIcons[i].toObject();

        if(themeIcon.contains("name") && themeIcon.contains("icon"))
        {
            QIcon loadedIcon;
            m_iconNames[themeIcon["name"].toString()] = themeIcon["icon"].toString();

            if(themeVariables.contains("icon-color") && !themeIcon["icon"].toString().endsWith(".gif", Qt::CaseInsensitive))
            {
                QImage image(iconSetLocation + themeIcon["icon"].toString());

                QImage alpha(image.width(), image.height(), QImage::Format_Alpha8);
                alpha.fill(Qt::transparent);

                QImage transferedImage(image.width(), image.height(), image.format());
                transferedImage.fill(QColor::fromString(themeVariables["icon-color"]));

                QImage finalImage(image.width(), image.height(), image.format());
                finalImage.fill(Qt::transparent);

                QPainter painter;

                painter.begin(&alpha);
                painter.drawImage(image.rect(),image);
                painter.end();

                alpha.invertPixels(QImage::InvertRgba);

                painter.begin(&finalImage);
                painter.setRenderHint(QPainter::Antialiasing);
                painter.drawImage(image.rect(), transferedImage);
                painter.setCompositionMode(QPainter::CompositionMode_Xor);
                painter.drawImage(image.rect(), alpha);
                painter.end();

                loadedIcon = QIcon(QPixmap::fromImage(finalImage));

                if(themeVariables.contains("icon-disabled-color"))
                {
                    transferedImage.fill(QColor::fromString(themeVariables["icon-disabled-color"]));

                    QImage disabledImage(image.width(), image.height(), image.format());
                    finalImage.fill(Qt::transparent);

                    painter.begin(&disabledImage);
                    painter.setRenderHint(QPainter::Antialiasing);
                    painter.drawImage(image.rect(), transferedImage);
                    painter.setCompositionMode(QPainter::CompositionMode_Xor);
                    painter.drawImage(image.rect(), alpha);
                    painter.end();

                    loadedIcon.addPixmap(QPixmap::fromImage(disabledImage), QIcon::Disabled);
                    loadedIcon.addPixmap(QPixmap::fromImage(disabledImage), QIcon::Disabled, QIcon::On);
                }

                if(themeVariables.contains("icon-selected-color"))
                {
                    transferedImage.fill(QColor::fromString(themeVariables["icon-selected-color"]));

                    QImage disabledImage(image.width(), image.height(), image.format());
                    finalImage.fill(Qt::transparent);

                    painter.begin(&disabledImage);
                    painter.setRenderHint(QPainter::Antialiasing);
                    painter.drawImage(image.rect(), transferedImage);
                    painter.setCompositionMode(QPainter::CompositionMode_Xor);
                    painter.drawImage(image.rect(), alpha);
                    painter.end();

                    loadedIcon.addPixmap(QPixmap::fromImage(disabledImage), QIcon::Selected);
                    loadedIcon.addPixmap(QPixmap::fromImage(disabledImage), QIcon::Selected, QIcon::On);
                }

                if(themeVariables.contains("icon-active-color"))
                {
                    transferedImage.fill(QColor::fromString(themeVariables["icon-active-color"]));

                    QImage disabledImage(image.width(), image.height(), image.format());
                    finalImage.fill(Qt::transparent);

                    painter.begin(&disabledImage);
                    painter.setRenderHint(QPainter::Antialiasing);
                    painter.drawImage(image.rect(), transferedImage);
                    painter.setCompositionMode(QPainter::CompositionMode_Xor);
                    painter.drawImage(image.rect(), alpha);
                    painter.end();

                    loadedIcon.addPixmap(QPixmap::fromImage(disabledImage), QIcon::Active);
                    loadedIcon.addPixmap(QPixmap::fromImage(disabledImage), QIcon::Active, QIcon::On);
                }
            }
            else
                loadedIcon = QIcon(iconSetLocation + themeIcon["icon"].toString());

            m_iconMap[themeIcon["name"].toString()] = loadedIcon;
            m_iconLocationMap[themeIcon["name"].toString()] = iconSetLocation + themeIcon["icon"].toString();
        }
    }
}

void Settings::load()
{
    //setup settings object
    QSettings settings;

    if(settings.value("first-run", true).toBool())
    {
        qDebug() << "Initiating first run";
        inflateSettingsDirectory();
        scanForKlipperInstances();
        save();
    }

    m_currentIconSetName = settings.value("ui/icon-set").toString();

    int id = QFontDatabase::addApplicationFont(":/fonts/digital-7(mono).ttf");
    m_digitalFontFamily = QFontDatabase::applicationFontFamilies(id).at(0);

    loadThemes();
    loadIconSets();
    loadIcons();

    //load animation settings
    m_animationInStyle = (Settings::AnimationStyle)settings.value("ui/animation_in_style", Settings::SlideTop).toInt();
    m_animationInStyle = (Settings::AnimationStyle)settings.value("ui/animation_out_style", Settings::SlideBottom).toInt();
    m_animationDuration = settings.value("ui/animation_duration", 500).toInt();
    m_isAnimationEnabled = settings.value("ui/animations_enabled", true).toBool();
    m_animationEffectInStyle = (Settings::EffectsStyle)settings.value("ui/animation_in_effect", Settings::Opacity).toInt();
    m_animationEffectOutStyle = (Settings::EffectsStyle)settings.value("ui/animation_out_effect", Settings::Opacity).toInt();
    m_animationDuration = settings.value("ui/animation_duration", 500).toInt();
    m_isAnimationEffectsEnabled = settings.value("ui/animation_effects_enabled", true).toBool();

    //load the instance ids
    QStringList ids = settings.value("instance_id_list",QStringList()).toStringList();

    for(QString &id : ids)
    {
        QKlipperInstance *instance = new QKlipperInstance();

        //begin the group to load settings under this prefix
        settings.beginGroup(id);

        QString name = settings.value("name").toString();
        QString address = settings.value("address").toString();
        QString location = settings.value("location").toString();
        QString api = settings.value("api_key").toString();
        QString color = settings.value("color").toString();
        int port = settings.value("port").toInt();

        //set the instance settings
        instance->setId(id);
        instance->setName(settings.value("name").toString());
        instance->setAddress(settings.value("address").toString());
        instance->setPort(settings.value("port").toInt());
        instance->setInstanceLocation(settings.value("location").toString());
        instance->setApiKey(settings.value("api_key").toString());
        instance->setProfileColor(settings.value("color").toString());
        instance->setAutoConnect(settings.value("auto_connect").toBool());

        //end group to move to power settings
        settings.endGroup();

        settings.beginGroup(id + "/power");
        QStringList keys = settings.childKeys();

        for(const QString &key : keys)
            instance->printer()->addPowerProfileData(key, settings.value(key).toDouble());

        settings.endGroup();

        QString thumbnailLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + QDir::separator() + "thumbnails";
        QString thumbnailFile(thumbnailLocation + QDir::separator() + instance->id() + ".png");

        if(QFile::exists(thumbnailFile))
        {
            QImage thumbnail(thumbnailFile);
            instance->setThumbnail(thumbnail);
        }

        QObject::connect(instance, SIGNAL(connected(QKlipperInstance*)), Settings::instance(), SLOT(onInstanceOnline(QKlipperInstance*)));

        QKlipperInstancePool::addInstance(instance);
    }
}

void Settings::save()
{
    QSettings settings;

    settings.setValue("first-run", false);

    //scan for removed printers
    QStringList savedInstances = settings.value("instance_id_list").toStringList();
    QStringList runningInstances = QKlipperInstancePool::klipperInstanceIds();

    for(const QString &instance : savedInstances)
    {
        if(!runningInstances.contains(instance))
            settings.remove(instance);
    }

    //save current instances
    settings.setValue("instance_id_list", QKlipperInstancePool::klipperInstanceIds()); //save the id list to know what settings group to load
    settings.setValue("ui/animation_in_style", m_animationInStyle);
    settings.setValue("ui/animation_out_style", m_animationOutStyle);
    settings.setValue("ui/animation_duration", m_animationDuration);
    settings.setValue("ui/animations_enabled", m_isAnimationEnabled);
    settings.setValue("ui/animation_effects_enabled", m_isAnimationEffectsEnabled);
    settings.setValue("ui/animation_in_effect", m_animationEffectInStyle);
    settings.setValue("ui/animation_out_effect", m_animationEffectOutStyle);
    settings.setValue("ui/icon-set", m_currentIconSetName);

    //iterate over the instances to save settings under its id
    QKlipperInstanceList instances = QKlipperInstancePool::klipperInstances();

    for(QKlipperInstance *instance : instances)
    {
        if(!instance->hasUpdate())
            continue;

        if(!instance->thumbnail().isNull())
        {
            QString thumbnailLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + QDir::separator() + "thumbnails";
            QString thumbnailFile(thumbnailLocation + QDir::separator() + instance->id() + ".png");

            instance->thumbnail().save(thumbnailFile);
        }

        settings.beginGroup(instance->id()); //start the group so all following settings get stored under this prefix

        settings.setValue("name", instance->name());
        settings.setValue("address", instance->address());
        settings.setValue("port", instance->port());
        settings.setValue("location", instance->instanceLocation());
        settings.setValue("api_key", instance->apiKey());
        settings.setValue("color", instance->profileColor());
        settings.setValue("auto_connect", instance->autoConnect());

        QStringList keys = instance->printer()->powerProfile().keys();

        for(const QString &key : keys)
            settings.setValue(QString("power/") + key, instance->printer()->powerProfile().value(key));

        settings.endGroup();
    }

    // QString requestedIconLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + QDir::separator() + "icons";
    // QFile requestedIconFile(requestedIconLocation + QDir::separator() + "icons.json");

    // if(requestedIconFile.open(QFile::WriteOnly))
    // {
    //     QJsonDocument document;
    //     QJsonArray array;

    //     for(QString requestedIcon : m_requestedIcons)
    //     {
    //         QJsonObject object;
    //         object["name"] = requestedIcon;
    //         object["icon"] = m_iconNames[requestedIcon];

    //         array.append(object);
    //     }

    //     document.setArray(array);

    //     requestedIconFile.write(document.toJson());
    //     requestedIconFile.close();
    // }

    // QDir requestedIconDir(requestedIconLocation + QDir::separator() + "requested");

    // if(!requestedIconDir.exists())
    //     requestedIconDir.mkpath(".");

    // for(QString requestedIcon : m_requestedIcons)
    // {
    //     QString name = m_iconNames[requestedIcon];
    //     QPixmap pixmap = m_iconMap[requestedIcon].pixmap(64,64);

    //     pixmap.save(requestedIconDir.absolutePath() + QDir::separator() + name);
    // }
}

void Settings::reset()
{
    QSettings settings;
    settings.clear();
}

void Settings::removeInstance(QKlipperInstance *instance)
{
    QSettings settings;
    settings.remove(instance->id());
}

QVariant Settings::get(QString key, QVariant value)
{
    QSettings settings;

    if(value != QVariant() && !settings.contains(key))
    {
        settings.setValue(key, value);
        return value;
    }
    else if(!settings.contains(key))
        return QVariant();

    return settings.value(key);
}

void Settings::set(QString key, QVariant value)
{
    QSettings settings;
    settings.setValue(key, value);
}

QString Settings::getTheme(QString key)
{
    QFile themeFile(themeMap[key]);

    //Missing or corrupt files are just skipped for now
    if(!themeFile.open(QFile::ReadOnly))
        return QString();

    QString theme = themeFile.readAll();
    themeFile.close();

    QVariableStyleSheet sheet(theme);
    theme = sheet.stylesheet();

    m_theme = sheet;

    QMap<QString,QString> themeVariables = sheet.variables();

    foreach(QString key, themeVariables.keys())
        set(QString("theme/") + key, themeVariables[key]);

    //For Debug
#ifdef THEME_DEBUG
    QFile alteredFile(themeMap[key] + QString("_debug"));
    if(alteredFile.open(QFile::WriteOnly))
    {
        alteredFile.write(theme.toUtf8());
        alteredFile.close();
    }
#endif

    return theme;
}

QVariableStyleSheet Settings::getThemeSheet(QString key)
{
    QFile themeFile(themeMap[key]);

    //Missing or corrupt files are just skipped for now
    if(!themeFile.open(QFile::ReadOnly))
        return QString();

    QString theme = themeFile.readAll();
    themeFile.close();

    QVariableStyleSheet sheet(theme);

    return sheet;
}

QIcon Settings::getThemeIcon(QString key, QColor color)
{
    if(!m_requestedIcons.contains(key))
        m_requestedIcons += key;

    if(color.isValid())
    {
        QIcon loadedIcon = m_iconMap[key];
        QImage image(loadedIcon.pixmap(64,64).toImage());

        QImage alpha(image.width(), image.height(), QImage::Format_Alpha8);
        alpha.fill(Qt::transparent);

        QImage transferedImage(image.width(), image.height(), image.format());
        transferedImage.fill(color);

        QImage finalImage(image.width(), image.height(), image.format());
        finalImage.fill(Qt::transparent);

        QPainter painter;

        painter.begin(&alpha);
        painter.drawImage(image.rect(),image);
        painter.end();

        alpha.invertPixels(QImage::InvertRgba);

        painter.begin(&finalImage);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawImage(image.rect(), transferedImage);
        painter.setCompositionMode(QPainter::CompositionMode_Xor);
        painter.drawImage(image.rect(), alpha);
        painter.end();

        loadedIcon = QIcon(QPixmap::fromImage(finalImage));

        return loadedIcon;
    }
    else
        return m_iconMap[key];
}

QString Settings::getThemeIconLocation(QString key)
{
    QString location;

    if(m_iconLocationMap.contains(key))
        location = m_iconLocationMap[key];

    return location;
}

QStringList Settings::getThemeList()
{
    QStringList themes = themeMap.keys();
    return themes;
}

QStringList Settings::getIconSetList()
{
    return m_iconSetMap.keys();
}

void Settings::setTheme(QString key)
{
    set("theme_name", key);
    m_currentTheme = getTheme(key);
    m_currentThemeName = key;
    emit m_instance->currentThemeChanged();
}

QStringList Settings::themeList()
{
    return themeMap.keys();
}

bool Settings::saveTheme(const QString &name, const QVariableStyleSheet &sheet)
{
    QString themeLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) +
                            QDir::separator() + "themes" + QDir::separator();

    QFile themeFile(themeLocation + name + ".css");

    if(!themeFile.open(QFile::WriteOnly))
    {
        qDebug() << "Could not open theme file " << themeFile.fileName();
        return false;
    }

    themeFile.write(sheet.rawStyleSheet().toUtf8());

    themeFile.close();

    //m_instance->setTheme(name);

    loadThemes();

    return true;
}

bool Settings::deleteTheme(const QString &name)
{
    QString themeLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) +
                            QDir::separator() + "themes" + QDir::separator();

    QFile themeFile(themeLocation + name + ".css");

    if(!themeFile.remove())
    {
        qDebug() << "Could not delete theme" << name << themeLocation + name + ".css";
        return false;
    }

    themeMap.remove(name);
    return true;
}

bool Settings::renameTheme(const QString &name, const QString &newName)
{
    QString themeLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) +
                            QDir::separator() + "themes" + QDir::separator();

    QFile themeFile(themeLocation + name + ".css");

    if(!themeFile.rename(newName))
    {
        qDebug() << "Could not rename theme" << name << themeLocation + name + ".css";
        return false;
    }

    QString data = themeMap[name];
    themeMap.remove(name);
    themeMap.insert(newName, data);
    return true;
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
    QSettings settings;
    return settings.contains(key);
}

QVariableStyleSheet Settings::theme()
{
    return m_theme;
}

void Settings::onInstanceOnline(QKlipperInstance *instance)
{
}

Settings::Settings()
{
}

QString Settings::currentThemeName()
{
    return m_currentThemeName;
}

QString Settings::currentIconSetName()
{
    return m_currentIconSetName;
}

bool Settings::inflateSettingsDirectory()
{
    QString themeLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) +
                            QDir::separator() + "themes" + QDir::separator();
    QDir themeDir(themeLocation);

    if(!themeDir.exists())
        themeDir.mkpath(".");

    QString iconLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) +
                            QDir::separator() + "icons" + QDir::separator() + "default" + QDir::separator();
    QDir iconDir(iconLocation);

    if(!iconDir.exists())
        iconDir.mkpath(".");

    QString thumbnailLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) +
                            QDir::separator() + "thumbnails" + QDir::separator();
    QDir thumbnailDir(thumbnailLocation);

    if(!thumbnailDir.exists())
        thumbnailDir.mkpath(".");

    QFile zipFile(":/data/default.zip");
    zipFile.open(QFile::ReadWrite);

    QuaZip zip(&zipFile);

    if (!zip.open(QuaZip::mdUnzip))
        qDebug() << "error";

    QuaZipFile file(&zip);
    for (bool f = zip.goToFirstFile(); f; f = zip.goToNextFile()) {
        QuaZipFileInfo fileInfo;
        file.getFileInfo(&fileInfo);

        //skip folder entries
        if(fileInfo.name == "default/")
            continue;
        else if(fileInfo.name == "default/icons/")
            continue;
        else if(fileInfo.name == "default/themes/")
            continue;
        else if(fileInfo.name == "default/thumbnails/")
            continue;

        QString fileName = fileInfo.name;

        if(fileName.startsWith("default/"))
            fileName.remove(0, 8);

        fileName = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) +
            QDir::separator() + fileName;

        QFile outFile(fileName);

        if(!outFile.open(QFile::ReadWrite))
        {
            qDebug() << "Error opening file on disk" << fileInfo.name;
            continue;
        }

        file.open(QIODevice::ReadOnly);

        outFile.write(file.readAll());
        outFile.close();
        file.close();
    }

    zip.close();

    return true;
}

bool Settings::scanForKlipperInstances()
{
    QString homeLocation = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

    QDir homeDir(homeLocation);

    QStringList scannableDirectories;

    if(!homeDir.cdUp())
    {
        qDebug() << "Could not resolve base home directory";
        scannableDirectories += homeLocation;
    }
    else
        scannableDirectories = homeDir.entryList(QStringList(), QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);

    //scan each home directory for klipper instances
    for(QString user : scannableDirectories)
    {
        QMoonrakerDirectoryValidator *moonrakerValidator = new QMoonrakerDirectoryValidator();

        QDir userDirectory(homeDir.absolutePath());
        userDirectory.cd(user);

        QStringList klipperDirectoryList = userDirectory.entryList(QStringList() << "printer_data*", QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);

        for(QString klipperDirectoryEntry : klipperDirectoryList)
        {
            QDir klipperDirectory(userDirectory.absolutePath());
            klipperDirectory.cd(klipperDirectoryEntry);

            QString klipperDirectoryLocation = klipperDirectory.absolutePath();
            int pos = 0;

            if(moonrakerValidator->validate(klipperDirectoryLocation, pos))
            {
                klipperDirectory.cd("config");
                qDebug() << klipperDirectory.absoluteFilePath("moonraker.conf");

                int port = 7125;
                bool portValid = false;

                QFile moonrakerSettings(klipperDirectory.absoluteFilePath("moonraker.conf"));
                QMap<QString, QVariant> moonrakerSettingsMap;

                if(moonrakerSettings.open(QFile::ReadWrite | QFile::Text))
                {
                    QTextStream dataStream(&moonrakerSettings);

                    // canReadLine() returning false. verified files have \n
                    while(!dataStream.atEnd())
                    {
                        QString key, value;
                        QString data = dataStream.readLine();

                        key = data.left(data.indexOf(": "));
                        value = data.right(data.indexOf(": "));

                        moonrakerSettingsMap[key] = value;
                    }
                }

                if(moonrakerSettingsMap.contains("port"))
                {
                    portValid = true;
                    port = moonrakerSettingsMap["port"].toInt();
                }

                if(portValid && port > 0)
                {
                    QColor color = QColor::fromRgb(QRandomGenerator::global()->generate());

                    QKlipperInstance *instance = new QKlipperInstance();
                    instance->setName(klipperDirectoryEntry);
                    instance->setAddress("http://localhost");
                    instance->setPort(port);
                    instance->setInstanceLocation(userDirectory.absolutePath() + QDir::separator() + klipperDirectoryEntry);
                    instance->setProfileColor(color.name());

                    QMessageBox msgBox;
                    msgBox.setText("Klipper Instance Found");
                    msgBox.setInformativeText("Found instance '" + instance->instanceLocation() + "'. Would you like to automatically add it?");
                    msgBox.setStandardButtons(QMessageBox::Apply | QMessageBox::Cancel);
                    msgBox.setDefaultButton(QMessageBox::Apply);
                    msgBox.setFixedSize(400,250);

                    int ret = msgBox.exec();

                    switch(ret)
                    {
                        case QMessageBox::Apply:
                            QKlipperInstancePool::addInstance(instance);
                            break;
                        default:
                            instance->deleteLater();
                            break;
                    }
                }

            }
        }
    }

    return true;
}

Settings::EffectsStyle Settings::animationEffectOutStyle()
{
    return m_animationEffectOutStyle;
}

void Settings::setAnimationEffectOutStyle(EffectsStyle animationEffectOutStyle)
{
    m_animationEffectOutStyle = animationEffectOutStyle;
}

void Settings::setIconSet(const QString &name)
{
    if(!m_iconSetMap.contains(name))
    {
        qWarning("Icon set unknown");
        return;
    }

    if(name == m_currentIconSetName)
    {
        qWarning("Requested icon set is same as current");
        return;
    }

    m_currentIconSetName = name;
    loadIcons();

    set("theme/icon-set", name);

    emit m_instance->currentThemeChanged();
}

Settings::EffectsStyle Settings::animationEffectInStyle()
{
    return m_animationEffectInStyle;
}

void Settings::setAnimationEffectInStyle(EffectsStyle animationEffectInStyle)
{
    m_animationEffectInStyle = animationEffectInStyle;
}

void Settings::setAnimationInStyle(AnimationStyle animationInStyle)
{
    m_animationInStyle = animationInStyle;
}

void Settings::setAnimationOutStyle(AnimationStyle animationOutStyle)
{
    m_animationOutStyle = animationOutStyle;
}

void Settings::setIsAnimationEnabled(bool isAnimationEnabled)
{
    m_isAnimationEnabled = isAnimationEnabled;
}

void Settings::setAnimationDuration(qint16 animationDuration)
{
    m_animationDuration = animationDuration;
}

bool Settings::isAnimationEffectsEnabled()
{
    return m_isAnimationEffectsEnabled;
}

void Settings::setIsAnimationEffectsEnabled(bool isAnimationEffectsEnabled)
{
    m_isAnimationEffectsEnabled = isAnimationEffectsEnabled;
}

qint16 Settings::animationDuration()
{
    return m_animationDuration;
}

Settings::AnimationStyle Settings::animationOutStyle()
{
    return m_animationOutStyle;
}

bool Settings::isAnimationEnabled()
{
    return m_isAnimationEnabled;
}

Settings::AnimationStyle Settings::animationInStyle()
{
    return m_animationInStyle;
}
