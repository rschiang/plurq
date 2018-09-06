#ifndef ENTITY_H
#define ENTITY_H

#include <QJsonArray>
#include <QJsonObject>
#include <QIODevice>

namespace Plurq {

class Entity
{
public:
    Entity(QIODevice* stream);

    bool valid() const;
    QJsonObject& entity();

    inline QJsonValue operator[](QLatin1String key) const { return m_entity[key]; }
    template<typename T> inline T operator[](QLatin1String key) const { return T(m_entity[key].toObject()); }

    inline int intValue(QLatin1String key) const { return m_entity[key].toInt(); }
    inline bool boolValue(QLatin1String key) const { return m_entity[key].toBool(); }
    inline double doubleValue(QLatin1String key) const { return m_entity[key].toDouble(); }
    inline QString stringValue(QLatin1String key) const { return m_entity[key].toString(); }
    inline QJsonArray arrayValue(QLatin1String key) const { return m_entity[key].toArray(); }
    inline QJsonObject objectValue(QLatin1String key) const { return m_entity[key].toObject(); }

protected:
    Entity();
    Entity(QJsonObject&);

    bool m_valid = false;
    QJsonObject m_entity;
};

}

#endif // ENTITY_H
