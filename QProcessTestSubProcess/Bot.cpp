#include "Bot.h"

#include <iostream>

Bot::Bot(QObject *parent) : QObject(parent)
  , in(stdin)
{
}

void Bot::run()
{
    forever {
        QString line = in.readLine();
        if (line == "Ping?")
            std::cout << "Pong!" << std::endl;
        else if (line == "quit")
            break;
        else
            std::cout << "Ik snap het niet :(." << std::endl;

    }
}
