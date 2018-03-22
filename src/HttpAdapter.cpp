#include <QUrl>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "HttpAdapter.h"

HttpAdapter::HttpAdapter(QObject *parent) :
    QObject(parent)
{
    m_networkAccessManager = new QNetworkAccessManager(this);
}

// Sends a HTTP GET request.
void HttpAdapter::httpGet(const QString &url)
{
    QNetworkReply* reply = m_networkAccessManager->get(QNetworkRequest(QUrl(url)));
    connect(reply, &QNetworkReply::finished, [reply, this]()
    {
        emit httpGetFinished(QJsonDocument::fromJson(reply->readAll()));
        reply->deleteLater();
    });
}

// Sends a HTTP PUT request.
void HttpAdapter::httpPut(const QString& url, const QByteArray& body)
{
    QNetworkReply* reply = m_networkAccessManager->put(QNetworkRequest(QUrl(url)), body);
    connect(reply, &QNetworkReply::finished, [reply, this]()
    {
        emit httpPutFinished(QJsonDocument::fromJson(reply->readAll()));
        reply->deleteLater();
    });
}

// Sends a HTTP POST request.
void HttpAdapter::httpPost(const QString& url, const QByteArray& body)
{
    QNetworkReply* reply = m_networkAccessManager->post(QNetworkRequest(QUrl(url)), body);
    connect(reply, &QNetworkReply::finished, [reply, this]()
    {
        emit httpPostFinished(QJsonDocument::fromJson(reply->readAll()));
        reply->deleteLater();
    });
}

// Sends a HTTP DELETE request.
void HttpAdapter::httpDelete(const QString &url)
{
    QNetworkReply* reply = m_networkAccessManager->deleteResource(QNetworkRequest(QUrl(url)));
    connect(reply, &QNetworkReply::finished, [reply, this]()
    {
        emit httpDeleteFinished(QJsonDocument::fromJson(reply->readAll()));
        reply->deleteLater();
    });
}

// Sends a HTTP HEAD request.
void HttpAdapter::httpHead(const QString &url)
{
    QNetworkReply* reply = m_networkAccessManager->head(QNetworkRequest(QUrl(url)));
    connect(reply, &QNetworkReply::finished, [reply, this]()
    {
        emit httpHeadFinished(QJsonDocument::fromJson(reply->readAll()));
        reply->deleteLater();
    });
}

// Sends a HTTP COPY request.
void HttpAdapter::httpCopy(const QString &url, const QString &destination)
{
    QNetworkRequest request= QNetworkRequest(QUrl(url));
    request.setRawHeader("Destination", destination.toUtf8());
    QNetworkReply* reply = m_networkAccessManager->sendCustomRequest(request, "COPY");
    connect(reply, &QNetworkReply::finished, [reply, this]()
    {
        emit httpCopyFinished(QJsonDocument::fromJson(reply->readAll()));
        reply->deleteLater();
    });
}

// Sends a HTTP ANY request.
void HttpAdapter::httpAny(const QString &url)
{
    QNetworkReply* reply = m_networkAccessManager->sendCustomRequest(QNetworkRequest(QUrl(url)), "ANY");
    connect(reply, &QNetworkReply::finished, [reply, this]()
    {
        emit httpAnyFinished(QJsonDocument::fromJson(reply->readAll()));
        reply->deleteLater();
    });
}




