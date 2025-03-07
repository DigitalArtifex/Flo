/*
* QNumberEdit - A simple QDoubleSpinBox replacement that doesnt focus suffix/prefix text
* Copyright (C) 2025 DigitalArtifex
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

#ifndef QNUMBEREDIT_H
#define QNUMBEREDIT_H

#include <QFrame>
#include <QTimer>
#include "qspinbox.h"

namespace Ui {
class QNumberEdit;
}

class QNumberEdit : public QFrame
{
    Q_OBJECT

public:
    explicit QNumberEdit(QWidget *parent = nullptr);
    ~QNumberEdit();

    qreal value() const;
    void setValue(qreal value);

    qreal minimum() const;
    void setMinimum(qreal minimum);

    qreal maximum() const;
    void setMaximum(qreal maximum);

    QString prefix() const;
    void setPrefix(const QString &prefix);

    QString suffix() const;
    void setSuffix(const QString &suffix);

    qreal step() const;

public slots:
    void setStep(qreal step);

signals:
    void valueChanged(const qreal &);

    void minimumChanged();

    void maximumChanged();

    void prefixChanged();

    void suffixChanged();

    void stepChanged();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void setValuePrivate(qreal value);

    void on_spinUpButton_pressed();
    void onStepTimerTimeout();
    void onButtonHoldTimerTimeout();

    void on_spinDownButton_pressed();

    void on_spinUpButton_released();

    void on_spinDownButton_released();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void focusInEvent(QFocusEvent *event) override;
    virtual void changeEvent(QEvent *event) override;
    void createStepTimer();
    void deleteStepTimer();

private:
    virtual bool eventFilter(QObject *object, QEvent *event) override;
    Ui::QNumberEdit *ui;
    QTimer *m_stepTimer = nullptr;
    QTimer *m_buttonHoldTimer = nullptr;
    bool m_stepIncrement = true;

    qreal m_value = 0.00;
    qreal m_minimum = 0.00;
    qreal m_maximum = 100.00;
    qreal m_step = 1;

    QString m_prefix;
    QString m_suffix;
    QSpinBox *m_spinbox;

    QObjectList m_focusObjects;
    bool m_childFocused = false;

    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged FINAL)
    Q_PROPERTY(qreal minimum READ minimum WRITE setMinimum NOTIFY minimumChanged FINAL)
    Q_PROPERTY(qreal maximum READ maximum WRITE setMaximum NOTIFY maximumChanged FINAL)
    Q_PROPERTY(QString prefix READ prefix WRITE setPrefix NOTIFY prefixChanged FINAL)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix NOTIFY suffixChanged FINAL)
    Q_PROPERTY(qreal step READ step WRITE setStep NOTIFY stepChanged FINAL)
};

Q_DECLARE_METATYPE(QNumberEdit)

#endif // QNUMBEREDIT_H
