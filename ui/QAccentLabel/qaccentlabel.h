/*
* QAccentLabel
*
* Provides a widget that contains a QLabel and a color accent
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

#ifndef QACCENTLABEL_H
#define QACCENTLABEL_H

#include <QFrame>

namespace Ui {
class QAccentLabel;
}

class QAccentLabel : public QFrame
{
    Q_OBJECT

public:
    explicit QAccentLabel(QWidget *parent = nullptr);
    ~QAccentLabel();

    QColor accentColor() const;

    QString text() const;

    qint8 accentWidth() const;

public slots:
    void setAccentColor(const QColor &accentColor);

    void setText(const QString &text);

    void setAccentWidth(qint8 accentWidth);

signals:
    void accentColorChanged();

    void textChanged();

    void accentWidthChanged();

private:
    Ui::QAccentLabel *ui;

    qint8 m_accentWidth = 10;
    QColor m_accentColor = QColor("#800080");

    Q_PROPERTY(QColor accentColor READ accentColor WRITE setAccentColor NOTIFY accentColorChanged FINAL)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged FINAL)
    Q_PROPERTY(qint8 accentWidth READ accentWidth WRITE setAccentWidth NOTIFY accentWidthChanged FINAL)
};

#endif // QACCENTLABEL_H
