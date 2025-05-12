#ifndef TRAINING_H
#define TRAINING_H
#include <QList>
#include <QMap>
#include <QQueue>
#include <QStack>
#include <QString>
#include "User.h"
struct training
{
    QString name;
    int capacity;
    QTime Stime;
    int duration_time;
    QList<QString> days;
    QString assigned_coach;
    QMap<QString, User> users;
    QList<User> waiting_list;

};

#endif // TRAINING_H
