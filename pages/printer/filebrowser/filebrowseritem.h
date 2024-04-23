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
    FileBrowserItem(KlipperFile file, QWidget *parent);
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
    KlipperFile _file = KlipperFile();

    bool _directory = false;

    //UI Elements
    QLabel *_titleLabel = nullptr;
    QLabel *_sizeLabel = nullptr;
    QLabel *_modifiedLabel = nullptr;
    QLabel *_iconLabel = nullptr;

    QWidget *_iconContainer = nullptr;

    QGridLayout *_layout = nullptr;
    QSpacerItem *_spacer = nullptr;
};

#endif // FILEBROWSERITEM_H
