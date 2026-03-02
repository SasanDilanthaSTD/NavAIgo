// GeminiApiClient.cpp
#include "GeminiApiClient.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

GeminiApiClient::GeminiApiClient(QObject *parent)
    : QObject(parent), m_networkManager(new QNetworkAccessManager(this)) {
    connect(m_networkManager, &QNetworkAccessManager::finished,
            this, &GeminiApiClient::onReplyFinished);
}

void GeminiApiClient::sendGroundingRequest(const QString& prompt, const QString& apiKey) {
    // Note: URL structure follows Gemini Maps Grounding API docs
    QUrl url("https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-pro:generateContent?key=" + apiKey);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Constructing JSON payload with tools enabled (Maps Grounding)
    QJsonObject root;
    QJsonArray contents;
    QJsonObject parts, textPart;
    textPart["text"] = prompt;
    parts["parts"] = QJsonArray{textPart};
    contents.append(parts);
    root["contents"] = contents;

    // Enable Maps Grounding Tool
    QJsonObject tools, googleSearch;
    googleSearch["googleSearchRetrieval"] = QJsonObject(); // Simplified for example
    tools["tools"] = QJsonArray{googleSearch};
    root["tools"] = tools;

    m_networkManager->post(request, QJsonDocument(root).toJson());
}

void GeminiApiClient::onReplyFinished(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        emit responseReceived(jsonDoc.object());
    } else {
        emit errorOccurred(reply->errorString());
    }
    reply->deleteLater(); // Memory management
}
