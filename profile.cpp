#include "profile.h"
#include <QJsonDocument>
#include <QDebug>

using namespace Plurq;

Profile::Profile()
{}

Profile::Profile(QJsonObject entity)
{
    m_entity = entity;
    m_valid = true;
}

Profile Profile::fromStream(QIODevice *stream)
{
    QJsonParseError parseError;
    const QByteArray data = stream->readAll();
    const QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error) {
        qDebug() << "Error parsing Profile JSON" << parseError.errorString();
        return Profile();
    } else {
        const QJsonObject entity = doc.object();
        return Profile(entity);
    }
}

bool Profile::valid()
{
    return m_valid;
}

QJsonObject& Profile::entity()
{
    return m_entity;
}


