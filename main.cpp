#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("DigitalArtifex");
    QCoreApplication::setOrganizationDomain("digitalartifex.github.com");
    QCoreApplication::setApplicationName("Flo");

    QSettings settings;
    settings.beginGroup("ui");

    if(settings.value("virtual-keyboard").toBool())
        qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    if(settings.contains("media-backend"))
        qputenv("QT_MEDIA_BACKEND", settings.value("media-backend").toString().toStdString());

    QFont applicationFont = QApplication::font();

    if(settings.contains("font-string"))
    {
        if(applicationFont.fromString(settings.value("font-string").toString()))
            QApplication::setFont(applicationFont);
    }

    settings.endGroup();

    qDebug() << "Font: " << applicationFont.toString();

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "FLO_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    w.show();

    int retcode = a.exec();

    if (retcode == APPLICATION_RESTART_CODE)
    {
        QProcess* proc = new QProcess();
        proc->start(QCoreApplication::applicationFilePath(), QCoreApplication::arguments());
    }

    return retcode;
}
