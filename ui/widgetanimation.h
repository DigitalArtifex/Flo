#ifndef WIDGETANIMATION_H
#define WIDGETANIMATION_H

#include <QObject>
#include <QWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QGraphicsOpacityEffect>

class WidgetAnimation : public QObject
{
    Q_OBJECT
public:
    enum Property {
        MaxHeight = 1,
        MaxWidth = 2,
        MinHeight = 4,
        MinWidth = 8,
        Opacity = 16,
        Blur = 16,
        MinMaxHeight = (MaxHeight | MinHeight),
        MinMaxWidth = (MaxWidth | MinWidth)
    };

    explicit WidgetAnimation(QWidget *target, Property property, QObject *parent = nullptr);

    void show();
    void hide();

    void setProperty(Property property);
    void setHeightIn(qreal height);
    void setHeightOut(qreal height);
    void setWidthIn(qreal width);
    void setWidthOut(qreal width);

    bool hasPropertyFlag(Property property);

signals:
    void finished();

private slots:
    void on_animations_finished();

private:
    Property m_property = (Property)0;
    qreal m_heightIn = 0;
    qreal m_heightOut = 0;
    qreal m_widthIn = 0;
    qreal m_widthOut = 0;

    QWidget *m_target = nullptr;
    QParallelAnimationGroup *m_animationsIn = nullptr;
    QParallelAnimationGroup *m_animationsOut = nullptr;
    QPropertyAnimation *m_animationIn_maxHeight = nullptr;
    QPropertyAnimation *m_animationIn_minHeight = nullptr;
    QPropertyAnimation *m_animationIn_maxWidth = nullptr;
    QPropertyAnimation *m_animationIn_minWidth = nullptr;
    QPropertyAnimation *m_animationIn_opacity = nullptr;
    QPropertyAnimation *m_animationOut_maxHeight = nullptr;
    QPropertyAnimation *m_animationOut_minHeight = nullptr;
    QPropertyAnimation *m_animationOut_maxWidth = nullptr;
    QPropertyAnimation *m_animationOut_minWidth = nullptr;
    QPropertyAnimation *m_animationOut_opacity = nullptr;
    QGraphicsOpacityEffect *m_effect_opacity = nullptr;
};

#endif // WIDGETANIMATION_H
