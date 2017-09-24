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
    if (m_process->state() == QProcess::Running)
        m_process->write(state.toStdString().c_str());
}

QStringList MacroBot::receiveCommands()
{
    unsigned long bytesAvailable = static_cast<unsigned long>(m_process->bytesAvailable());
    char* buf = new char[bytesAvailable];
    m_process->readLine(buf, static_cast<qint64>(bytesAvailable));
    QString commands(buf);
    delete[] buf;

    auto splitCommands = commands.split('\n');
    splitCommands.removeAll("");
    return splitCommands;
}

bool MacroBot::running()
{
    return m_process->state() == QProcess::Running;
}
