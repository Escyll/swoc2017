#include "Universe.h"

#include <QJsonArray>

Universe::Universe(QList<SolarSystem *> solarSystems, QObject *parent)
    : GameObject(parent)
    , m_solarSystems(solarSystems)
{
    for (auto solarSystemIt = m_solarSystems.begin(); solarSystemIt != m_solarSystems.end(); solarSystemIt++)
    {
        (*solarSystemIt)->setParent(this);
    }
}

void Universe::writeState(QJsonObject& gameState)
{
    QJsonArray solarSystemArray;
    foreach (const SolarSystem* solarSystem, m_solarSystems) {
        QJsonObject solarSystemObject;
        solarSystem->writeState(solarSystemObject);
        solarSystemArray.append(solarSystemObject);
    }
    gameState["solarSystems"] = solarSystemArray;
}

void Universe::applyTick(double durationInSeconds)
{
    foreach (SolarSystem* solarSystem, m_solarSystems) {
        solarSystem->applyTick(durationInSeconds);
    }
}
