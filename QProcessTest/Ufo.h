#ifndef UFO_H
#define UFO_H

#include "GameObject.h"

#include <QObject>

class Ufo : public GameObject
{
    Q_OBJECT
public:
    explicit Ufo(QObject *parent = nullptr);

signals:

public slots:

private:
};

#endif // UFO_H
