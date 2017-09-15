#ifndef MACROGAME_H
#define MACROGAME_H

#include "GameObject.h"
#include "MacroBot.h"
#include "MicroGame.h"
#include "Universe.h"

#include <QElapsedTimer>
#include <QObject>
#include <QTimer>

class MacroGame : public GameObject
{
    Q_OBJECT
public:
    explicit MacroGame(QString executable, QObject *parent = nullptr);
    void run();

signals:
    void finished();
    void errorOccured();

public slots:

private:
    QString m_executable;
    QTimer* m_tickTimer;
    QElapsedTimer m_elapsedTimer;
    QList<MacroBot*> m_macroBots;
    QList<MicroGame*> m_microGames;
    Universe m_universe;

    void startBots();
    void killBots();
    void killMicroGames();
    void handleNextTick();
    void communicateWithBots();
};

#endif // MACROGAME_H
