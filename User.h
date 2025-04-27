#ifndef USER_H
#define USER_H
#include <QString>

struct User
{
    QString username;
    QString id;
    QString password;
    bool isClient;
    QString birthDate;
    QString subscriptionPeriod;
};

#endif // USER_H
