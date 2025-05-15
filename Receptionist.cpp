#include "Receptionist.h"
#include <QLabel>

Receptionist::Receptionist(QMap<QString, User> &usersMapRef, QObject *parent)
    : QObject(parent)
    , usersMap(usersMapRef)
{}

Receptionist::~Receptionist() {}

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

void Receptionist::displayClientInfo(const User &client,
                                     QLabel *nameLabel,
                                     QLabel *birthDateLabel,
                                     QLabel *subPeriodLabel)
{
    if (nameLabel)
        nameLabel->setText(client.username);
    if (birthDateLabel)
        birthDateLabel->setText(client.birthDate);
    if (subPeriodLabel)
        subPeriodLabel->setText(client.subscriptionPeriod);
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

void Receptionist::checkSubscriptionStatusForUser(const QString &userId)
{

        if (!usersMap.contains(userId))
            return;

        User &user = usersMap[userId];

        if (!user.isClient || !user.subscriptionStartDate.isValid())
            return;

        int months = 0;

        if (user.subscriptionPeriod == "Monthly")
            months = 1;
        else if (user.subscriptionPeriod == "3 Months")
            months = 3;
        else if (user.subscriptionPeriod == "6 Months")
            months = 6;
        else if (user.subscriptionPeriod == "Yearly")
            months = 12;
        else
            return;

        QDate endDate = user.subscriptionStartDate.addMonths(months);

        if (QDate::currentDate() > endDate) {
            user.isSubscriptionExpired = true;
            user.isSubscriptionExpiringSoon = false;
        }
        else if (QDate::currentDate().daysTo(endDate) <= 5) {
            user.isSubscriptionExpired = false;
            user.isSubscriptionExpiringSoon = true;
        }
        else {
            user.isSubscriptionExpired = false;
            user.isSubscriptionExpiringSoon = false;
        }

}

