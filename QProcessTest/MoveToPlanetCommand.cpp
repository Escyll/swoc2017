#include "MoveToPlanetCommand.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>

MoveToPlanetCommand::MoveToPlanetCommand(QObject* parent)
    : CommandBase(parent)
{

}

void MoveToPlanetCommand::readCommand(const QJsonObject jsonObject)
{
    m_planetId = jsonObject["planetId"].toInt(-1);
    QJsonArray ufoArray = jsonObject["ufo"].toArray();

    for (int ufoIndex = 0; ufoIndex < ufoArray.size(); ufoIndex++)
    {
        m_ufos << ufoArray[ufoIndex].toInt(-1);
    }
}

void MoveToPlanetCommand::printCommand()
{
    std::cout << "planet: " << m_planetId << "\nufos: " << std::endl;
    foreach (int ufo, m_ufos)
    {
        std::cout << ufo << " ";
    }
    std::cout << std::endl;

}
