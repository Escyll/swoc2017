#ifndef ENGINE_H
#define ENGINE_H

#include "MacroBot.h"
#include "MicroGame.h"

#include <QObject>
#include <QElapsedTimer>
#include <QTimer>

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QString executable, QObject *parent = 0);

signals:
    void finished();
    void errorOccured();

public slots:
    void run();

private:
    QString m_executable;
    QTimer* m_tickTimer;
    QElapsedTimer m_elapsedTimer;
    QList<MacroBot*> m_macroBots;
    QList<MicroGame*> m_microGames;

    void startBots();
    void killBots();
    void killMicroGames();
    void handleNextTick();
    void communicateWithBots();
};

#endif // ENGINE_H
