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
    Property _property = (Property)0;
    qreal _heightIn = 0;
    qreal _heightOut = 0;
    qreal _widthIn = 0;
    qreal _widthOut = 0;

    QWidget *_target = nullptr;
    QParallelAnimationGroup *_animationsIn = nullptr;
    QParallelAnimationGroup *_animationsOut = nullptr;
    QPropertyAnimation *_animationIn_maxHeight = nullptr;
    QPropertyAnimation *_animationIn_minHeight = nullptr;
    QPropertyAnimation *_animationIn_maxWidth = nullptr;
    QPropertyAnimation *_animationIn_minWidth = nullptr;
    QPropertyAnimation *_animationIn_opacity = nullptr;
    QPropertyAnimation *_animationOut_maxHeight = nullptr;
    QPropertyAnimation *_animationOut_minHeight = nullptr;
    QPropertyAnimation *_animationOut_maxWidth = nullptr;
    QPropertyAnimation *_animationOut_minWidth = nullptr;
    QPropertyAnimation *_animationOut_opacity = nullptr;
    QGraphicsOpacityEffect *_effect_opacity = nullptr;
};

#endif // WIDGETANIMATION_H
