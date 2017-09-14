#ifndef ENGINE_H
#define ENGINE_H

#include "MacroBot.h"

#include <QObject>
#include <QProcess>

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QString executable, QObject *parent = 0);
    void handleNextTick();

signals:
    void finished();
    void errorOccured();

public slots:
    void run();

private:
    QProcess* m_process;
    QString m_executable;
    QList<MacroBot*> m_macroBots;

    void startBots();
};

#endif // ENGINE_H
