#ifndef QABSTRACTKLIPPERPARSER_H
#define QABSTRACTKLIPPERPARSER_H

#include <QObject>
#include <QFunctionPointer>
#include <QAbstractSocket>
#include <QQueue>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include "../klipperfile.h"

class Printer;
class QAbstractKlipperParser;

typedef void(QAbstractKlipperParser::*ParserFunction)(QJsonObject, Printer*);

class QAbstractKlipperParser : public QObject
{
    Q_OBJECT
public:
    explicit QAbstractKlipperParser(QObject *parent = nullptr);

    //File Management
    virtual void on_deleteFile(QJsonObject object, Printer *printer);
    virtual void on_moveFile(QJsonObject object, Printer *printer);
    virtual void on_copyFile(QJsonObject object, Printer *printer);

    virtual QString downloadFile(QJsonObject object, Printer *printer);
    virtual bool uploadFile(QJsonObject object, Printer *printer);

    virtual void on_getFileList(QJsonObject object, Printer *printer);
    virtual void on_createDirectory(QJsonObject object, Printer *printer);
    virtual void on_deleteDirectory(QJsonObject object, Printer *printer);

    //Print Management
    virtual void on_startPrint(QJsonObject object, Printer *printer);
    virtual void on_pausePrint(QJsonObject object, Printer *printer);
    virtual void on_resumePrint(QJsonObject object, Printer *printer);
    virtual void on_cancelPrint(QJsonObject object, Printer *printer);

    //Machine Management
    virtual void on_machineShutdown(QJsonObject object, Printer *printer);
    virtual void on_machineReboot(QJsonObject object, Printer *printer);

    //Service Management
    virtual void on_serviceRestart(QJsonObject object, Printer *printer);
    virtual void on_serviceStop(QJsonObject object, Printer *printer);
    virtual void on_serviceStart(QJsonObject object, Printer *printer);

    virtual void on_sendGcode(QJsonObject object, Printer *printer);

    //Printer Management
    virtual void on_printerInfo(QJsonObject object, Printer *printer);
    virtual void on_restartKlipper(QJsonObject object, Printer *printer);
    virtual void on_restartFirmware(QJsonObject object, Printer *printer);
    virtual void on_printerSubscribe(QJsonObject object, Printer *printer);

    //Server Management
    virtual void on_serverInfo(QJsonObject object, Printer *printer);
    virtual void on_serverConfig(QJsonObject object, Printer *printer);
    virtual void on_serverFileRoots(QJsonObject object, Printer *printer);

    //Client Management
    virtual void on_clientIdentifier(QJsonObject object, Printer *printer);

signals:
};

#endif // QABSTRACTKLIPPERPARSER_H
