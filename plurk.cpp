#include "plurk.h"
#include "plurk_p.h"
#include <QDesktopServices>
#include <QHostAddress>
#include <QSysInfo>
#include <QUuid>

Plurk::Plurk(QObject *parent) :
    Plurk(qMakePair(QString(), QString()), parent)
{}

Plurk::Plurk(const QPair<QString, QString> &clientCredentials, QObject *parent) :
    QOAuth1(clientCredentials.first, clientCredentials.second, nullptr, parent)
{
    Q_D(Plurk);

    // Initialize Plurk service information
    setSignatureMethod(SignatureMethod::Hmac_Sha1);
    setContentType(ContentType::WwwFormUrlEncoded);
    setTemporaryCredentialsUrl(QUrl("https://www.plurk.com/OAuth/request_token"));
    setAuthorizationUrl(QUrl("https://www.plurk.com/OAuth/authorize"));
    setTokenCredentialsUrl(QUrl("https://www.plurk.com/OAuth/access_token"));

    // Setup local callback listener for OAuth verifier
    QHostAddress host(QHostAddress::LocalHost);
    auto replyHandler = new QOAuthHttpServerReplyHandler(host, 0, this);
    replyHandler->setCallbackPath("callback");
    replyHandler->setCallbackText(tr(PLURK_CALLBACK_RECEIVED_TEXT) + "<script>window.location='https://www.plurk.com';</script>");
    d->replyHandler = replyHandler;
    setReplyHandler(replyHandler);

    // Set up signals
    connect(this, &QAbstractOAuth::authorizeWithBrowser, this, &Plurk::authorizeWithBrowser);
}

QUrl Plurk::apiUrl(const QString &endpoint)
{
    static const QUrl baseUrl("https://www.plurk.com/APP/");
    return baseUrl.resolved(QUrl(endpoint));
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
