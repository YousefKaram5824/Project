#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QDate>
#include <QFile>
#include <QIODevice>
#include <QList>
#include <QMap>
#include <QString>
#include <QTime>
#include "Court.h"
#include "User.h"

class FileManager
{
public:
    static void save(const QMap<QString, User> &usersMap, const QMap<int, Court> &courtsMap);
    static void load(QMap<QString, User> &usersMap, QMap<int, Court> &courtsMap);
    static void saveUsersToFile(const QMap<QString, User> &usersMap);
    static QMap<QString, User> loadUsersFromFile();
    static QMap<int, Court> loadCourtsFromFile();
    static void saveCourtsToFile(const QString &filePath, const QMap<int, Court> &courts);

private:
    static bool tryOpenFile(QFile &file, const QStringList &paths, QIODevice::OpenMode mode);
};

#endif
