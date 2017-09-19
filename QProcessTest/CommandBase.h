#ifndef COMMANDBASE_H
#define COMMANDBASE_H

#include <QObject>

class CommandBase : public QObject
{
    Q_OBJECT
public:
    explicit CommandBase(QObject *parent = nullptr);

signals:

public slots:
};

#endif // COMMANDBASE_H