#ifndef UNIVERSEBUILDER_H
#define UNIVERSEBUILDER_H

#include "Universe.h"
#include <random>

class UniverseBuilder
{
public:
    Universe* buildUniverse();

signals:

public slots:

private:
    std::mt19937 m_randomGenerator;
};

#endif // UNIVERSEBUILDER_H
