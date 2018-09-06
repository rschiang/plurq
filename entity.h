#ifndef ENTITY_H
#define ENTITY_H

#include <QDateTime>
#include <QIODevice>
#include <QJsonArray>
#include <QJsonObject>

namespace Plurq {

class Entity
{
    friend class Array;
public:
    Entity(const QJsonObject &entity);
    explicit Entity(QIODevice *stream);
    explicit Entity(const QByteArray &json);

    inline bool valid() const { return m_valid; }
    inline QJsonObject& entity() { return m_entity; }
    inline QJsonValue operator[](QLatin1String key) const { return m_entity[key]; }

    inline int intValue(QLatin1String key) const { return m_entity[key].toInt(); }
    inline bool boolValue(QLatin1String key) const { return m_entity[key].toBool(); }
    inline double doubleValue(QLatin1String key) const { return m_entity[key].toDouble(); }
    inline QString stringValue(QLatin1String key) const { return m_entity[key].toString(); }
    inline QJsonArray arrayValue(QLatin1String key) const { return m_entity[key].toArray(); }
    inline QJsonObject objectValue(QLatin1String key) const { return m_entity[key].toObject(); }

    QDateTime dateValue(QLatin1String key) const;

protected:
    bool m_valid = false;
    QJsonObject m_entity;
};

}

#endif // ENTITY_H
