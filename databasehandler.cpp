#include "databasehandler.h"
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>

DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject(parent)
{
    m_networkManager = new QNetworkAccessManager(this);

    // For GET request
    m_networkReply = m_networkManager->get(QNetworkRequest(QUrl("https://fir-qt-da647-default-rtdb.firebaseio.com/Pets.json")));
    connect(m_networkReply, &QNetworkReply::readyRead, this, &DatabaseHandler::networkReplyReadyRead);

    // For POST request
    QVariantMap newPet;
    newPet["Type"] = "Dog";
    newPet["Name"] = "Richie";
    newPet["Food"] = "Cookies";

    QJsonDocument jsonDoc = QJsonDocument::fromVariant(newPet);
    QNetworkRequest newPetRequest(QUrl("https://fir-qt-da647-default-rtdb.firebaseio.com/Pets.json"));
    newPetRequest.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));

    // Post the data
    m_networkReply = m_networkManager->post(newPetRequest, jsonDoc.toJson());
    connect(m_networkReply, &QNetworkReply::readyRead, this, &DatabaseHandler::networkReplyReadyRead);
}

DatabaseHandler::~DatabaseHandler()
{
    m_networkManager->deleteLater();
}

void DatabaseHandler::networkReplyReadyRead()
{
    qDebug() << m_networkReply->readAll();
}
