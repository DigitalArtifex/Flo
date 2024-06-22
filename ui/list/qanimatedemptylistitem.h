#ifndef QANIMATEDEMPTYLISTITEM_H
#define QANIMATEDEMPTYLISTITEM_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QSpacerItem>
#include <QObject>

#include "../qanimatedwidget.h"

class QAnimatedEmptyListItem : public QAnimatedWidget
{
    Q_OBJECT
public:
    QAnimatedEmptyListItem(QWidget *parent = nullptr);
    ~QAnimatedEmptyListItem();

    void setupUi();

    virtual void setText(const QString &text);
    virtual void setIcon(const QPixmap &pixmap);
    virtual void setIcon(const QString &iconName);

private:

    QLabel *m_label = nullptr;
    QLabel *m_iconLabel = nullptr;

    QSpacerItem *m_topSpacer = nullptr;
    QSpacerItem *m_middleSpacer = nullptr;
    QSpacerItem *m_bottomSpacer = nullptr;
};

#endif // QANIMATEDEMPTYLISTITEM_H
