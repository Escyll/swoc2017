#include "SolarSystem.h"

SolarSystem::SolarSystem(QString name, QPoint coord, QList<Planet *> planets, QObject *parent)
    : GameObject(parent)
    , m_name(name)
    , m_coord(coord)
    , m_planets(planets)
{
}
