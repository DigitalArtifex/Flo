#include "qabstractklipperparser.h"

QAbstractKlipperParser::QAbstractKlipperParser(QObject *parent)
    : QObject{parent}
{

}

void QAbstractKlipperParser::on_deleteFile(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_moveFile(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_copyFile(QJsonObject object, Printer *printer)
{

}

QString QAbstractKlipperParser::downloadFile(QJsonObject object, Printer *printer)
{

}

bool QAbstractKlipperParser::uploadFile(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_getFileList(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_createDirectory(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_deleteDirectory(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_startPrint(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_pausePrint(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_resumePrint(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_cancelPrint(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_machineShutdown(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_machineReboot(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_serviceRestart(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_serviceStop(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_serviceStart(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_sendGcode(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_printerInfo(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_restartKlipper(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_restartFirmware(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_printerSubscribe(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_serverInfo(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_serverConfig(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_serverFileRoots(QJsonObject object, Printer *printer)
{

}

void QAbstractKlipperParser::on_clientIdentifier(QJsonObject object, Printer *printer)
{

}
