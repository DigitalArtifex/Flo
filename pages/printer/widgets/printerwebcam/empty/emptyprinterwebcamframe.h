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
    void setupIcons();

private:

    QLabel *m_label = nullptr;
    QLabel *m_iconLabel = nullptr;
    QGridLayout *m_layout = nullptr;
    QSpacerItem *m_topSpacer = nullptr;
    QSpacerItem *m_bottomSpacer = nullptr;
};

#endif // EMPTYPRINTERWEBCAMFRAME_H
