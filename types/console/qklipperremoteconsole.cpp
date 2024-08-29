#include "qklipperremoteconsole.h"

QKlipperRemoteConsole::QKlipperRemoteConsole(Printer *printer, QObject *parent)
    : QAbstractKlipperConsole{printer, parent}
{}

void QKlipperRemoteConsole::shutdown()
{

}

void QKlipperRemoteConsole::sendCommand(QString command, KlipperMessage::MessageOrigin origin, bool forced)
{

}

void QKlipperRemoteConsole::sendCommand(KlipperMessage *message, bool immediate)
{

}

void QKlipperRemoteConsole::connectToMoonraker()
{

}

void QKlipperRemoteConsole::disconnectKlipper()
{

}

QString QKlipperRemoteConsole::downloadFile(KlipperFile file)
{

}

bool QKlipperRemoteConsole::uploadFile(QString root, QString directory, QString name, QByteArray data)
{

}

void QKlipperRemoteConsole::responseReceivedEvent()
{

}
