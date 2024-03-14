#ifndef FILEBROWSERITEM_H
#define FILEBROWSERITEM_H

#include <QListWidgetItem>
#include <QDateTime>
#include <QUuid>
#include <QMouseEvent>
#include <QTimer>

#include "../types/klipperfile.h"

namespace Ui {
class FileBrowserItem;
}

class FileBrowserItem : public QFrame
{
    Q_OBJECT

    QString _name;
    qint64 _fileSize;
    QDateTime _modified;
    KlipperFile _file;

    QString _id;
    bool directory = false;
    bool pressed = false;
    bool longPress = false;
    bool rightClick = false;
    QTimer *clickTimer = NULL;

public:
    explicit FileBrowserItem(QWidget *parent = nullptr);
    ~FileBrowserItem();

    void setName(QString name);
    void setFileSize(qint64 size);
    void setDateModified(QDateTime time);
    bool isDirectory();

    void setIcons();
    void showButtons(bool show = true);
    void setDirectoryFlag(bool directory);

    QString id();
    QString name();
    qint64 fileSize();
    QDateTime dateModified();

    KlipperFile file();
    void setFile(KlipperFile file);

signals:
    void printRequested(FileBrowserItem *item);
    void deleteRequested(FileBrowserItem *item);
    void createRequested(FileBrowserItem *item);
    void clicked(FileBrowserItem *item);
    void longPressed(FileBrowserItem *item);

private slots:
    virtual void clickTimeout();

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void repaint();

private:
    Ui::FileBrowserItem *ui;
};

#endif // FILEBROWSERITEM_H
