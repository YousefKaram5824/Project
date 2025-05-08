#ifndef USER_H
#define USER_H
#include <QList>
#include <QString>
#include "WorkoutRecord.h"

struct User
{
    QString username;
    QString id;
    QString password;
    bool isClient = false;
    QString birthDate;
    QString subscriptionPeriod;
    int budget = 0;
    bool isVIP = false;
    QList<WorkoutRecord> workoutHistory;
};

#endif
