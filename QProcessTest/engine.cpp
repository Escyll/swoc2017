#include "engine.h"

#include <QTimer>
#include <QDebug>
#include <iostream>

Engine::Engine(QObject *parent) : QObject(parent)
{

}

void Engine::run()
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() { handleNextTick(); });

    m_process = new QProcess(this);
    m_process->start("D:/Projects/build-QProcessTestSubProcess-Desktop_Qt_5_9_0_MSVC2015_64bit-Debug/debug/QProcessTestSubProcess.exe");

    QObject::connect(m_process, &QProcess::stateChanged, this, [this](QProcess::ProcessState state)
    {
        switch (state) {
        case QProcess::NotRunning:
            std::cout << "Not running";
            break;
        case QProcess::Running:
            std::cout << "Running";
            break;
        case QProcess::Starting:
            std::cout << "Starting";
            break;
        default:
            break;
        }
    });

    QObject::connect(m_process, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error)
    {
        std::cout << error;
    });

    timer->start(1000);
}

void Engine::handleNextTick()
{
    char buf[1024];
    qint64 lineLength =  m_process->readLine(buf, sizeof(buf));
    if (lineLength > 0) {
        std::cout << buf;
    }
    std::cout << "Ping?\n" << std::endl;
    m_process->write("Ping?\n");
}
