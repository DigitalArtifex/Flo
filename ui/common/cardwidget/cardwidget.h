#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QToolButton>
#include <QVBoxLayout>
#include <QGridLayout>

#include "system/flo.h"
#include "ui/QIconButton/qiconbutton.h"

class CardWidget : public QFrame
{
    Q_OBJECT
public:
    enum class CardType : unsigned int
    {
        Widget = 0,
        SubWidget = 1
    };

    enum CardFlags : unsigned int
    {
        None = 0,
        NoFooter = 1,
        NoTitleBar = 2
    };

    explicit CardWidget(CardType type = CardType::Widget, QWidget *parent = nullptr);
    ~CardWidget();


    void addToolButton(QToolButton *toolbutton);
    void addFooterWidget(QWidget *widget);
    void addFooterItem(QLayoutItem *item);

    QString title() const;

    CardType cardType() const;

    QIcon icon() const;

    CardFlags cardFlags() const;

    QWidget *centralWidget() const;

public slots:
    void setIcon(const QIcon &icon);
    void setCentralWidget(QWidget *widget);

    void setCardFlags(CardFlags cardFlags);
    void setCardType(CardType newCardType);
    void setTitle(const QString &newTitle);

signals:

    void cardFlagsChanged();

protected:
    void setupFooter();
    void setupActionBar();

private:
    QVBoxLayout *m_layout = nullptr;
    QVBoxLayout *m_contentLayout = nullptr;
    QHBoxLayout *m_actionBarLayout = nullptr;
    QHBoxLayout *m_footerLayout = nullptr;
    QHBoxLayout *m_titleBarLayout = nullptr;

    QWidget *m_centralWidget = nullptr;
    QWidget *m_titleBarWidget = nullptr;
    QWidget *m_actionBarWidget = nullptr;
    QWidget *m_contentWidget = nullptr;
    QWidget *m_footerWidget = nullptr;

    QLabel *m_titleLabel = nullptr;
    QLabel *m_iconLabel = nullptr;

    QIcon m_icon;

    QString m_title;

    CardFlags m_cardFlags;
    CardType m_cardType;
    Q_PROPERTY(CardFlags cardFlags READ cardFlags WRITE setCardFlags NOTIFY cardFlagsChanged FINAL)
};

Q_DECLARE_ENUM_FLAGS(CardWidget::CardFlags)

#endif // CARDWIDGET_H
