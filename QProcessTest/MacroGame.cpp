#include "MacroGame.h"
#include <iostream>

MacroGame::MacroGame(QString executable, Universe* universe, QObject *parent)
    : GameObject(parent)
    , m_executable(executable)
    , m_universe(universe)
    , m_tickTimer(new QTimer(this))
{
    m_universe->setParent(this);
    m_macroBots << new MacroBot("Bot1", executable, this) << new MacroBot("Bot2", executable, this);
    connect(m_tickTimer, &QTimer::timeout, this, [this]() { handleNextTick(); });
}

void MacroGame::run()
{
    startBots();
    m_elapsedTimer.start();
    m_tickTimer->start(1000);
}

void MacroGame::startBots()
{
    for (auto it = m_macroBots.begin(); it != m_macroBots.end(); it++)
    {
        auto macroBot = *it;
        macroBot->startProcess();
    }
}

void MacroGame::killBots()
{
    for (auto it = m_macroBots.begin(); it != m_macroBots.end(); it++)
    {
        auto macroBot = *it;
        macroBot->stopProcess();
    }
}

void MacroGame::killMicroGames()
{
    for (auto it = m_microGames.begin(); it != m_microGames.end(); it++)
    {
        auto microGame = *it;
        microGame->stopProcess();
    }
}

void MacroGame::handleNextTick()
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

void MacroGame::communicateWithBots()
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
