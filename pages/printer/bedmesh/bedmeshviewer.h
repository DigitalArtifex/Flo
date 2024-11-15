#ifndef BEDMESHVIEWER_H
#define BEDMESHVIEWER_H

#include <QObject>
#include <QWidget>
#include <QtWebView/QtWebView>

class BedMeshViewer : public QWidget
{
        Q_OBJECT
    public:
        explicit BedMeshViewer(QWidget *parent = nullptr);

    signals:
};

#endif // BEDMESHVIEWER_H
