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
