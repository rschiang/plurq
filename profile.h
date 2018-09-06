#ifndef PROFILE_H
#define PROFILE_H

#include <QUrl>
#include "entity.h"

namespace Plurq {

enum Avatar
{
    Small,
    Medium,
    Large
};

class Profile : public Entity
{
    using Entity::Entity;

public:
    inline int id() const { return intValue(QLatin1String("id")); }
    inline QString nickName() const { return stringValue(QLatin1String("nick_name")); }
    inline QString displayName() const { return stringValue(QLatin1String("display_name")); }
    inline QString location() const { return stringValue(QLatin1String("location")); }
    inline QString fullName() const { return stringValue(QLatin1String("full_name")); }
    inline double karma() const { return doubleValue(QLatin1String("karma")); }
    inline bool premium() const { return boolValue(QLatin1String("premium")); }

    QUrl avatarUrl(Avatar size = Avatar::Medium) const;
    bool birthday() const;
};

}

#endif // PROFILE_H
