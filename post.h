#ifndef POST_H
#define POST_H

#include <QDateTime>
#include "entity.h"

namespace Plurq {

enum Commenting {
    On = 0,
    Off = 1,
    FriendsOnly = 2
};

enum Reading {
    Read = 0,
    Unread = 1,
    Muted = 2
};

class Post : public Entity
{
    using Entity::Entity;

public:
    // Plurk data
    inline int id() const { return intValue(QLatin1String("plurk_id")); }
    inline int userId() const { return intValue(QLatin1String("user_id")); }
    inline int ownerId() const { return intValue(QLatin1String("owner_id")); }
    inline QString qualifier() const { return stringValue(QLatin1String("qualifier")); }
    inline QString content() const { return stringValue(QLatin1String("content")); }
    inline QString rawContent() const { return stringValue(QLatin1String("content_raw")); }
    inline QString language() const { return stringValue(QLatin1String("lang")); }
    inline QDateTime posted() const { return dateValue(QLatin1String("posted")); }

    // Privacy and visibility status
    inline Commenting commenting() const { return static_cast<Commenting>(intValue(QLatin1String("no_comments"))); }
    inline bool anonymous() const { return boolValue(QLatin1String("anonymous")); }
    inline bool porn() const { return boolValue(QLatin1String("porn")); }
    inline bool replurkable() const { return boolValue(QLatin1String("replurkable")); }
    inline int replurkerId() const { return intValue(QLatin1String("replurker_id")); }

    // Statistics
    inline int responses() const { return intValue(QLatin1String("response_count")); }
    inline int favorites() const { return intValue(QLatin1String("favorite_count")); }
    inline int replurks() const { return intValue(QLatin1String("replurkers_count")); }
    inline int coins() const { return intValue(QLatin1String("coins")); }

    // User-specific status
    inline Reading reading() const { return static_cast<Reading>(intValue(QLatin1String("is_unread"))); }
    inline bool responded() const { return boolValue(QLatin1String("responded")); }
    inline bool mentioned() const { return boolValue(QLatin1String("mentioned")); }
    inline bool favorited() const { return boolValue(QLatin1String("favorite")); }
    inline bool replurked() const { return boolValue(QLatin1String("replurked")); }
    inline bool coined() const { return boolValue(QLatin1String("has_gift")); }
    inline bool bookmarked() const { return boolValue(QLatin1String("bookmark")); }

    bool secret() const;
    QString translatedQualifier() const;
};

}

#endif // POST_H
