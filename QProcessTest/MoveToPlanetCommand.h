#ifndef MOVETOPLANETCOMMAND_H
#define MOVETOPLANETCOMMAND_H

#include "CommandBase.h"

class MoveToPlanetCommand : public CommandBase
{
public:
    explicit MoveToPlanetCommand(QObject* parent);
};

#endif // MOVETOPLANETCOMMAND_H
