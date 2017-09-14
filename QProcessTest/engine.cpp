#include "engine.h"

#include <QTimer>
#include <QDebug>
#include <iostream>

Engine::Engine(QString executable, QObject *parent)
    : QObject(parent)
    , m_executable(executable)
    , m_tickTimer(new QTimer(this))
{
    m_macroBots << new MacroBot("Bot1", executable, this) << new MacroBot("Bot2", executable, this);
    connect(m_tickTimer, &QTimer::timeout, this, [this]() { handleNextTick(); });
}

void Engine::run()
{
    startBots();
    m_elapsedTimer.start();
    m_tickTimer->start(1000);
}

void Engine::startBots()
{
    for (auto it = m_macroBots.begin(); it != m_macroBots.end(); it++)
    {
        auto macroBot = *it;
        macroBot->startProcess();
    }
}

void Engine::killBots()
{
    for (auto it = m_macroBots.begin(); it != m_macroBots.end(); it++)
    {
        auto macroBot = *it;
        macroBot->stopProcess();
    }
}

void Engine::killMicroGames()
{
    for (auto it = m_microGames.begin(); it != m_microGames.end(); it++)
    {
        auto microGame = *it;
        microGame->stopProcess();
    }
}

void Engine::handleNextTick()
{
    if (m_elapsedTimer.elapsed() > 1e4)
    {
        std::cout << "\nShutting processes down..." << std::endl;
        m_tickTimer->stop();
        killBots();
        killMicroGames();
        deleteLater();
        std::cout << "\nBye!" << std::endl;
        return;
    }
    communicateWithBots();
}

void Engine::communicateWithBots()
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
