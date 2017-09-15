#include "UniverseBuilder.h"

UniverseBuilder::UniverseBuilder()
{
    std::random_device rd;
    m_randomGenerator = std::mt19937(rd);
}

Universe *UniverseBuilder::buildUniverse()
{
    std::uniform_int_distribution<> disSolarSystem(4, 9);
    std::uniform_int_distribution<> disPlanets(5, 13);
    auto nSolarSystems = disSolarSystem(m_randomGenerator);

    std::vector<int> nPlanetsPerSolarSystem;
    nPlanetsPerSolarSystem.push_back(disPlanets(m_randomGenerator));


    QList<SolarSystem*> solarSystems;
    for (int i = 0; i < nSolarSystems; i++)
    {

    }

    auto universe = new Universe();

    return universe;
}

SolarSystem *UniverseBuilder::buildSolarSystem()
{
    std::uniform_int_distribution<> dis(5, 13);
    auto nPlanets = dis(m_randomGenerator);

    QList<Planet*> planets;
    for (int i = 0; i < nPlanets; i++)
    {

    }
}
