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

QKlipperPrintBedMesh::Limit QKlipperPrintBedMesh::minimum() const
{
    return m_minimum;
}

void QKlipperPrintBedMesh::setMinimum(const Limit &minimum)
{
    if (m_minimum.x == minimum.x &&
        m_minimum.y == minimum.y)
        return;

    m_minimum = minimum;
    emit minimumChanged();
}

QKlipperPrintBedMesh::Limit QKlipperPrintBedMesh::maximum() const
{
    return m_maximum;
}

void QKlipperPrintBedMesh::setMaximum(const Limit &maximum)
{
    if (m_maximum.x == maximum.x &&
        m_maximum.y == maximum.y)
        return;

    m_maximum = maximum;
    emit maximumChanged();
}

QKlipperPrintBedMesh::Limit QKlipperPrintBedMesh::probeCount() const
{
    return m_probeCount;
}

void QKlipperPrintBedMesh::setProbeCount(const Limit &probeCount)
{
    m_probeCount = probeCount;
    emit probeCountChanged();
}

QList<QList<qreal> > QKlipperPrintBedMesh::matrix() const
{
    return m_matrix;
}

void QKlipperPrintBedMesh::setMatrix(const QList<QList<qreal> > matrix)
{
    qDebug() << "setting probed";
    m_matrix = matrix;
    emit matrixChanged();
}

QList<QList<qreal> > QKlipperPrintBedMesh::probed() const
{
    return m_probed;
}

void QKlipperPrintBedMesh::setProbed(const QList<QList<qreal> > probed)
{
    qDebug() << "setting probed";
    m_probed = probed;
    emit probedChanged();
}

QString QKlipperPrintBedMesh::algorithm() const
{
    return m_algorithm;
}

void QKlipperPrintBedMesh::setAlgorithm(const QString &algorithm)
{
    if (m_algorithm == algorithm)
        return;
    m_algorithm = algorithm;
    emit algorithmChanged();
}
