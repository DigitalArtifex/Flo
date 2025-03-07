/*
* QAnimatedToolBox
*
* Provides animated replacement for QToolBox (WIP)
*
* Copyright (C) 2024-2025 DigitalArtifex
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
