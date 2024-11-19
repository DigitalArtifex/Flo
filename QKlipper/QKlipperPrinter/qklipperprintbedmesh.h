/*!
 * QKlipper - A Qt library for the Klipper/Moonraker API
 * Copyright (C) 2024 James Dudeck
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QKLIPPERPRINTBEDMESH_H
#define QKLIPPERPRINTBEDMESH_H

#include <QObject>
#include <QVector3D>
#include <QVector2D>

typedef QList<QList<QVector3D>> QVertexTable;

class QKlipperConsole;

//!  QKlipperPrintBedMesh class
/*!
  This class provides the current bed mesh configuration as well as the probed and calculated mesh
*/
class QKlipperPrintBedMesh : public QObject
{
    Q_OBJECT

    friend QKlipperConsole;
public:

    /*!
     * Constructor
     *
     * \param parent The parent object
     */
    explicit QKlipperPrintBedMesh(QObject *parent = nullptr);

    qreal fadeEnd() const;

    qreal fadeStart() const;

    qreal fadeTarget() const;

    qreal horizontalMoveZ() const;

    qreal adaptiveMargin() const;

    qreal speed() const;

    qreal tension() const;

    qreal splitDeltaZ() const;

    qreal moveCheckDistance() const;

    QString profileName() const;

    QStringList profiles() const;

    QList<QList<qreal> > matrix() const;

    QList<QList<qreal> > probed() const;

    QString algorithm() const;

    QVertexTable verticies();

    QVector2D minimum() const;

    QVector2D maximum() const;

    QVector2D probeCount() const;

public slots:
    void setMinimum(const QVector2D &minimum);

    void setMaximum(const QVector2D &maximum);

    void setProbeCount(const QVector2D &probeCount);

private slots:
    void setFadeEnd(qreal fadeEnd);

    void setFadeStart(qreal fadeStart);

    void setFadeTarget(qreal fadeTarget);

    void setHorizontalMoveZ(qreal horizontalMoveZ);

    void setAdaptiveMargin(qreal adaptiveMargin);

    void setSpeed(qreal speed);

    void setTension(qreal tension);

    void setSplitDeltaZ(qreal splitDeltaZ);

    void setMoveCheckDistance(qreal moveCheckDistance);

    void setProfileName(const QString &profileName);

    void setProfiles(const QStringList &profiles);

    void setMatrix(const QList<QList<qreal> > matrix);

    void setProbed(const QList<QList<qreal> > probed);

    void setAlgorithm(const QString &algorithm);

signals:

    void fadeEndChanged();
    void fadeStartChanged();
    void fadeTargetChanged();
    void horizontalMoveZChanged();
    void adaptiveMarginChanged();
    void speedChanged();
    void tensionChanged();
    void splitDeltaZChanged();
    void moveCheckDistanceChanged();
    void profileNameChanged();
    void profilesChanged();
    void matrixChanged();
    void probedChanged();
    void algorithmChanged();

    void minimumChanged();

    void maximumChanged();

    void probeCountChanged();

private:

    qreal m_fadeEnd = 0;
    qreal m_fadeStart = 0;
    qreal m_fadeTarget = 0;
    qreal m_horizontalMoveZ = 0;
    qreal m_adaptiveMargin = 0;
    qreal m_speed = 0;
    qreal m_tension = 0;
    qreal m_splitDeltaZ = 0;
    qreal m_moveCheckDistance = 0;

    QString m_profileName;
    QStringList m_profiles;

    QVector2D m_minimum;
    QVector2D m_maximum;
    QVector2D m_probeCount;

    QList<QList<qreal>> m_matrix;
    QList<QList<qreal>> m_probed;

    QString m_algorithm;

    Q_PROPERTY(qreal fadeEnd READ fadeEnd WRITE setFadeEnd NOTIFY fadeEndChanged FINAL)
    Q_PROPERTY(qreal fadeStart READ fadeStart WRITE setFadeStart NOTIFY fadeStartChanged FINAL)
    Q_PROPERTY(qreal fadeTarget READ fadeTarget WRITE setFadeTarget NOTIFY fadeTargetChanged FINAL)
    Q_PROPERTY(qreal horizontalMoveZ READ horizontalMoveZ WRITE setHorizontalMoveZ NOTIFY horizontalMoveZChanged FINAL)
    Q_PROPERTY(qreal adaptiveMargin READ adaptiveMargin WRITE setAdaptiveMargin NOTIFY adaptiveMarginChanged FINAL)
    Q_PROPERTY(qreal speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)
    Q_PROPERTY(qreal tension READ tension WRITE setTension NOTIFY tensionChanged FINAL)
    Q_PROPERTY(qreal splitDeltaZ READ splitDeltaZ WRITE setSplitDeltaZ NOTIFY splitDeltaZChanged FINAL)
    Q_PROPERTY(qreal moveCheckDistance READ moveCheckDistance WRITE setMoveCheckDistance NOTIFY moveCheckDistanceChanged FINAL)
    Q_PROPERTY(QString profileName READ profileName WRITE setProfileName NOTIFY profileNameChanged FINAL)
    Q_PROPERTY(QStringList profiles READ profiles WRITE setProfiles NOTIFY profilesChanged FINAL)
    Q_PROPERTY(QList<QList<qreal> > matrix READ matrix WRITE setMatrix NOTIFY matrixChanged FINAL)
    Q_PROPERTY(QList<QList<qreal> > probed READ probed WRITE setProbed NOTIFY probedChanged FINAL)
    Q_PROPERTY(QString algorithm READ algorithm WRITE setAlgorithm NOTIFY algorithmChanged FINAL)
    Q_PROPERTY(QVector2D minimum READ minimum WRITE setMinimum NOTIFY minimumChanged FINAL)
    Q_PROPERTY(QVector2D maximum READ maximum WRITE setMaximum NOTIFY maximumChanged FINAL)
    Q_PROPERTY(QVector2D probeCount READ probeCount WRITE setProbeCount NOTIFY probeCountChanged FINAL)
};

#endif // QKLIPPERPRINTBEDMESH_H
