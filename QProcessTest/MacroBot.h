#ifndef MACROBOT_H
#define MACROBOT_H

#include <QObject>
#include <QProcess>

class MacroBot : public QObject
{
    Q_OBJECT
public:
    explicit MacroBot(QString name, QString executablePath, QObject *parent = nullptr);
    void startProcess();
    void sendGameState(QString state);
    void receiveCommands();
    bool running();

signals:

public slots:

private:
    QString m_name;
    QString m_executablePath;
    QProcess* m_process;
};

#endif // MACROBOT_H
