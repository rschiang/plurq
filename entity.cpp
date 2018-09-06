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
    : Entity::Entity(stream->readAll())
{}

Entity::Entity(const QByteArray &json)
{
    QJsonParseError parseError;
    const QJsonDocument doc = QJsonDocument::fromJson(json, &parseError);
    if (parseError.error) {
        qDebug() << "Error parsing JSON entity" << parseError.errorString();
        qDebug() << QString::fromUtf8(json.data());
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
