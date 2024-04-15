#ifndef FILEBROWSEROVERLAY_H
#define FILEBROWSEROVERLAY_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include "../../../../ui/qanimatedwidget.h"

class FileBrowserOverlay : public QAnimatedWidget
{
    Q_OBJECT
public:
    FileBrowserOverlay(QWidget *parent = nullptr);
    ~FileBrowserOverlay();

    void setupUi();

    virtual void setText(const QString &text);

private:

    QLabel *_label = nullptr;
    QGridLayout *_layout = nullptr;
};

#endif // FILEBROWSEROVERLAY_H
