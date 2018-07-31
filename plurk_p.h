#ifndef PLURK_P_H
#define PLURK_P_H

#include <QtCore>
#include <QtNetworkAuth>

class PlurkPrivate
{
public:
    QString deviceId;
    QOAuthHttpServerReplyHandler *replyHandler = nullptr;
};

#define PLURK_CALLBACK_RECEIVED_TEXT "Plurk authorization completed! Feel free to close this page."

#endif // PLURK_P_H
