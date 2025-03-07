#ifndef QANIMATEDTOOLBOX_H
#define QANIMATEDTOOLBOX_H

#include <QObject>
#include <QToolBox>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include "qanimatedtoolboxbutton.h"
#include "common/QAnimatedWidget/qanimatedwidget.h"

class QAnimatedToolBox : public QFrame
{
    Q_OBJECT
public:
    QAnimatedToolBox(QWidget *parent = nullptr);

    int spacing() const;
    int indexOf(QWidget *widget, qsizetype from = 0);
    QWidget *widget(int index);

    void addItem(QWidget *widget, QIcon icon, QString title);
    void addItem(QWidget *widget, QString title);
    void addItem(QWidget *widget);

    void insertItem(int index, QWidget *widget, QIcon icon, QString title);
    void insertItem(int index, QWidget *widget, QString title);

    void removeItem(int index);
    void removeItem(QWidget *widget);

    void setItemIcon(int index, const QIcon &icon);
    void setItemText(int index, const QString &text);

    int currentIndex() const;
    int toolBoxButtonHeight() const;
    int animationDuration() const;

public slots:
    void setSpacing(int spacing);
    void setCurrentIndex(int currentIndex);
    void setCurrentWidget(QWidget *widget);
    void setToolBoxButtonHeight(int toolBoxButtonHeight);

    void setAnimationDuration(int animationDuration);

protected slots:
    void onButtonClicked(QAnimatedToolBoxButton *button);
    void onAnimationsFinished();

signals:
    void spacingChanged();
    void currentIndexChanged();

    void toolBoxButtonHeightChanged();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    void append(QAnimatedToolBoxButton *button, QWidget *widget);
    QVBoxLayout *m_layout = nullptr;
    QList<QAnimatedToolBoxButton*> m_buttons;
    QList<QWidget*> m_widgets;
    QList<QAnimatedWidget*> m_animatedWidgets;

    int m_toolBoxButtonHeight = 35;
    int m_spacing = 6;
    int m_currentIndex = 0;
    int m_nextIndex = 0;
    int m_animationDuration = 300;
    bool m_animating = false;

    QParallelAnimationGroup *m_animations = nullptr;

    Q_PROPERTY(int spacing READ spacing WRITE setSpacing NOTIFY spacingChanged FINAL)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged FINAL)
    Q_PROPERTY(int toolBoxButtonHeight READ toolBoxButtonHeight WRITE setToolBoxButtonHeight NOTIFY toolBoxButtonHeightChanged FINAL)
};

Q_DECLARE_METATYPE(QAnimatedToolBox)
#endif // QANIMATEDTOOLBOX_H
