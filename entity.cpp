#include "entity.h"
#include <QJsonDocument>
#include <QDebug>

using namespace Plurq;

Entity::Entity()
{}

Entity::Entity(QJsonObject &entity)
{
    m_entity = entity;
    m_valid = true;
}

Entity::Entity(QIODevice *stream)
{
    QJsonParseError parseError;
    const QByteArray data = stream->readAll();
    const QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error) {
        qDebug() << "Error parsing Profile JSON" << parseError.errorString();
    } else {
        m_entity = doc.object();
        m_valid = true;
    }
}

bool Entity::valid() const
{
    return m_valid;
}

QJsonObject& Entity::entity()
{
    return m_entity;
}

QJsonValue Entity::operator[](QLatin1String key) const
{
    return m_entity[key];
}
