#include "MacroBot.h"

#include <iostream>

MacroBot::MacroBot(QString executablePath, QObject *parent)
    : QObject(parent)
    , m_executablePath(executablePath)
{
}

void MacroBot::startProcess()
{
    m_process = new QProcess(this);
    m_process->start(m_executablePath);
}

void MacroBot::stopProcess()
{
    m_process->kill();
    m_process->waitForFinished(500);
}

void MacroBot::sendGameState(QString state)
{
    if (!state.contains("\n"))
        state = state + "\n";
    m_process->write(state.toStdString().c_str());
}

QStringList MacroBot::receiveCommands()
{
    char buf[1000000];
    m_process->readLine(buf, sizeof(buf));
    QString commands(buf);

    auto splitCommands = commands.split('\n');
    splitCommands.removeLast();
    return splitCommands;
}

bool MacroBot::running()
{
    return m_process->state() == QProcess::Running;
}
