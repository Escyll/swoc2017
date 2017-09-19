#ifndef MOVETOCOORDCOMMAND_H
#define MOVETOCOORDCOMMAND_H

#include "CommandBase.h"

class MoveToCoordCommand : public CommandBase
{
public:
    explicit MoveToCoordCommand(QObject* parent = nullptr);
};

#endif // MOVETOCOORDCOMMAND_H
