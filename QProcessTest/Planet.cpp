#include "Planet.h"

Planet::Planet(QString name, int orbitDistance, int orbitRotation, double orbitSpeed, QObject *parent)
    : GameObject(parent)
    , m_name(name)
    , m_orbitDistance(orbitDistance)
    , m_orbitRotation(orbitRotation)
    , m_orbitSpeed(orbitSpeed)
    , m_ownedBy(-1)
{
}
