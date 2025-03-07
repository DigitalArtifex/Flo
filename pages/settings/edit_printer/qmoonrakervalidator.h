/*
* Flo :: QMoonrakerValidator
*
* Provides a validation for moonraker instances (WIP)
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

#ifndef QMOONRAKERVALIDATOR_H
#define QMOONRAKERVALIDATOR_H

#include <QObject>
#include <QDir>
#include <QValidator>
#include <QRegularExpression>

class QMoonrakerValidator : public QValidator
{
    Q_OBJECT
public:
    explicit QMoonrakerValidator(QObject *parent = nullptr);
    ~QMoonrakerValidator();

    virtual QValidator::State validate(QString &text, int &pos) const;

private:
    QRegularExpression m_httpExpression = QRegularExpression("^\\s*(http|https)\\:\\/\\/");
};

#endif // QMOONRAKERVALIDATOR_H
