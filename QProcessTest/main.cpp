#include <QCoreApplication>
#include <QTimer>

#include <engine.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Engine engine(&a);
    QObject::connect(&engine, &Engine::finished, &a, [&a]() { a.quit(); });
    QObject::connect(&engine, &Engine::errorOccured, &a, [&a]() { a.quit(); });

    QTimer::singleShot(0, &engine, SLOT(run()));

    return a.exec();
}
