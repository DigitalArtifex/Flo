#include "qanimatedtoolbox.h"

QAnimatedToolBox::QAnimatedToolBox(QWidget *parent)
    : QFrame(parent)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setSpacing(m_spacing);

    setLayout(m_layout);

    m_animations = new QParallelAnimationGroup(this);
    connect(m_animations, SIGNAL(finished()), this, SLOT(onAnimationsFinished()));
}

int QAnimatedToolBox::spacing() const
{
    return m_spacing;
}

int QAnimatedToolBox::indexOf(QWidget *widget, qsizetype from)
{
    return m_widgets.indexOf(widget, from);
}

QWidget *QAnimatedToolBox::widget(int index)
{
    if(index >= 0 && index < m_widgets.count())
        return m_widgets[index];

    return nullptr;
}

void QAnimatedToolBox::addItem(QWidget *widget, QIcon icon, QString title)
{
    QAnimatedToolBoxButton *button = new QAnimatedToolBoxButton(icon, title, this);
    append(button, widget);
}

void QAnimatedToolBox::addItem(QWidget *widget, QString title)
{
    QAnimatedToolBoxButton *button = new QAnimatedToolBoxButton(title, this);
    append(button, widget);
}

void QAnimatedToolBox::addItem(QWidget *widget)
{
    QAnimatedToolBoxButton *button = new QAnimatedToolBoxButton(QString("Page %1").arg(m_widgets.count() + 1), this);
    append(button, widget);
}

void QAnimatedToolBox::insertItem(int index, QWidget *widget, QIcon icon, QString title)
{
    if(index == m_currentIndex && m_widgets.count() > 0)
    {
        m_currentIndex++;
    }

    for(int i = index; i < m_buttons.count(); i++)
    {
        m_layout->removeWidget(m_buttons[i]);
        m_layout->removeWidget(m_animatedWidgets[i]);
    }

    QAnimatedToolBoxButton *button = new QAnimatedToolBoxButton(icon, title, this);
    button->setFixedHeight(m_toolBoxButtonHeight);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    button->setCheckable(true);
    button->setChecked(false);

    connect(button, SIGNAL(clicked(QAnimatedToolBoxButton*)), this, SLOT(onButtonClicked(QAnimatedToolBoxButton*)));

    QAnimatedWidget *animated = new QAnimatedWidget(this);
    animated->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    animated->setCentralWidget(widget);

    m_buttons.insert(index, button);
    m_widgets.insert(index, widget);
    m_animatedWidgets.insert(index, animated);

    for(int i = index; i < m_buttons.count(); i++)
    {
        m_layout->addWidget(m_buttons[i]);
        m_layout->addWidget(m_animatedWidgets[i]);

        if(i == m_currentIndex)
        {
            m_widgets[i]->setMaximumHeight(QWIDGETSIZE_MAX);
            m_animatedWidgets[i]->setMaximumHeight(QWIDGETSIZE_MAX);
        }
        else
            m_animatedWidgets[i]->setMaximumHeight(0);
    }
}

void QAnimatedToolBox::insertItem(int index, QWidget *widget, QString title)
{
    if(index == m_currentIndex && m_widgets.count() > 0)
        m_currentIndex++;

    for(int i = index; i < m_buttons.count(); i++)
    {
        m_layout->removeWidget(m_buttons[i]);
        m_layout->removeWidget(m_animatedWidgets[i]);
    }

    QAnimatedToolBoxButton *button = new QAnimatedToolBoxButton(title, this);
    button->setFixedHeight(m_toolBoxButtonHeight);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    button->setCheckable(true);
    button->setChecked(false);

    connect(button, SIGNAL(clicked(QAnimatedToolBoxButton*)), this, SLOT(onButtonClicked(QAnimatedToolBoxButton*)));

    QAnimatedWidget *animated = new QAnimatedWidget(this);
    animated->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    animated->setCentralWidget(widget);
    animated->setMaximumHeight(0);

    m_buttons.insert(index, button);
    m_widgets.insert(index, widget);
    m_animatedWidgets.insert(index, animated);

    for(int i = index; i < m_buttons.count(); i++)
    {
        m_layout->addWidget(m_buttons[i]);
        m_layout->addWidget(m_animatedWidgets[i]);

        if(i == m_currentIndex)
        {
            m_widgets[i]->setMaximumHeight(QWIDGETSIZE_MAX);
            m_animatedWidgets[i]->setMaximumHeight(QWIDGETSIZE_MAX);
        }
        else
            m_animatedWidgets[i]->setMaximumHeight(0);
    }
}

void QAnimatedToolBox::removeItem(int index)
{
    if(index >= 0 && index < m_widgets.count())
    {
        QAnimatedToolBoxButton *button = m_buttons.takeAt(index);
        QWidget *widget = m_widgets.takeAt(index);
        QAnimatedWidget *animated = m_animatedWidgets.takeAt(index);

        m_layout->removeWidget(button);
        m_layout->removeWidget(animated);
        delete button;
        delete animated;
    }
}

void QAnimatedToolBox::removeItem(QWidget *widget)
{
    removeItem(indexOf(widget));
}

void QAnimatedToolBox::setItemIcon(int index, const QIcon &icon)
{
    if(index < 0 || index > m_buttons.count())
        return;

    m_buttons[index]->setIcon(icon);
}

void QAnimatedToolBox::setItemText(int index, const QString &text)
{
    if(index < 0 || index > m_buttons.count())
        return;

    m_buttons[index]->setText(text);
}

void QAnimatedToolBox::setSpacing(int spacing)
{
    if (m_spacing == spacing)
        return;

    m_spacing = spacing;
    m_layout->setSpacing(spacing);

    emit spacingChanged();
}

void QAnimatedToolBox::append(QAnimatedToolBoxButton *button, QWidget *widget)
{
    button->setFixedHeight(m_toolBoxButtonHeight);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    button->setCheckable(true);
    button->setChecked(false);

    connect(button, SIGNAL(clicked(QAnimatedToolBoxButton*)), this, SLOT(onButtonClicked(QAnimatedToolBoxButton*)));

    widget->setParent(this);

    QAnimatedWidget *animated = new QAnimatedWidget(this);
    animated->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    animated->setCentralWidget(widget);

    layout()->addWidget(button);
    layout()->addWidget(animated);

    if(m_widgets.count() > 0)
        animated->setMaximumHeight(0);
    else
    {
        button->setChecked(true);
        animated->setMaximumHeight(QWIDGETSIZE_MAX);
        widget->setMaximumHeight(QWIDGETSIZE_MAX);
    }

    m_buttons.append(button);
    m_widgets.append(widget);
    m_animatedWidgets.append(animated);
}

int QAnimatedToolBox::animationDuration() const
{
    return m_animationDuration;
}

void QAnimatedToolBox::setAnimationDuration(int animationDuration)
{
    m_animationDuration = animationDuration;
}

int QAnimatedToolBox::toolBoxButtonHeight() const
{
    return m_toolBoxButtonHeight;
}

void QAnimatedToolBox::setToolBoxButtonHeight(int toolBoxButtonHeight)
{
    if (m_toolBoxButtonHeight == toolBoxButtonHeight)
        return;

    for(QAnimatedToolBoxButton *button : m_buttons)
        button->setFixedHeight(toolBoxButtonHeight);

    m_toolBoxButtonHeight = toolBoxButtonHeight;
    emit toolBoxButtonHeightChanged();
}

void QAnimatedToolBox::onButtonClicked(QAnimatedToolBoxButton *button)
{
    int index = m_buttons.indexOf(button);

    qDebug() << "Button" << index << "clicked, current index" << m_currentIndex;

    if(m_animating || index < 0 || index == m_currentIndex)
    {
        button->setChecked(!button->isChecked());
        return;
    }

    m_buttons[m_currentIndex]->setChecked(false);
    setCurrentIndex(index);
}

void QAnimatedToolBox::onAnimationsFinished()
{
    qDebug() << "Animations finished. Previous index" << m_currentIndex << ", new index" << m_nextIndex;

    m_currentIndex = m_nextIndex;
    m_nextIndex = 0;
    m_animatedWidgets[m_currentIndex]->setMaximumHeight(QWIDGETSIZE_MAX);
    update();
    m_animating = false;
    emit currentIndexChanged();
}

void QAnimatedToolBox::resizeEvent(QResizeEvent *event)
{
    QFrame::resizeEvent(event);
}

int QAnimatedToolBox::currentIndex() const
{
    return m_currentIndex;
}

void QAnimatedToolBox::setCurrentIndex(int currentIndex)
{
    if(currentIndex < 0 || currentIndex >= m_widgets.count())
        return;

    if (m_currentIndex == currentIndex)
        return;

    if(!m_buttons[currentIndex]->isChecked())
        m_buttons[currentIndex]->setChecked(true);

    if(m_buttons[m_currentIndex]->isChecked())
        m_buttons[m_currentIndex]->setChecked(false);

    m_nextIndex = currentIndex;

    QAnimatedWidget *currentWidget = m_animatedWidgets[m_currentIndex];
    QAnimatedWidget *nextWidget = m_animatedWidgets[m_nextIndex];

    if(!currentWidget || !nextWidget)
        return;

    if(visibleRegion().isEmpty())
    {
        currentWidget->setMaximumHeight(0);
        nextWidget->setMaximumHeight(QWIDGETSIZE_MAX);
        onAnimationsFinished();

        return;
    }

    m_animations = new QParallelAnimationGroup(this);
    connect(m_animations, SIGNAL(finished()), this, SLOT(onAnimationsFinished()));

    QPropertyAnimation *currentWidgetAnimation = new QPropertyAnimation(currentWidget, "maximumHeight");
    QPropertyAnimation *nextWidgetAnimation = new QPropertyAnimation(nextWidget, "maximumHeight");

    int showHeight = currentWidget->height();

    currentWidgetAnimation->setDuration(m_animationDuration);
    currentWidgetAnimation->setStartValue(showHeight);
    currentWidgetAnimation->setEndValue(0);

    nextWidgetAnimation->setDuration(m_animationDuration);
    nextWidgetAnimation->setStartValue(0);
    nextWidgetAnimation->setEndValue(showHeight);

    m_animatedWidgets[m_currentIndex]->initAnimations();
    m_animatedWidgets[m_currentIndex]->addAnimation(currentWidgetAnimation);
    m_animatedWidgets[m_nextIndex]->initAnimations();
    m_animatedWidgets[m_nextIndex]->addAnimation(nextWidgetAnimation);

    m_animations->addAnimation(m_animatedWidgets[m_currentIndex]->animations());
    m_animations->addAnimation(m_animatedWidgets[m_nextIndex]->animations());

    m_animating = true;
    m_animations->start(QAbstractAnimation::DeleteWhenStopped);
}

void QAnimatedToolBox::setCurrentWidget(QWidget *widget)
{
    setCurrentIndex(indexOf(widget));
}
