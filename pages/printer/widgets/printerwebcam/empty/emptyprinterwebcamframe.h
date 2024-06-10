#ifndef EMPTYPRINTERWEBCAMFRAME_H
#define EMPTYPRINTERWEBCAMFRAME_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>

#include "../../../../../system/settings.h"

class EmptyPrinterWebcamFrame : public QFrame
{
    Q_OBJECT
public:
    EmptyPrinterWebcamFrame(QWidget *parent = nullptr);

    virtual void setStyleSheet(QString &styleSheet);

protected:
    void setupUi();
    void setIcons();

private:

    QLabel *_label = nullptr;
    QLabel *_iconLabel = nullptr;
    QGridLayout *_layout = nullptr;
    QSpacerItem *_topSpacer = nullptr;
    QSpacerItem *_bottomSpacer = nullptr;
};

#endif // EMPTYPRINTERWEBCAMFRAME_H
