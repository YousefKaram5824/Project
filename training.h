#ifndef TRAINING_H
#define TRAINING_H
#include <QQueue>
#include <QStack>
#include <QList>
#include <QString>
#include <QMap>
#include "User.h"
struct training{
    QString name;
    int capacity;
    QTime duration_time;
    QList<QString> days;
    QString assigned_coach;
    QMap<int, User> users;
    QList<User> waiting_list;
};

#endif // TRAINING_H
