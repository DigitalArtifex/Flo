#ifndef KLIPPERFILE_H
#define KLIPPERFILE_H

#include <QString>
#include <QMap>
#include <QVariant>

class KlipperFile
{
    Q_GADGET
public:
    enum FileType {
        GCode,
        GCodeMacro,
        Config,
        Directory
    };

    //File metadata
    struct Metadata
    {
        struct Thumbnail
        {
            qint32 width = 0;
            qint32 height = 0;
            qint64 size = 0;

            QString relativePath;
        };

        qreal printStartTime = 0;
        qreal modified = 0;
        qreal layerHeight = 0;
        qreal firstLayerHeight = 0;
        qreal firstLayerBedTemp = 0;
        qreal firstLayerExtruderTemp = 0;
        qreal objectHeight = 0;
        qreal filamentTotal = 0;

        qint32 jobId = 0;
        qint64 estimatedTime = 0;
        qint64 gcodeStartByte = 0;
        qint64 gcodeEndByte = 0;
        qint64 size = 0;

        QString filename;
        QString slicer;
        QString slicerVersion;

        QList<Thumbnail> thumbnails;
    };

    QString fileLocation();

    KlipperFile(FileType type = GCode);

    Metadata metadata;

    double dateModified = 0;
    double fileSize = 0;
    QString root;
    QString path;
    QString name;
    FileType type;
};
#endif // KLIPPERFILE_H
