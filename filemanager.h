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
#include "training.h"

class FileManager
{
public:
    static void save(const QMap<QString, User> &usersMap,
                     const QMap<int, Court> &courtsMap,
                     const QMap<QString, training> &trainingsMap,
                     const QMap<QString, QStringList> &notificationsMap);

    static void load(QMap<QString, User> &usersMap,
                     QMap<int, Court> &courtsMap,
                     QMap<QString, training> &trainingsMap,
                     QMap<QString, QStringList> &notificationsMap);
    static void saveUsersToFile(const QMap<QString, User> &usersMap);
    static void saveCourtsToFile(const QMap<int, Court> &courts);
    static void saveTrainingsToFile(const QMap<QString, training> &trainingsMap);
    static void saveNotificationsToFile(const QMap<QString, QStringList> &notificationsMap);
    static QMap<QString, User> loadUsersFromFile();
    static QMap<int, Court> loadCourtsFromFile();
    static QMap<QString, training> loadTrainingsFromFile();
    static QMap<QString, QStringList> loadNotificationsFromFile();

private:
    static bool tryOpenFile(QFile &file, const QStringList &paths, QIODevice::OpenMode mode);
};

#endif
