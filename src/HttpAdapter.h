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

#ifndef HTTPADAPTER_H
#define HTTPADAPTER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonDocument>


class HttpAdapter: public QObject
{
    Q_OBJECT

    public:
        explicit HttpAdapter(QObject *parent = nullptr);
        void httpGet(const QString &url);
        void httpPut(const QString &url, const QByteArray &body);
        void httpPost(const QString &url, const QByteArray &body);
        void httpDelete(const QString &url);
        void httpHead(const QString &url);
        void httpCopy(const QString &url, const QString &destination);
        void httpAny(const QString &url);

    signals:
        void httpGetFinished(const QJsonDocument &document);
        void httpPutFinished(const QJsonDocument &document);
        void httpPostFinished(const QJsonDocument &document);
        void httpDeleteFinished(const QJsonDocument &document);
        void httpHeadFinished(const QJsonDocument &document);
        void httpCopyFinished(const QJsonDocument &document);
        void httpAnyFinished(const QJsonDocument &document);

    private:
        QNetworkAccessManager* m_networkAccessManager;
};

#endif // HTTPADAPTER_H
