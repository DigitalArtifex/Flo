#include "qklipperprintbedmesh.h"
#include "qdebug.h"

QKlipperPrintBedMesh::QKlipperPrintBedMesh(QObject *parent)
    : QObject{parent}
{

}

qreal QKlipperPrintBedMesh::fadeEnd() const
{
    return m_fadeEnd;
}

void QKlipperPrintBedMesh::setFadeEnd(qreal fadeEnd)
{
    if (qFuzzyCompare(m_fadeEnd, fadeEnd))
        return;
    m_fadeEnd = fadeEnd;
    emit fadeEndChanged();
}

qreal QKlipperPrintBedMesh::fadeStart() const
{
    return m_fadeStart;
}

void QKlipperPrintBedMesh::setFadeStart(qreal fadeStart)
{
    if (qFuzzyCompare(m_fadeStart, fadeStart))
        return;
    m_fadeStart = fadeStart;
    emit fadeStartChanged();
}

qreal QKlipperPrintBedMesh::fadeTarget() const
{
    return m_fadeTarget;
}

void QKlipperPrintBedMesh::setFadeTarget(qreal fadeTarget)
{
    if (qFuzzyCompare(m_fadeTarget, fadeTarget))
        return;
    m_fadeTarget = fadeTarget;
    emit fadeTargetChanged();
}

qreal QKlipperPrintBedMesh::horizontalMoveZ() const
{
    return m_horizontalMoveZ;
}

void QKlipperPrintBedMesh::setHorizontalMoveZ(qreal horizontalMoveZ)
{
    if (qFuzzyCompare(m_horizontalMoveZ, horizontalMoveZ))
        return;
    m_horizontalMoveZ = horizontalMoveZ;
    emit horizontalMoveZChanged();
}

qreal QKlipperPrintBedMesh::adaptiveMargin() const
{
    return m_adaptiveMargin;
}

void QKlipperPrintBedMesh::setAdaptiveMargin(qreal adaptiveMargin)
{
    if (qFuzzyCompare(m_adaptiveMargin, adaptiveMargin))
        return;
    m_adaptiveMargin = adaptiveMargin;
    emit adaptiveMarginChanged();
}

qreal QKlipperPrintBedMesh::speed() const
{
    return m_speed;
}

void QKlipperPrintBedMesh::setSpeed(qreal speed)
{
    if (qFuzzyCompare(m_speed, speed))
        return;
    m_speed = speed;
    emit speedChanged();
}

qreal QKlipperPrintBedMesh::tension() const
{
    return m_tension;
}

void QKlipperPrintBedMesh::setTension(qreal tension)
{
    if (qFuzzyCompare(m_tension, tension))
        return;
    m_tension = tension;
    emit tensionChanged();
}

qreal QKlipperPrintBedMesh::splitDeltaZ() const
{
    return m_splitDeltaZ;
}

void QKlipperPrintBedMesh::setSplitDeltaZ(qreal splitDeltaZ)
{
    if (qFuzzyCompare(m_splitDeltaZ, splitDeltaZ))
        return;
    m_splitDeltaZ = splitDeltaZ;
    emit splitDeltaZChanged();
}

qreal QKlipperPrintBedMesh::moveCheckDistance() const
{
    return m_moveCheckDistance;
}

void QKlipperPrintBedMesh::setMoveCheckDistance(qreal moveCheckDistance)
{
    if (qFuzzyCompare(m_moveCheckDistance, moveCheckDistance))
        return;

    m_moveCheckDistance = moveCheckDistance;
    emit moveCheckDistanceChanged();
}

QString QKlipperPrintBedMesh::profileName() const
{
    return m_profileName;
}

void QKlipperPrintBedMesh::setProfileName(const QString &profileName)
{
    if (m_profileName == profileName)
        return;
    m_profileName = profileName;
    emit profileNameChanged();
}

QStringList QKlipperPrintBedMesh::profiles() const
{
    return m_profiles;
}

void QKlipperPrintBedMesh::setProfiles(const QStringList &profiles)
{
    if (m_profiles == profiles)
        return;

    m_profiles = profiles;
    emit profilesChanged();
}

QList<QList<qreal> > QKlipperPrintBedMesh::matrix() const
{
    return m_matrix;
}

void QKlipperPrintBedMesh::setMatrix(const QList<QList<qreal> > matrix)
{
    m_matrix = matrix;
    emit matrixChanged();
}

QList<QList<qreal> > QKlipperPrintBedMesh::probed() const
{
    return m_probed;
}

void QKlipperPrintBedMesh::setProbed(const QList<QList<qreal> > probed)
{
    m_probed = probed;
    emit probedChanged();
}

QString QKlipperPrintBedMesh::algorithm() const
{
    return m_algorithm;
}

//       0    1    2    3
//       ____ ____ ____ ____
// Row 0|    |    |    |    |
//      |____|____|____|____|
// Row 1|    |    |    |    |
//      |____|____|____|____|
// Row 2|    |    |    |    |
//      |____|____|____|____|
// Row 3|    |    |    |    |
//      |____|____|____|____|
QVertexTable QKlipperPrintBedMesh::verticies()
{
    QVertexTable vertexList;
    QVector2D increments;
    QVector2D span;

    if(!m_matrix.isEmpty() && !m_matrix[0].isEmpty())
    {
        //calculate the distance between the first and last probe points
        span.setX(m_maximum.x() - m_minimum.x());
        span.setY(m_maximum.y() - m_minimum.y());

        //calculate the distance between each probe point
        increments.setY(span.y() / m_matrix.count());
        increments.setX(span.x() / m_matrix[0].count());

        vertexList.reserve(m_matrix.count());

        for(int row = 0; row < m_matrix.count(); row++)
        {
            vertexList.insert(row, QList<QVector3D>());
            vertexList[row].reserve(m_matrix[row].count());

            QList<qreal> rowData = m_matrix[row];
            QVector2D currentPoint;

            currentPoint.setY(m_minimum.y() + (row * increments.y()));

            for(int col = 0; col < rowData.count(); col++)
            {
                currentPoint.setX(m_minimum.x() + (col * increments.x()));

                QVector3D vertex(currentPoint);
                vertex.setZ(m_matrix[row][col]);

                vertexList[row].insert(col, vertex);
            }
        }
    }

    return vertexList;
}

void QKlipperPrintBedMesh::setAlgorithm(const QString &algorithm)
{
    if (m_algorithm == algorithm)
        return;
    m_algorithm = algorithm;
    emit algorithmChanged();
}

QVector2D QKlipperPrintBedMesh::probeCount() const
{
    return m_probeCount;
}

void QKlipperPrintBedMesh::setProbeCount(const QVector2D &probeCount)
{
    if (m_probeCount == probeCount)
        return;
    m_probeCount = probeCount;
    emit probeCountChanged();
}

quint32 QKlipperPrintBedMesh::reportedProbePoints() const
{
    return m_reportedProbePoints;
}

void QKlipperPrintBedMesh::setReportedProbePoints(quint32 reportedProbePoints)
{
    if (m_reportedProbePoints == reportedProbePoints)
        return;
    m_reportedProbePoints = reportedProbePoints;
    emit reportedProbePointsChanged();
}

QVector2D QKlipperPrintBedMesh::maximum() const
{
    return m_maximum;
}

void QKlipperPrintBedMesh::setMaximum(const QVector2D &maximum)
{
    if (m_maximum == maximum)
        return;
    m_maximum = maximum;
    emit maximumChanged();
}

QVector2D QKlipperPrintBedMesh::minimum() const
{
    return m_minimum;
}

void QKlipperPrintBedMesh::setMinimum(const QVector2D &minimum)
{
    if (m_minimum == minimum)
        return;
    m_minimum = minimum;
    emit minimumChanged();
}
