#ifndef FILEBROWSEROVERLAY_H
#define FILEBROWSEROVERLAY_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QSpacerItem>

#include "../../../../ui/qanimatedwidget.h"

class FileBrowserOverlay : public QAnimatedWidget
{
    Q_OBJECT
public:
    FileBrowserOverlay(QWidget *parent = nullptr);
    ~FileBrowserOverlay();

    void setupUi();

    virtual void setText(const QString &text);
    virtual void setIcon(const QPixmap &pixmap);
    virtual void setIcon(const QIcon &icon);

private:

    QLabel *_label = nullptr;
    QLabel *_iconLabel = nullptr;

    QSpacerItem *_topSpacer = nullptr;
    QSpacerItem *_bottomSpacer = nullptr;

    QGridLayout *_layout = nullptr;
};

#endif // FILEBROWSEROVERLAY_H
