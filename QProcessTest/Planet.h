#ifndef PLANET_H
#define PLANET_H

#include "GameObject.h"

#include <QObject>

class Planet : public GameObject
{
    Q_OBJECT
public:
    Planet(QString name, int orbitDistance, int orbitRotation, double orbitSpeed, QObject *parent = nullptr);

signals:

public slots:

private:
    QString m_name;
    int m_orbitDistance;
    int m_orbitRotation;
    double m_orbitSpeed;
    int m_ownedBy;
};

#endif // PLANET_H
