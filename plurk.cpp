#include "plurk.h"
#include <QDesktopServices>
#include <QHostAddress>
#include <QSysInfo>
#include <QUuid>

#define PLURK_CALLBACK_RECEIVED_TEXT "Plurk authorization completed! Feel free to close this page."

using namespace Plurq;

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
    return m_deviceId;
}

void Plurk::setDeviceId(const QString &deviceId)
{
    m_deviceId = deviceId;
}

void Plurk::restoreTokenCredentials(const QString &token, const QString &tokenSecret)
{
    setTokenCredentials(token, tokenSecret);
    if (!(token.isEmpty() || tokenSecret.isEmpty()))
        setStatus(Status::Granted);
}

QUrl Plurk::buildUrl(const QString &apiPath)
{
    static const QUrl baseUrl("https://www.plurk.com/APP/");
    return baseUrl.resolved(QUrl(apiPath));
}

void Plurk::grant()
{
    // Setup local callback listener for OAuth verifier
    if (!m_replyHandler) {
        QHostAddress host(QHostAddress::LocalHost);
        auto replyHandler = new QOAuthHttpServerReplyHandler(host, 0, this);
        replyHandler->setCallbackPath("callback");
        replyHandler->setCallbackText(tr(PLURK_CALLBACK_RECEIVED_TEXT) + "<script>window.location='https://www.plurk.com';</script>");
        m_replyHandler = replyHandler;
        setReplyHandler(replyHandler);
    }

    QOAuth1::grant();
}

void Plurk::authorizeWithBrowser(QUrl url) {
    // Generate device ID if there were none
    if (m_deviceId.isEmpty())
        m_deviceId = QUuid::createUuid().toRfc4122().toHex();

    QUrlQuery query(url);
    query.addQueryItem("model", QSysInfo::prettyProductName());
    query.addQueryItem("deviceid", m_deviceId);

    url.setQuery(query);
    QDesktopServices::openUrl(url);
}
