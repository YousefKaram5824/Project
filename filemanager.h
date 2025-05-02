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
    static QMap<int, Court> loadCourtsFromFile(const QString& filePath);
    static void saveCourtsToFile(const QString& filePath, const QMap<int, Court>& courts);
};

#endif
