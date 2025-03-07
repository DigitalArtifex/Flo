/*
* Flo
*
* Provides a means of monitoring application load progress
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

#ifndef FLO_H
#define FLO_H

#include <QObject>
#include <QUuid>
#include <QtConcurrent/QtConcurrent>

#include "qklipperinstancepool.h"

#include "settings.h"

//generate operators for c++11
#ifndef Q_DECLARE_ENUM_FLAGS
#define Q_DECLARE_ENUM_FLAGS(TYPE)                                                          \
                                                                                            \
inline constexpr TYPE operator|(TYPE a, TYPE b)                                             \
{                                                                                           \
    return static_cast<TYPE>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));     \
}                                                                                           \
                                                                                            \
inline constexpr TYPE operator&(TYPE a, TYPE b)                                             \
{                                                                                           \
    return static_cast<TYPE>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));     \
}                                                                                           \
                                                                                            \
inline constexpr TYPE operator^(TYPE a, TYPE b)                                             \
{                                                                                           \
    return static_cast<TYPE>(static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b));     \
}                                                                                           \
                                                                                            \
inline constexpr TYPE operator~(TYPE a)                                                     \
{                                                                                           \
    return static_cast<TYPE>(~static_cast<unsigned int>(a));                                \
}                                                                                           \
inline constexpr TYPE operator|=(TYPE &a, TYPE b)                                           \
{                                                                                           \
    return a = static_cast<TYPE>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b)); \
}                                                                                           \
                                                                                            \
inline constexpr TYPE operator&=(TYPE &a, TYPE b)                                           \
{                                                                                           \
    return a = static_cast<TYPE>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b)); \
}                                                                                           \
                                                                                            \
inline constexpr TYPE operator^=(TYPE &a, TYPE b)                                           \
{                                                                                           \
    return a = static_cast<TYPE>(static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b)); \
}
#endif

class Flo : public QObject
{
    Q_OBJECT
    explicit Flo(QObject *parent = nullptr);
public:

    static QString generatId();
    static Flo *instance();
    void start();

    static QKlipperInstancePool *printerPool();
    static Settings *settings();

signals:
    void loading();
    void loadingProgress(QString message, qreal progress);
    void loadingFinished();

private:
    void on_loading();
    void on_loadingProgress(QString message, qreal progress);
    void on_loadingFinished();

private:
    static QKlipperInstancePool *m_printerPool;
    static Settings *m_settings;

    static Flo *m_instance;
};

#endif // FLO_H
