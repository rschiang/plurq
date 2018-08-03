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
public:
    Profile(QIODevice* stream);

    inline int id() const { return m_entity[QLatin1String("id")].toInt(); }
    inline QString nickName() const { return m_entity[QLatin1String("nick_name")].toString(); }
    inline QString displayName() const { return m_entity[QLatin1String("display_name")].toString(); }
    inline QString location() const { return m_entity[QLatin1String("location")].toString(); }
    inline QString fullName() const { return m_entity[QLatin1String("full_name")].toString(); }
    inline double karma() const { return m_entity[QLatin1String("karma")].toDouble(); }
    inline bool premium() const { return m_entity[QLatin1String("premium")].toBool(); }

    QUrl avatarUrl(Avatar size = Avatar::Medium) const;
    bool birthday() const;
};

}

#endif // PROFILE_H
