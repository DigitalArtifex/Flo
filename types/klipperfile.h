#ifndef KLIPPERFILE_H
#define KLIPPERFILE_H

#include <QString>
#include <QMap>
#include <QVariant>

class KlipperFile
{
    Q_GADGET
    QMap<QString,QVariant> _metadata;
public:
    enum FileType {
        GCode,
        GCodeMacro,
        Config,
        Directory
    };

    KlipperFile(FileType type = GCode);

    QMap<QString,QVariant> metadata();
    double dateModified = 0;
    double fileSize = 0;
    QString fileLocation = QString("");
    FileType type;
    QVariant operator[](QString key);
};
#endif // KLIPPERFILE_H
