#include "entity.h"
#include <QJsonDocument>
#include <QDebug>

using namespace Plurq;

Entity::Entity(const QJsonObject &entity)
    : m_valid(true), m_entity(entity)
{}

Entity::Entity(QIODevice *stream)
    : Entity(stream->readAll())
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

QDateTime Entity::dateValue(QLatin1String key) const
{
     return QDateTime::fromString(m_entity[key].toString(), Qt::RFC2822Date);
}
