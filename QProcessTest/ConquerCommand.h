#ifndef CONQUERCOMMAND_H
#define CONQUERCOMMAND_H

#include "CommandBase.h"

class ConquerCommand : public CommandBase
{
public:
    explicit ConquerCommand(QObject* parent = nullptr);
};

#endif // CONQUERCOMMAND_H
