#include "MacroGame.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>
#include <iostream>

MacroGame::MacroGame(QString executable, Universe* universe, QObject *parent)
    : GameObject(parent)
    , m_executable(executable)
    , m_universe(universe)
    , m_tickTimer(new QTimer(this))
    , m_currentTick(1)
    , m_name("Match ###")
{
    m_universe->setParent(this);
    m_macroBots << new MacroBot("Bot1", executable, this) << new MacroBot("Bot2", executable, this);
    connect(m_tickTimer, &QTimer::timeout, this, [this]() { handleTick(); });
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

void MacroGame::handleTick()
{
    if (m_elapsedTimer.elapsed() > 600e3)
    {
        m_tickTimer->stop();
        killBots();
        killMicroGames();
        deleteLater();
        return;
    }

    m_universe->applyTick(1.0);

    communicateWithBots();
    m_currentTick++;
}

void MacroGame::communicateWithBots()
{
    QJsonDocument gameStateDoc(generateGameState());
    auto gameStateJson = gameStateDoc.toJson(QJsonDocument::Indented);
    // Write game state
    QFile file("macro_" + QString::number(m_currentTick) + ".json");
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << gameStateJson;
    }


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

QJsonObject MacroGame::generateGameState()
{
    QJsonObject gameState;
    gameState["id"] = m_id;
    gameState["name"] = m_name;
    gameState["tick"] = m_currentTick;
    QJsonArray players;
    gameState["players"] = players;

    QJsonArray fights;
    gameState["fights"] = fights;
    m_universe->writeState(gameState);


    return gameState;
}
