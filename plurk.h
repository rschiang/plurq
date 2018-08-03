#ifndef PLURK_H
#define PLURK_H

#include <QtCore>
#include <QtNetwork>
#include <QtNetworkAuth>

namespace Plurq {

class PlurkPrivate;
class Plurk: public QOAuth1
{
    Q_OBJECT
    Q_PROPERTY(QString deviceId READ deviceId WRITE setDeviceId)

public:
    Plurk(QObject *parent = nullptr);
    Plurk(const QString &clientIdentifier, const QString &clientSharedSecret, QObject *parent = nullptr);

    QString deviceId() const;
    void setDeviceId(const QString &deviceId);

    void restoreTokenCredentials(const QString &token, const QString &tokenSecret);

    static QUrl apiUrl(const QString &endpoint);

public slots:
    void grant();

protected slots:
    void authorizeWithBrowser(QUrl url);

private:
    Q_DISABLE_COPY(Plurk)
    QString m_deviceId;
    QOAuthHttpServerReplyHandler *m_replyHandler = nullptr;
};

}

#endif // PLURK_H
