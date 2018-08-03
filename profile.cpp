#include "profile.h"
#include <QJsonDocument>
#include <QDebug>

using namespace Plurq;

Profile::Profile(QIODevice* stream)
    : Entity::Entity(stream)
{}

QJsonValue Profile::displayName() const
{
    return m_entity.value("display_name");
}
