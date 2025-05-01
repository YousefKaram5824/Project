#include "Receptionist.h"
#include <QLabel>

Receptionist::Receptionist(QMap<QString, User> &usersMapRef, QObject *parent)
    : QObject(parent)
    , usersMap(usersMapRef)
{
}

Receptionist::~Receptionist()
{
}

bool Receptionist::validateClient(const QString &clientId)
{
    if (!usersMap.contains(clientId)) {
        emit clientNotFound("Client ID not found");
        return false;
    }

    const User &client = usersMap[clientId];
    if (!client.isClient) {
        emit invalidClientType("The entered ID does not belong to a client");
        return false;
    }

    return true;
}

void Receptionist::displayClientInfo(const User &client, QLabel *nameLabel, QLabel *birthDateLabel, QLabel *subscriptionLabel)
{
    if (nameLabel) nameLabel->setText(client.username);
    if (birthDateLabel) birthDateLabel->setText(client.birthDate);
    if (subscriptionLabel) subscriptionLabel->setText(client.subscriptionPeriod);
}

QString Receptionist::getClientInfo(const QString &clientId)
{
    if (!validateClient(clientId)) {
        return QString();
    }

    const User &client = usersMap[clientId];
    return QString("Name: %1\nBirth Date: %2\nSubscription Period: %3")
        .arg(client.username, client.birthDate, client.subscriptionPeriod);
}
