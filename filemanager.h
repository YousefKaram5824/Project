#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QDate>
#include <QList>
#include <QMap>
#include <QString>
#include <QTime>
#include "Court.h"
#include "User.h"
class FileManager
{
public:
    static void save(const QMap<QString, User> &usersMap);
    static void load(QMap<QString, User> &usersMap);
    static void savecourt(const QList<Court> &courtsList);
    static void loadcourt(QList<Court> &courtsList);
};

#endif
