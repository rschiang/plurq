#include "plurk.h"
#include "plurk_p.h"
#include <QDesktopServices>
#include <QHostAddress>
#include <QSysInfo>
#include <QUuid>

Plurk::Plurk(QObject *parent) :
    Plurk(QString(), QString(), parent)
{}

Plurk::Plurk(const QString &clientIdentifier, const QString &clientSharedSecret, QObject *parent) :
    QOAuth1(clientIdentifier, clientSharedSecret, nullptr, parent)
{
    // Initialize Plurk service information
    setSignatureMethod(SignatureMethod::Hmac_Sha1);
    setContentType(ContentType::WwwFormUrlEncoded);
    setTemporaryCredentialsUrl(QUrl("https://www.plurk.com/OAuth/request_token"));
    setAuthorizationUrl(QUrl("https://www.plurk.com/OAuth/authorize"));
    setTokenCredentialsUrl(QUrl("https://www.plurk.com/OAuth/access_token"));

    // Set up signals
    connect(this, &QAbstractOAuth::authorizeWithBrowser, this, &Plurk::authorizeWithBrowser);
}

QString Plurk::deviceId() const
{
    Q_D(const Plurk);
    return d->deviceId;
}

void Plurk::setDeviceId(const QString &deviceId)
{
    Q_D(Plurk);
    d->deviceId = deviceId;
}

void Plurk::restoreTokenCredentials(const QString &token, const QString &tokenSecret)
{
    setTokenCredentials(token, tokenSecret);
    if (!(token.isEmpty() || tokenSecret.isEmpty()))
        setStatus(Status::Granted);
}

QUrl Plurk::apiUrl(const QString &endpoint)
{
    static const QUrl baseUrl("https://www.plurk.com/APP/");
    return baseUrl.resolved(QUrl(endpoint));
}

void Plurk::grant()
{
    Q_D(Plurk);

    // Setup local callback listener for OAuth verifier
    if (!d->replyHandler) {
        QHostAddress host(QHostAddress::LocalHost);
        auto replyHandler = new QOAuthHttpServerReplyHandler(host, 0, this);
        replyHandler->setCallbackPath("callback");
        replyHandler->setCallbackText(tr(PLURK_CALLBACK_RECEIVED_TEXT) + "<script>window.location='https://www.plurk.com';</script>");
        d->replyHandler = replyHandler;
        setReplyHandler(replyHandler);
    }

    QOAuth1::grant();
}

void Plurk::authorizeWithBrowser(QUrl url) {
    Q_D(Plurk);

    // Generate device ID if there were none
    if (!d->deviceId.isEmpty())
        d->deviceId = QUuid::createUuid().toRfc4122().toHex();

    QUrlQuery query(url);
    query.addQueryItem("model", QSysInfo::prettyProductName());
    query.addQueryItem("deviceid", d->deviceId);

    url.setQuery(query);
    QDesktopServices::openUrl(url);
}
