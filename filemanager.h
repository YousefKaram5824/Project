#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QMap>
#include <QString>
#include <QDate>
#include <QTime>
#include <QList>
#include "User.h"
#include "Court.h"
class FileManager
{
public:
    static void save(const QMap<QString, User> &usersMap);
    static void load(QMap<QString, User> &usersMap);
    static void savecourt(const QList<Court> &courtsList);
    static void loadcourt(QList<Court> &courtsList);
};

#endif
