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

    using QOAuth1::get;
    inline QNetworkReply* get(const QString &apiPath, const QVariantMap &parameters = QVariantMap()) {
        return get(buildUrl(apiPath), parameters);
    }

    using QOAuth1::post;
    inline QNetworkReply* post(const QString &apiPath, const QVariantMap &parameters = QVariantMap()) {
        return post(buildUrl(apiPath), parameters);
    }

    void restoreTokenCredentials(const QString &token, const QString &tokenSecret);

    static QUrl buildUrl(const QString &apiPath);

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
