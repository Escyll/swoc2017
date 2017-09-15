#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>

class GameObject : public QObject
{
    Q_OBJECT
public:
    explicit GameObject(QObject *parent = nullptr);

signals:

public slots:
private:
    int m_id;
};

#endif // GAMEOBJECT_H
