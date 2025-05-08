#include "FileManager.h"
#include <QDebug>
#include <QFile>
#include <QList>
#include <QTextStream>
#include "Court.h"

bool FileManager::tryOpenFile(QFile &file, const QStringList &paths, QIODevice::OpenMode mode)
{
    for (const QString &path : paths) {
        file.setFileName(path);
        if (file.open(mode)) {
            return true;
        }
    }
    return false;
}

void FileManager::saveUsersToFile(const QMap<QString, User> &usersMap)
{
    QFile file;
    QStringList paths = {
        "E:/Project/users.txt",       // Habiba
        "Y:/Final Project/users.txt", // Keko
    "C:\\Users\\ASUS\\Documents\\Project_branchk\\users.txt",
        "users.txt"                   // Local path as last resort
    };

    if (!tryOpenFile(file, paths, QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing in any path.";
        return;
    }

    QTextStream out(&file);
    for (const auto &user : usersMap) {
        // Save basic user info
        out << user.username << "," << user.id << "," << user.password << "," << user.isClient
            << "," << user.birthDate << "," << user.subscriptionPeriod << "," << user.budget << ","
            << user.isVIP << "\n";
    }
    file.close();
}

QMap<QString, User> FileManager::loadUsersFromFile()
{
    QMap<QString, User> usersMap;
    QFile file;
    QStringList paths = {
        "E:/Project/users.txt",       // Habiba
        "Y:/Final Project/users.txt", // Keko
         "C:\\Users\\ASUS\\Documents\\Project_branchk\\users.txt",
        "users.txt"                   // Local path as last resort
    };

    if (!tryOpenFile(file, paths, QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading in any path. Creating new file.";
        QFile newFile("users.txt");
        newFile.open(QIODevice::WriteOnly);
        newFile.close();
        return usersMap;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty())
            continue;

        QStringList fields = line.split(',');
        if (fields.size() < 8) { // At least 8 fields for basic user info
            qDebug() << "Invalid line format:" << line;
            continue;
        }

        User user;
        user.username = fields[0];
        user.id = fields[1];
        user.password = fields[2];
        user.isClient = (fields[3] == "1");
        user.birthDate = fields[4];
        user.subscriptionPeriod = fields[5];
        user.budget = fields[6].toInt();
        user.isVIP = (fields[7] == "1");

        usersMap.insert(user.id, user);
    }
    file.close();
    return usersMap;
}

QMap<int, Court> FileManager::loadCourtsFromFile()
{
    QMap<int, Court> courts;
    QFile file;
    QStringList paths = {
        "E:/Project/courts.txt",       // Habiba
        "Y:/Final Project/courts.txt", // Keko
        "C:\\Users\\ASUS\\Documents\\Project_branchk\\courts.txt",
        "courts.txt"                   // Local path as last resort
    };

    if (!tryOpenFile(file, paths, QIODevice::ReadOnly)) {
        qDebug() << "Failed to open courts file in any path.";
        return courts;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',', Qt::SkipEmptyParts);
        for (QString &part : parts) {
            part = part.trimmed();
        }

        if (parts.size() == 6) {
            int id = parts[0].toInt();
            QString name = parts[1];
            QString location = parts[2];
            QDate date = QDate::fromString(parts[3], "yyyy-MM-dd");
            QTime time = QTime::fromString(parts[4], "HH:mm");
            bool isBooked = (parts[5].toLower() == "true");
            QString idString = QString::number(id);
            courts[id] = Court(idString, name, location, date, time, isBooked);
        }
    }
    file.close();
    return courts;
}

void FileManager::saveCourtsToFile(const QString &filePath, const QMap<int, Court> &courts)
{
    QFile file;
    QStringList paths = {
        filePath,                      // Primary path
        "E:/Project/courts.txt",       // Habiba
        "Y:/Final Project/courts.txt", // Keko
         "C:\\Users\\ASUS\\Documents\\Project_branchk\\courts.txt",
        "courts.txt"                   // Local path as last resort
    };

    if (!tryOpenFile(file, paths, QIODevice::WriteOnly)) {
        qDebug() << "Failed to open courts file for writing in any path.";
        return;
    }

    QTextStream out(&file);
    for (const Court &court : courts) {
        out << court.id << "," << court.name << "," << court.location << ","
            << court.date.toString("yyyy-MM-dd") << "," << court.time.toString("HH:mm") << ","
            << (court.isBooked ? "true" : "false") << "\n";
    }
    file.close();
}

void FileManager::save(const QMap<QString, User> &usersMap, const QMap<int, Court> &courtsMap)
{
    saveUsersToFile(usersMap);
    saveCourtsToFile("", courtsMap);
}

void FileManager::load(QMap<QString, User> &usersMap, QMap<int, Court> &courtsMap)
{
    usersMap = loadUsersFromFile();
    courtsMap = loadCourtsFromFile();
}
