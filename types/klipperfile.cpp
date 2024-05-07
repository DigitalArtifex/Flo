#include "klipperfile.h"

QString KlipperFile::fileLocation()
{
    if(path.isEmpty())
        return name;
    else
        return path + QString("/") + name;
}

KlipperFile::KlipperFile(KlipperFile::FileType type) :
    type(type)
{

}
