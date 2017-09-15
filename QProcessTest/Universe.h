#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "Fight.h"
#include "Player.h"
#include "SolarSystem.h"

#include <QObject>

class Universe : public GameObject
{
    Q_OBJECT
public:
    explicit Universe(QList<SolarSystem*> solarSystems, QObject *parent = nullptr);

signals:

public slots:

private:
    QList<SolarSystem*> m_solarSystems;
    QList<Player*> m_players;
    QList<Fight*> m_fights;
};

#endif // UNIVERSE_H
