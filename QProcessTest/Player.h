#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Ufo.h"

#include <QObject>

class Player : public GameObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

signals:

public slots:

private:
    int m_credits;
    QList<Ufo*> m_ufos;
};

#endif // PLAYER_H
