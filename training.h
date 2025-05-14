#ifndef TRAINING_H
#define TRAINING_H
#include <QList>
#include <QMap>
#include <QQueue>
#include <QStack>
#include <QString>
#include "User.h"
#include "qdatetime.h"
struct training
{
    QString name;
    int capacity;
    QTime Stime;
    int duration_time;
    QList<QString> days;
    QString assigned_coach;
    QMap<QString, User> users;
    QQueue<User> waiting_list;
    QQueue<User> VIP_waiting_list;
    QMap<QString, int> userProgress;
    QMap<QString, int> attended;
};

#endif // TRAINING_H
