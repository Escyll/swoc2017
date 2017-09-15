#include "Universe.h"

Universe::Universe(QList<SolarSystem *> solarSystems, QObject *parent)
    : GameObject(parent)
    , m_solarSystems(solarSystems)
{
}
