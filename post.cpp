#include "post.h"

using namespace Plurq;

Post::Post(QIODevice* stream)
    : Entity::Entity(stream)
{}

QDateTime Post::posted() const
{
    QString value = stringValue(QLatin1String("posted"));
    return QDateTime::fromString(value, Qt::RFC2822Date);
}
