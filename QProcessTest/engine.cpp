#include "engine.h"

#include <QTimer>
#include <QDebug>
#include <iostream>

Engine::Engine(QString executable, QObject *parent)
    : QObject(parent)
    , m_executable(executable)
{
    m_macroBots << new MacroBot("Bot1", executable, this) << new MacroBot("Bot2", executable, this);
}

void Engine::run()
{
    startBots();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() { handleNextTick(); });
    timer->start(1000);
}

void Engine::startBots()
{
    for (auto it = m_macroBots.begin(); it != m_macroBots.end(); it++)
    {
        (*it)->startProcess();
    }
}

void Engine::handleNextTick()
{
    for (auto it = m_macroBots.begin(); it != m_macroBots.end(); it++)
    {
        auto macroBot = *it;
        if (macroBot->running())
        {
            macroBot->sendGameState("Ping?");
            macroBot->receiveCommands();
        }
    }
}
