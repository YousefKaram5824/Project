#ifndef USER_H
#define USER_H
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
};

#endif
