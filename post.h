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
public:
    Post(QIODevice* stream);

    inline int id() const { return intValue(QLatin1String("plurk_id")); }
    inline int ownerId() const { return intValue(QLatin1String("owner_id")); }
    inline int replurkerId() const { return intValue(QLatin1String("replurker_id")); }
    inline QString qualifier() const { return stringValue(QLatin1String("qualifier")); }
    inline QString content() const { return stringValue(QLatin1String("content")); }
    inline QString rawContent() const { return stringValue(QLatin1String("content_raw")); }
    inline Commenting commenting() const { return static_cast<Commenting>(intValue(QLatin1String("no_comments"))); }
    inline Reading reading() const { return static_cast<Reading>(intValue(QLatin1String("is_unread"))); }
    inline int responses() const { return intValue(QLatin1String("response_count")); }
    inline int favorites() const { return intValue(QLatin1String("favorite_count")); }
    inline int replurks() const { return intValue(QLatin1String("replurkers_count")); }
    inline int coins() const { return intValue(QLatin1String("coins")); }

    QDateTime posted() const;
};

}

#endif // POST_H
