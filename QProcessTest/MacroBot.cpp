#include "MacroBot.h"

#include <iostream>

MacroBot::MacroBot(QString name, QString executablePath, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_executablePath(executablePath)
{
}

void MacroBot::startProcess()
{
    m_process = new QProcess(this);
    m_process->start(m_executablePath);
}

void MacroBot::sendGameState(QString state)
{
    std::cout <<  "Sending to bot: "<< m_name.toStdString() << " \"" << state.toStdString() << "\"" << std::endl;
    if (!state.contains("\n"))
        state = state + "\n";
    m_process->write(state.toStdString().c_str());
}

void MacroBot::receiveCommands()
{
    char buf[1024];
    qint64 lineLength =  m_process->readLine(buf, sizeof(buf));
    if (lineLength > 0) {
        std::cout <<  "Received from bot: "<< m_name.toStdString() << " \"" << buf << "\"" << std::endl;
    }
}

bool MacroBot::running()
{
    return m_process->state() == QProcess::Running;
}
