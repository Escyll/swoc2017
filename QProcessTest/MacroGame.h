#ifndef MACROGAME_H
#define MACROGAME_H

#include "GameObject.h"
#include "MacroBot.h"
#include "MicroGame.h"
#include "Universe.h"

#include <QElapsedTimer>
#include <QMap>
#include <QObject>
#include <QTimer>

class MacroGame : public GameObject
{
    Q_OBJECT
public:
    MacroGame(QString executable, Universe *universe, QObject *parent = nullptr);
    void run();

signals:
    void finished();
    void errorOccured();

public slots:

private:
    QString m_executable;
    Universe* m_universe;

    QTimer* m_tickTimer;
    QElapsedTimer m_elapsedTimer;
    QList<MacroBot*> m_macroBots;
    QList<MicroGame*> m_microGames;
    int m_currentTick;
    double m_tickDurationInSeconds;
    QMap<Player*, MacroBot*> m_playerBotMap;
    QMap<MacroBot*, Player*> m_botPlayerMap;
    QString m_name;

    void startBots();
    void killBots();
    void killMicroGames();
    void handleTick();
    void communicateWithBots();
    QJsonObject generateGameState();
};

#endif // MACROGAME_H
