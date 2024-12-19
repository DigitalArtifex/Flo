/*
 * QKlipper - A Qt library for the Klipper/Moonraker API
 * Copyright (C) 2024 James Dudeck
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QKLIPPERMETADATA_H
#define QKLIPPERMETADATA_H

#include <QObject>
#include <QList>

#include "qklipperthumbnail.h"

//File metadata
class QKlipperMetadata
{
public:
    qreal printStartTime = 0;
    qreal modified = 0;
    qreal layerHeight = 0;
    qreal firstLayerHeight = 0;
    qreal firstLayerBedTemp = 0;
    qreal firstLayerExtruderTemp = 0;
    qreal objectHeight = 0;
    qreal filamentTotal = 0;
    qreal filamentTotalWeight = 0;
    qreal nozzleDiameter = 0;

    qint32 jobId = 0;
    qint64 estimatedTime = 0;
    qint64 gcodeStartByte = 0;
    qint64 gcodeEndByte = 0;
    qint64 size = 0;

    QString filename;
    QString filamentName;
    QString slicer;
    QString slicerVersion;
    QString uuid;

    QList<QKlipperThumbnail> thumbnails;

    QKlipperMetadata() = default;
    ~QKlipperMetadata() = default;

    QKlipperMetadata(const QKlipperMetadata &value)
    {
        printStartTime = value.printStartTime;
        modified = value.modified;
        layerHeight = value.layerHeight;
        firstLayerHeight = value.firstLayerHeight;
        firstLayerBedTemp = value.firstLayerBedTemp;
        firstLayerExtruderTemp = value.firstLayerExtruderTemp;
        objectHeight = value.objectHeight;
        filamentTotal = value.filamentTotal;
        filamentTotalWeight = value.filamentTotalWeight;
        nozzleDiameter = value.nozzleDiameter;
        jobId = value.jobId;
        estimatedTime = value.estimatedTime;
        gcodeEndByte = value.gcodeEndByte;
        gcodeStartByte = value.gcodeStartByte;
        size = value.size;
        filename = value.filename;
        filamentName = value.filamentName;
        slicer = value.slicer;
        slicerVersion = value.slicerVersion;
        uuid = value.uuid;
    }

    QKlipperMetadata &operator=(const QKlipperMetadata &value)
    {
        printStartTime = value.printStartTime;
        modified = value.modified;
        layerHeight = value.layerHeight;
        firstLayerHeight = value.firstLayerHeight;
        firstLayerBedTemp = value.firstLayerBedTemp;
        firstLayerExtruderTemp = value.firstLayerExtruderTemp;
        objectHeight = value.objectHeight;
        filamentTotal = value.filamentTotal;
        filamentTotalWeight = value.filamentTotalWeight;
        nozzleDiameter = value.nozzleDiameter;
        jobId = value.jobId;
        estimatedTime = value.estimatedTime;
        gcodeEndByte = value.gcodeEndByte;
        gcodeStartByte = value.gcodeStartByte;
        size = value.size;
        filename = value.filename;
        filamentName = value.filamentName;
        slicer = value.slicer;
        slicerVersion = value.slicerVersion;
        uuid = value.uuid;

        return *this;
    }

    bool operator==(const QKlipperMetadata &value)
    {
        if(thumbnails != value.thumbnails) return false;
        if(estimatedTime != value.estimatedTime) return false;
        if(gcodeEndByte != value.gcodeEndByte) return false;
        if(gcodeStartByte != value.gcodeStartByte) return false;
        if(jobId != value.jobId) return false;
        if(size != value.size) return false;
        if(filamentName != value.filamentName) return false;
        if(filamentTotal != value.filamentTotal) return false;
        if(filamentTotalWeight != value.filamentTotalWeight) return false;
        if(filename != value.filename) return false;
        if(firstLayerBedTemp != value.firstLayerBedTemp) return false;
        if(firstLayerExtruderTemp != value.firstLayerExtruderTemp) return false;
        if(firstLayerHeight != value.firstLayerHeight) return false;
        if(layerHeight != value.layerHeight) return false;
        if(objectHeight != value.objectHeight) return false;
        if(modified != value.modified) return false;
        if(nozzleDiameter != value.nozzleDiameter) return false;
        if(printStartTime != value.printStartTime) return false;
        if(slicer != value.slicer) return false;
        if(slicerVersion != value.slicerVersion) return false;
        if(uuid != value.uuid) return false;

        return true;
    }

    bool operator!=(const QKlipperMetadata &value)
    {
        return !(*this == value);
    }
};

Q_DECLARE_METATYPE(QKlipperMetadata)

#endif // QKLIPPERMETADATA_H
