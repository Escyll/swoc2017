#include <QCoreApplication>
#include <QTimer>
#include <iostream>

#include <engine.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if (argc < 2)
    {
        std::cout << "Need path to executable as argument" << std::endl;
        return -1;
    }

    Engine engine(argv[1], &a);
    QObject::connect(&engine, &Engine::finished, &a, [&a]() { a.quit(); });
    QObject::connect(&engine, &Engine::errorOccured, &a, [&a]() { a.quit(); });

    QTimer::singleShot(0, &engine, SLOT(run()));

    return a.exec();
}
