#ifndef PROFILE_H
#define PROFILE_H

#include "entity.h"

namespace Plurq {

class Profile : public Entity
{
public:
    Profile(QIODevice* stream);

    QJsonValue displayName() const;
};

}

#endif // PROFILE_H
