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

#endif
