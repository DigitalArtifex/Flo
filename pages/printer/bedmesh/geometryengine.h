// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine();
    virtual ~GeometryEngine();

    void drawCubeGeometry(QOpenGLShaderProgram *program);

    qint32 width() const;
    void setWidth(qint32 width);

    qint32 length() const;
    void setLength(qint32 length);

    qint32 thickness() const;
    void setThickness(qint32 thickness);

private:
    void initCubeGeometry();

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    qint32 _width = 235;
    qint32 _length = 235;
    qint32 _thickness = 1;
    qreal  _scaleFactor = 1000;
    qreal  _scale = 5;
};

#endif // GEOMETRYENGINE_H
