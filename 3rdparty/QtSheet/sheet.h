#ifndef SHEETPANEL_H
#define SHEETPANEL_H

#include <QWidget>
#include <QFrame>
#include <QPropertyAnimation>
#include <QWidget>
#include <QKeyEvent>
#include <functional>

class AnimatedWidget;

/* the sheet implementation
 * the animations are made using QPropertyAnimation, which is conviniently provided by AnimatedWidget
 */
class Sheet : public QWidget
{
    Q_OBJECT

public:
    enum Side
    {
        Left,
        Right
    };

    int m_width = 400;  // width in pixels
    int m_showDurationMs = 350; // default show duration in milliseconds
    int m_hideDurationMs = 350; // default hide duration in milliseconds
    bool m_showTopRightCloseButton = true; // 
    
    Side m_side = Right;
    QWidget *m_content = nullptr;
    QWidget *m_destination;
    AnimatedWidget *m_backdrop;
    AnimatedWidget *m_sidepanel;
    QWidget *m_buttonBar;

public:
    Sheet(QWidget *content, QWidget *parent = nullptr);
    ~Sheet();

    void showSheet(QWidget *destination, Side side = Right);
    void hideSheet(bool animated = true);
    void layout(bool animated = true);

    int width() const { return m_width; }
    void setWidth(int width) { m_width = width; }

    int showDurationMs() const { return m_showDurationMs; }
    void setShowDurationMs(int duration) { m_showDurationMs = duration; }

    int hideDurationMs() const { return m_hideDurationMs; }
    void setHideDurationMs(int duration) { m_hideDurationMs = duration; }

    bool showTopRightCloseButton() const { return m_showTopRightCloseButton; }
    void setShowTopRightCloseButton(bool show) { m_showTopRightCloseButton = show; }
};
;

class AnimatedWidget : public QFrame
{
    Q_OBJECT
public:
    Q_PROPERTY(QPoint position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

    explicit AnimatedWidget(QWidget *parent = nullptr) : QFrame(parent) {
        this->installEventFilter(this);
        for(QObject* child : children()) {
            child->installEventFilter(this);
        }
    }

    QPoint position() const { return m_position; };
    void setPosition(const QPoint position)
    {
        if (m_position == position) {
            return;
        }
        m_position = position;
        this->move(m_position);
        emit positionChanged(m_position);
    }
    // animated
    void setPositionA(const QPoint position, int durationMs = 350, std::function<void()> onFinished = nullptr)
    {
        if (positionAnimation) {
            positionAnimation->stop();
            delete positionAnimation;
        }
        auto anim = new QPropertyAnimation(this, "position");
        this->positionAnimation = anim;
        anim->setEasingCurve(QEasingCurve::InOutCubic);
        anim->setDuration(durationMs);
        anim->setStartValue(m_position);
        anim->setEndValue(position);
        anim->start();
        if (onFinished != nullptr) {
            anim->connect(anim, &QPropertyAnimation::finished, this, [=]() { onFinished(); });
        }
    }

    QColor backgroundColor() const { return m_backgroundColor; };
    void setBackgroundColor(const QColor color)
    {
        if (m_backgroundColor == color) {
            return;
        }
        applyBackgroundColor(m_backgroundColor);
        emit backgroundColorChanged(m_backgroundColor);
    }

    void applyBackgroundColor(QColor color)
    {
        m_backgroundColor = color;
        auto backdropPalette = palette();
        backdropPalette.setColor(QPalette::Window, color);
        setAutoFillBackground(true);
        setPalette(backdropPalette);
    }

    void setBackgroundColorA(
        const QColor color, 
        int durationMs = 500,
        std::function<void()> onFinished = nullptr)
    {
        if (backgroundColorAnimation) {
            backgroundColorAnimation->stop();
            delete backgroundColorAnimation;
        }
        auto anim = new QPropertyAnimation(this, "backgroundColor");
        this->backgroundColorAnimation = anim;
        //anim->setEasingCurve(QEasingCurve::InOutCubic);
        anim->setDuration(durationMs);
        anim->setStartValue(m_backgroundColor);
        anim->setEndValue(color);
        anim->start();
        connect(anim, &QPropertyAnimation::valueChanged, this, [this, anim] {
            auto v = anim->currentValue();
            // get the color from the animation
            applyBackgroundColor(v.value<QColor>());
        });
        if (onFinished != nullptr) {
            anim->connect(anim, &QPropertyAnimation::finished, this, [=]() { onFinished(); });
        }
    }


signals:
    void positionChanged(const QPoint point);
    void backgroundColorChanged(const QColor color);

private:
    QPoint m_position = QPoint(0, 0);
    QColor m_backgroundColor = QColor(0,0,0,0);
    QPropertyAnimation *positionAnimation = nullptr;
    QPropertyAnimation *backgroundColorAnimation = nullptr;
};

#endif // SHEETPANEL_H
