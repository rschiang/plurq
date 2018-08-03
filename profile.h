#ifndef PROFILE_H
#define PROFILE_H

#include <QJsonObject>
#include <QIODevice>

namespace Plurq {

class Profile
{
public:
    bool valid();
    QJsonObject& entity();

    static Profile fromStream(QIODevice* stream);

protected:
    Profile();
    Profile(QJsonObject);

    bool m_valid = false;
    QJsonObject m_entity;
};

}

#endif // PROFILE_H
