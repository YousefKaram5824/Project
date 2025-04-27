// FileManager.h
/*
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include "User.h"

class FileManager {
public:
    static bool saveToFile(const QString &filename, const QMap<QString, User> &users);
    static bool loadFromFile(const QString &filename, QMap<QString, User> &users);
    //QMap<QString, User> users;
};
#endif // FILEMANAGER_H
*/
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QMap>
#include "User.h"

class FileManager
{
public:
    static void save(const QMap<QString, User> &usersMap);
    static void load(QMap<QString, User> &usersMap);
};

#endif // FILEMANAGER_H
