#ifndef BUYCOMMAND_H
#define BUYCOMMAND_H

#include "CommandBase.h"

class BuyCommand : public CommandBase
{
public:
    explicit BuyCommand(QObject* parent = nullptr);
};

#endif // BUYCOMMAND_H
