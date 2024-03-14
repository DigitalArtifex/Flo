#include "klipperfile.h"

KlipperFile::KlipperFile(KlipperFile::FileType type) :
    type(type)
{

}

QMap<QString, QVariant> KlipperFile::metadata()
{
    return this->_metadata;
}

QVariant KlipperFile::operator[](QString key) {
    return this->_metadata[key];
}
