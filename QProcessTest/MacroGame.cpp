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
    , m_tickDurationInSeconds(1.0)
    , m_name("Match ###")
{
    m_universe->setParent(this);

    auto player1 = new Player("Bot1", this);
    player1->giveUfo(new Ufo());
    player1->giveUfo(new Ufo());
    player1->giveUfo(new Ufo());
    auto bot1 = new MacroBot(executable, this);
    auto player2 = new Player("Bot2", this);
    player2->giveUfo(new Ufo());
    player2->giveUfo(new Ufo());
    player2->giveUfo(new Ufo());
    auto bot2 = new MacroBot(executable, this);

    m_universe->addPlayer(player1);
    m_universe->addPlayer(player2);
    m_macroBots << bot1 << bot2;

    m_playerBotMap[player1] = bot1;
    m_playerBotMap[player2] = bot2;
    m_botPlayerMap[bot1] = player1;
    m_botPlayerMap[bot2] = player2;

    connect(m_tickTimer, &QTimer::timeout, this, [this]() { handleTick(); });
}

void MacroGame::run()
{
    startBots();
    m_elapsedTimer.start();
    m_tickTimer->start(m_tickDurationInSeconds * 1000);
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

    m_universe->applyTick(m_tickDurationInSeconds);

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

    auto players = m_universe->getPlayers();
    foreach (Player* player, players)
    {
        auto macroBot = m_playerBotMap[player];
        if (macroBot->running())
        {
            macroBot->sendGameState(gameStateDoc.toJson(QJsonDocument::Compact));
            QStringList commands = macroBot->receiveCommands();
            foreach (QString command, commands)
            {
                // Handle command
                std::cout << player->getName().toStdString() << ": " << command.toStdString() << std::endl;
            }
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
