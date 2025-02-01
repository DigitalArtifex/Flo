#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QVariant>
#include <QMap>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>

#include <QBuffer>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QRegularExpression>
#include <QBitmap>
#include <QRandomGenerator>
#include <QMessageBox>

#include <QSettings>
#include <QtSvg/QSvgRenderer>

#include <QIcon>

#include <QFontDatabase>
#include <QColorTransform>
#include <QuaZip-Qt5-1.4/quazip/quazip.h>
#include <QuaZip-Qt5-1.4/quazip/quazipfile.h>

#include "QKlipper/qklipper.h"

#include "3rdparty/QVariableStyleSheet/qvariablestylesheet.h"
#include "validators/QMoonrakerDirectoryValidator/qmoonrakerdirectoryvalidator.h"

class Settings : public QObject
{
    Q_OBJECT

public:

    enum AnimationStyle
    {
        SlideTop,
        SlideBottom,
        SlideRight,
        SlideLeft
    };

    enum EffectsStyle
    {
        Blur,
        Opacity
    };

    static void load();
    static void save();
    static void reset();
    static void removeInstance(QKlipperInstance *instance);

    static QVariant get(QString key, QVariant value = QVariant());
    static void set(QString key, QVariant value);

    static QString getTheme(QString key);
    static QIcon getThemeIcon(QString key, QColor color = QColor());
    static QString getThemeIconLocation(QString key);
    static QStringList getThemeList();
    static QStringList getIconSetList();
    void setTheme(QString key);
    static QStringList themeList();
    static bool saveTheme(const QString &name, const QVariableStyleSheet &sheet);

    static QKlipperInstance *defaultPrinter();
    static void addPrinter(QKlipperInstance* printer);
    static void removePrinter(QKlipperInstance* printer);
    static void setDefaultPrinter(QKlipperInstance* printer);
    static void updatePrinter(QKlipperInstance* printer);

    static Settings *instance();

    static QString currentTheme();

    static QString digitalFontFamily();
    static bool contains(QString key);

    static QVariableStyleSheet theme();

    static AnimationStyle animationInStyle();
    static AnimationStyle animationOutStyle();
    static qint16 animationDuration();
    static bool isAnimationEnabled();

    static bool isAnimationEffectsEnabled();

    static EffectsStyle animationEffectInStyle();

    static EffectsStyle animationEffectOutStyle();

    static QString currentIconSetName();

    static QString currentThemeName();

signals:
    void currentThemeChanged();

public slots:
    void onInstanceOnline(QKlipperInstance *instance);

    static void setIsAnimationEffectsEnabled(bool isAnimationEffectsEnabled);

    static void setAnimationDuration(qint16 animationDuration);

    static void setIsAnimationEnabled(bool isAnimationEnabled);

    static void setAnimationOutStyle(AnimationStyle animationOutStyle);

    static void setAnimationInStyle(AnimationStyle animationInStyle);

    static void setAnimationEffectInStyle(EffectsStyle animationEffectInStyle);

    static void setAnimationEffectOutStyle(EffectsStyle animationEffectOutStyle);
    static void setIconSet(const QString &name);

private:
    explicit Settings();

    static QMap<QString,QVariant> themeSettings;
    static QMap<QString, QString> themeMap;
    static QMap<QString,QIcon> m_iconMap;
    static QMap<QString,QString> m_iconSetMap;
    static QMap<QString, QString> m_iconNames;
    static QMap<QString, QString> m_iconLocationMap;
    static QString m_currentThemeName;
    static QString m_currentIconSetName;

    static void loadThemes();
    static void loadIconSets();
    static void loadIcons();

    static bool inflateSettingsDirectory();
    static bool scanForKlipperInstances();

    static Settings *m_instance;
    static QVariableStyleSheet m_theme;
    static QList<QKlipperInstance*> m_instances;
    static QString m_currentTheme;

    static QString m_digitalFontFamily;
    static bool m_instanceCreated;

    static bool           m_isAnimationEnabled;
    static AnimationStyle m_animationInStyle;
    static AnimationStyle m_animationOutStyle;
    static qint16         m_animationDuration;

    static bool           m_isAnimationEffectsEnabled;
    static EffectsStyle   m_animationEffectInStyle;
    static EffectsStyle   m_animationEffectOutStyle;

    static QStringList m_requestedIcons;
};

#endif // SETTINGS_H
