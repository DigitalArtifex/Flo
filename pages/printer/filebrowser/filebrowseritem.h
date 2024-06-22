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
#include "../../../types/klipperfile.h"

class FileBrowserItem : public QAnimatedListItem
{
    Q_OBJECT
public:

    enum DisplayMode
    {
        Page,
        Widget
    };

    FileBrowserItem(KlipperFile file, QWidget *parent, DisplayMode mode = Page);
    ~FileBrowserItem();

    KlipperFile file() const;
    void setFile(const KlipperFile &file);

    bool isDirectory() const;

signals:
    void printRequested(FileBrowserItem *item);
    void deleteRequested(FileBrowserItem *item);
    void createRequested(FileBrowserItem *item);
    void saveRequested(FileBrowserItem *item);

private slots:
    virtual void setupUi();

private:
    KlipperFile m_file = KlipperFile();

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
};

#endif // FILEBROWSERITEM_H
