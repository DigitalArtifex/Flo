#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("DigitalArtifex");
    QCoreApplication::setOrganizationDomain("digitalartifex.github.com");
    QCoreApplication::setApplicationName("Flo");

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
    w.init();
    w.show();

    int retcode = a.exec();

    if (retcode == APPLICATION_RESTART_CODE)
    {
        QProcess* proc = new QProcess();
        proc->start(QCoreApplication::applicationFilePath(), QCoreApplication::arguments());
    }

    return retcode;
}
