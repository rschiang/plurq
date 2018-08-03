#include "profile.h"
#include <QJsonDocument>
#include <QDebug>
#include <QDateTime>

using namespace Plurq;

Profile::Profile(QIODevice* stream)
    : Entity::Entity(stream)
{}

QUrl Profile::avatarUrl(Avatar size) const
{
    bool hasProfileImage = (m_entity[QLatin1String("has_profile_image")].toInt() == 1);
    auto avatar = m_entity[QLatin1String("avatar")];

    if (!hasProfileImage) {
        switch (size) {
        case Avatar::Small:
            return QUrl(QStringLiteral("https://www.plurk.com/static/default_small.gif"));
        case Avatar::Medium:
            return QUrl(QStringLiteral("https://www.plurk.com/static/default_medium.gif"));
        case Avatar::Large:
            return QUrl(QStringLiteral("https://www.plurk.com/static/default_big.gif"));
        }
    } else {
        QString version = avatar.isNull() ? "" : QString::number(avatar.toInt());
        switch (size) {
        case Avatar::Small:
            return QUrl(QStringLiteral("https://avatars.plurk.com/%1-small%2.gif").arg(id()).arg(version));
        case Avatar::Medium:
            return QUrl(QStringLiteral("https://avatars.plurk.com/%1-medium%2.gif").arg(id()).arg(version));
        case Avatar::Large:
            return QUrl(QStringLiteral("https://avatars.plurk.com/%1-large%2.jpg").arg(id()).arg(version));
        }
    }
}

bool Profile::birthday() const
{
    if (m_entity[QLatin1String("bday_privacy")].toInt() != 0) {
        QString value = m_entity[QLatin1String("date_of_birth")].toString();
        QDate date = QDateTime::fromString(value, Qt::RFC2822Date).date();
        QDate today = QDate::currentDate();
        return (date.month() == today.month()) && (date.day() == today.day());
    } else {
        return false;
    }
}
