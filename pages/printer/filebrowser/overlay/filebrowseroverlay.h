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

    QLabel *m_label = nullptr;
    QLabel *m_iconLabel = nullptr;

    QSpacerItem *m_topSpacer = nullptr;
    QSpacerItem *m_bottomSpacer = nullptr;

    QGridLayout *m_layout = nullptr;
};

#endif // FILEBROWSEROVERLAY_H
