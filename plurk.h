#ifndef PLURK_H
#define PLURK_H

#include <QtCore>
#include <QtNetwork>
#include <QtNetworkAuth>

class PlurkPrivate;
class Plurk: public QOAuth1
{
    Q_OBJECT
    Q_PROPERTY(QString deviceId READ deviceId WRITE setDeviceId)

public:
    Plurk(QObject *parent = nullptr);
    Plurk(const QPair<QString, QString> &clientCredentials, QObject *parent = nullptr);

    QString deviceId();
    void setDeviceId(const QString &deviceId);

    static QUrl apiUrl(const QString &endpoint);

protected slots:
    void authorizeWithBrowser(QUrl url);

private:
    Q_DISABLE_COPY(Plurk)
    Q_DECLARE_PRIVATE(Plurk)
};

#endif // PLURK_H
