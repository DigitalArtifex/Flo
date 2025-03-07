#include "qanimatedwidget.h"

QAnimatedWidget::QAnimatedWidget(QWidget *parent)
    : QFrame{parent}
{
    m_animations = new QParallelAnimationGroup(this);
    connect(m_animations, SIGNAL(stateChanged(QAbstractAnimation::State,QAbstractAnimation::State)), this, SLOT(onAnimationsStateChanged(QAbstractAnimation::State,QAbstractAnimation::State)));
}

QAnimatedWidget::~QAnimatedWidget()
{
    if(m_snapshotLabel)
    {
        if(m_layout)
            m_layout->removeWidget(m_snapshotLabel);

        delete m_snapshotLabel;
    }

    if(m_centralWidget)
    {
        if(m_layout)
            m_layout->removeWidget(m_centralWidget);

        delete m_centralWidget;
    }

    if(m_layout)
        delete m_layout;
}

void QAnimatedWidget::renderSnapshot()
{
    if(!m_snapshotLabel)
        m_snapshotLabel = new QLabel(this);

    if(!visibleRegion().isEmpty())
    {
        //switch to a snapshot of the actual widget to prevent performance issues
        QImage snapshot(size(), QImage::Format_ARGB32);
        snapshot.fill(Qt::transparent);

        QPainter painter(&snapshot);
        //painter.setRenderHints(QPainter::Antialiasing);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

        if(m_centralWidget)
            m_centralWidget->render(&painter, QPoint(), visibleRegion().boundingRect(), QWidget::DrawChildren);

        m_snapshot = QPixmap::fromImage(snapshot);
    }

    m_snapshotLabel->setPixmap(m_snapshot);
    m_snapshotLabel->resize(m_snapshot.size());
    m_snapshotLabel->show();

    //hide after showing the snapshot to prevent flicker
    if(m_centralWidget)
    {
        m_layout->removeWidget(m_centralWidget);
        m_centralWidget->hide();
    }
}

QWidget *QAnimatedWidget::centralWidget() const
{
    return m_centralWidget;
}

void QAnimatedWidget::setCentralWidget(QWidget *centralWidget)
{
    if(!m_layout)
    {
        m_layout = new QVBoxLayout(this);
        m_layout->setContentsMargins(0,0,0,0);
        setLayout(m_layout);
    }

    if(m_centralWidget)
    {
        m_layout->removeWidget(m_centralWidget);
        delete m_centralWidget;
        m_centralWidget = nullptr;
    }

    m_centralWidget = centralWidget;
    m_layout->addWidget(m_centralWidget);
}

void QAnimatedWidget::initAnimations()
{
    m_animations = new QParallelAnimationGroup(this);
    connect(m_animations, SIGNAL(stateChanged(QAbstractAnimation::State,QAbstractAnimation::State)), this, SLOT(onAnimationsStateChanged(QAbstractAnimation::State,QAbstractAnimation::State)));
}

QParallelAnimationGroup *QAnimatedWidget::animations() const
{
    return m_animations;
}

void QAnimatedWidget::addAnimation(QAbstractAnimation *animation)
{
    m_animations->addAnimation(animation);
}

void QAnimatedWidget::resizeEvent(QResizeEvent *event)
{
    QFrame::resizeEvent(event);
}

void QAnimatedWidget::onAnimationsStateChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    if((oldState == QAbstractAnimation::Stopped) && (newState == QAbstractAnimation::Running))
        renderSnapshot();
    else if(newState == QAbstractAnimation::Stopped)
    {
        m_layout->addWidget(m_centralWidget);

        m_centralWidget->show();

        if(m_snapshotLabel)
        {
            m_layout->removeWidget(m_snapshotLabel);
            m_snapshotLabel->hide();
            delete m_snapshotLabel;
            m_snapshotLabel = nullptr;
        }
    }
}
