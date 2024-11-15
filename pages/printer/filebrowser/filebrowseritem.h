#ifndef FILEBROWSERITEM_H
#define FILEBROWSERITEM_H

#include <QObject>
#include <QLabel>
#include <QWidget>
#include <QToolButton>
#include <QGridLayout>
#include <QSpacerItem>
#include <QDateTime>

#include "../../../ui/list/qanimatedlistitem.h"
#include <QKlipper/qklipper.h>

class FileBrowserItem : public QAnimatedListItem
{
    Q_OBJECT
public:

    enum DisplayMode
    {
        Page,
        Widget
    };

    FileBrowserItem(QKlipperFile *file, QWidget *parent, DisplayMode mode = Page);
    ~FileBrowserItem();

    QKlipperFile *file() const;
    void setFile(QKlipperFile *file);

    bool isDirectory() const;

signals:
    void printRequested(FileBrowserItem *item);
    void deleteRequested(FileBrowserItem *item);
    void editRequested(FileBrowserItem *item);

private slots:
    virtual void setupUi();

    void printActionTriggered(bool checked);
    void editActionTriggered(bool checked);
    void deleteActionTriggered(bool checked);

private:
    QKlipperFile *m_file = nullptr;

    bool m_directory = false;

    //UI Elements
    QLabel *m_titleLabel = nullptr;
    QLabel *m_sizeLabel = nullptr;
    QLabel *m_modifiedLabel = nullptr;
    QLabel *m_iconLabel = nullptr;

    QWidget *m_iconContainer = nullptr;

    QGridLayout *m_layout = nullptr;
    QSpacerItem *m_spacer = nullptr;

    DisplayMode m_displayMode = Page;

    //Context menu
    QAction *m_printAction = nullptr;
    QAction *m_editAction = nullptr;
    QAction *m_deleteAction = nullptr;
};

#endif // FILEBROWSERITEM_H
