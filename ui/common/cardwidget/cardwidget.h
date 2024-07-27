#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QToolButton>
#include <QVBoxLayout>
#include <QGridLayout>

#include "ui/QIconButton/qiconbutton.h"

class CardWidget : public QFrame
{
    Q_OBJECT
public:
    enum CardType
    {
        Widget = 0,
        SubWidget = 1
    };

    enum CardFlags
    {
        None = 0x0000,
        NoFooter = 0x0001
    };

    explicit CardWidget(CardType type = Widget, QWidget *parent = nullptr);
    ~CardWidget();

    void setCentralWidget(QWidget *widget);

    void addToolButton(QToolButton *toolbutton);
    void addFooterWidget(QWidget *widget);
    void addFooterItem(QLayoutItem *item);

    QString title() const;
    void setTitle(const QString &newTitle);

    CardType cardType() const;
    void setCardType(CardType newCardType);

signals:

protected:
    void setupFooter();
    void setupActionBar();

private:
    QVBoxLayout *m_layout = nullptr;
    QVBoxLayout *m_contentLayout = nullptr;
    QHBoxLayout *m_actionBarLayout = nullptr;
    QHBoxLayout *m_footerLayout = nullptr;
    QHBoxLayout *m_titleBarLayout = nullptr;

    QWidget *m_titleBarWidget = nullptr;
    QWidget *m_actionBarWidget = nullptr;
    QWidget *m_contentWidget = nullptr;
    QWidget *m_footerWidget = nullptr;

    QLabel *m_titleLabel = nullptr;

    QString m_title;

    CardFlags m_cardFlags;
    CardType m_cardType;
};

#endif // CARDWIDGET_H
