#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QProcess>

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = 0);
    void handleNextTick();

signals:
    void finished();
    void errorOccured();

public slots:
    void run();

private:
    QProcess* m_process;
};

#endif // ENGINE_H
