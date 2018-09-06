#include "profile.h"
#include <QJsonDocument>
#include <QDebug>
#include <QDateTime>

using namespace Plurq;

QUrl Profile::avatarUrl(Avatar size) const
{
    bool hasProfileImage = (intValue(QLatin1String("has_profile_image")) == 1);
    auto avatar = (*this)[QLatin1String("avatar")];

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
    if (intValue(QLatin1String("bday_privacy")) != 0) {
        QDate date = dateValue(QLatin1String("date_of_birth")).date();
        QDate today = QDate::currentDate();
        return (date.month() == today.month()) && (date.day() == today.day());
    } else {
        return false;
    }
}
