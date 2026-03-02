// GeminiApiClient.h
#ifndef GEMINIAPICLIENT_H
#define GEMINIAPICLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>

class GeminiApiClient : public QObject {
    Q_OBJECT
public:
    explicit GeminiApiClient(QObject *parent = nullptr);
    void sendGroundingRequest(const QString& prompt, const QString& apiKey);

signals:
    void responseReceived(const QJsonObject& response);
    void errorOccurred(const QString& errorString);

private slots:
    void onReplyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager* m_networkManager;
};

#endif // GEMINIAPICLIENT_H
