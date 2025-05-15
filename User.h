#ifndef USER_H
#define USER_H
#include "qdatetime.h"
#include <QList>
#include <QString>

struct User
{
    QString username;
    QString id;
    QString password;
    bool isClient = false;
    QString birthDate;
    QString subscriptionPeriod;
    bool isVIP = false;
    QDate subscriptionStartDate;
    bool  isSubscriptionExpired=false;
    bool isSubscriptionExpiringSoon = false;
};

#endif
