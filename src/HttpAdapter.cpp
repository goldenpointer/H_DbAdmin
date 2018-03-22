/****************************************************************************
**
** BSD 2-Clause License
**
** Copyright (c) 2018, mikispring
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**
**   * Redistributions of source code must retain the above copyright notice, this
**     list of conditions and the following disclaimer.
**
**   * Redistributions in binary form must reproduce the above copyright notice,
**     this list of conditions and the following disclaimer in the documentation
**     and/or other materials provided with the distribution.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
** SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
** CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
** OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************/

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




