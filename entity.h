#ifndef ENTITY_H
#define ENTITY_H

#include <QJsonObject>
#include <QIODevice>

namespace Plurq {

class Entity
{
public:
    Entity(QIODevice* stream);

    bool valid() const;
    QJsonObject& entity();
    QJsonValue operator[](QLatin1String key) const;

protected:
    Entity();
    Entity(QJsonObject&);

    bool m_valid = false;
    QJsonObject m_entity;
};

}

#endif // ENTITY_H
