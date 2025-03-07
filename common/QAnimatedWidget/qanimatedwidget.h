#ifndef QANIMATEDWIDGET_H
#define QANIMATEDWIDGET_H

#include <QObject>
#include <QFrame>
#include <QLabel>
#include <QGridLayout>
#include <QPixmap>
#include <QPainter>
#include <QResizeEvent>
#include <QParallelAnimationGroup>

class QAnimatedWidget : public QFrame
{
    Q_OBJECT
public:
    explicit QAnimatedWidget(QWidget *parent = nullptr);
    ~QAnimatedWidget();

    QParallelAnimationGroup *animations() const;
    void addAnimation(QAbstractAnimation *animation);

    QWidget *centralWidget() const;

public slots:
    void setCentralWidget(QWidget *centralWidget);
    void initAnimations();

protected:
    virtual void resizeEvent(QResizeEvent *event);

signals:
    void animationFinished();
    void animationFinished(QAnimatedWidget*);

private slots:
    void renderSnapshot();
    void onAnimationsStateChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);

private:
    QParallelAnimationGroup *m_animations = nullptr;
    QLabel *m_snapshotLabel = nullptr;
    QWidget *m_centralWidget = nullptr;
    QVBoxLayout *m_layout = nullptr;
    QPixmap m_snapshot;
};

#endif // QANIMATEDWIDGET_H
