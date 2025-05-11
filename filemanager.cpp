#include "FileManager.h"
#include <QDebug>
#include <QFile>
#include <QList>
#include <QTextStream>
#include "Court.h"
#include "training.h"

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
    QStringList paths = {":/files/users.txt",
                         "qrc:/files/users.txt",
                         "Y:/Project/users.txt",
                         "E:/Project1/users.txt",
                         "C:\\Users\\ASUS\\Documents\\Project_master\\users.txt",
                         "D:/Project/users.txt",
                         "users.txt"};

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
    QStringList paths = {":/files/users.txt",
                         "qrc:/files/users.txt",
                         "Y:/Project/users.txt",
                         "E:/Project1/users.txt",
                         "C:\\Users\\ASUS\\Documents\\Project_master\\users.txt",
                         "D:/Project/users.txt",
                         "users.txt"};

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
        if (fields.size() < 8) {
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
    QStringList paths = {":/files/courts.txt",
                         "qrc:/files/courts.txt",
                         "Y:/Project/courts.txt",
                         "E:/Project1/courts.txt",
                         "C:\\Users\\ASUS\\Documents\\Project_master\\courts.txt",
                         "D:/Project/courts.txt",
                         "courts.txt"};

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

        if (parts.size() >= 7) {
            int id = parts[0].toInt();
            QString name = parts[1];
            QString location = parts[2];
            QDate date = QDate::fromString(parts[3], "yyyy-MM-dd");
            QTime time = QTime::fromString(parts[4], "HH:mm");
            bool isBooked = (parts[5].toLower() == "true");
            QString idString = QString::number(id);
            QString userId = parts[6];
            courts[id] = Court(idString, name, location, date, time, isBooked, userId);
        }
    }
    file.close();
    return courts;
}

void FileManager::saveCourtsToFile(const QMap<int, Court> &courts)
{
    QFile file;
    QStringList paths = {":/files/courts.txt",
                         "qrc:/files/courts.txt",
                         "Y:/Project/courts.txt",
                         "E:/Project1/courts.txt",
                         "C:\\Users\\ASUS\\Documents\\Project_master\\courts.txt",
                         "D:/Project/courts.txt",
                         "courts.txt"};

    if (!tryOpenFile(file, paths, QIODevice::WriteOnly)) {
        qDebug() << "Failed to open courts file for writing in any path.";
        return;
    }

    QTextStream out(&file);
    for (const Court &court : courts) {
        out << court.id << "," << court.name << "," << court.location << ","
            << court.date.toString("yyyy-MM-dd") << "," << court.time.toString("HH:mm") << ","
            << (court.isBooked ? "true" : "false") << "," << court.clientId << "\n";
    }
    file.close();
}

void FileManager::saveTrainingsToFile(const QMap<QString, training> &trainingsMap)
{
    QFile file;
    QStringList paths = {":/files/trainings.txt",
                         "qrc:/files/trainings.txt",
                         "E:/Project1/trainings.txt",
                         "Y:/Final Project/trainings.txt",
                         "Y:/Project/trainings.txt",
                         "C:/Users/ASUS/Documents/Project_master/trainings.txt",
                         "D:/Project/trainings.txt",
                         "trainings.txt"};

    if (!tryOpenFile(file, paths, QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing in any path.";
        return;
    }

    QTextStream out(&file);
    for (const auto &t : trainingsMap) {
        out << t.name << "," << t.capacity << "," << t.Stime.toString("HH:mm") << ","
            << t.duration_time << "," << t.days.join('|') << "," << t.assigned_coach << "\n";
    }

    file.close();
}
QMap<QString, training> FileManager::loadTrainingsFromFile()
{
    QMap<QString, training> trainingsMap;
    QFile file;
    QStringList paths = {":/files/trainings.txt",
                         "qrc:/files/trainings.txt",
                         "E:/Project1/trainings.txt",
                         "Y:/Final Project/trainings.txt",
                         "Y:/Project/trainings.txt",
                         "C:/Users/ASUS/Documents/Project_master/trainings.txt",
                         "D:/Project/trainings.txt",
                         "trainings.txt"};

    if (!tryOpenFile(file, paths, QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading in any path. Creating new file.";
        QFile newFile("trainings.txt");
        newFile.open(QIODevice::WriteOnly);
        newFile.close();
        return trainingsMap;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty())
            continue;

        QStringList fields = line.split(',');
        if (fields.size() < 6) {
            qDebug() << "Invalid training line:" << line;
            continue;
        }

        training t;
        t.name = fields[0];
        t.capacity = fields[1].toInt();
        t.Stime = QTime::fromString(fields[2], "HH:mm");
        t.duration_time = fields[3].toInt();
        t.days = fields[4].split('|', Qt::SkipEmptyParts);
        t.assigned_coach = fields[5];

        trainingsMap.insert(t.name, t);
    }

    file.close();
    return trainingsMap;
}

void FileManager::save(const QMap<QString, User> &usersMap,
                       const QMap<int, Court> &courtsMap,
                       const QMap<QString, training> &trainingsMap)
{
    saveUsersToFile(usersMap);
    saveCourtsToFile(courtsMap);
    saveTrainingsToFile(trainingsMap);
}

void FileManager::load(QMap<QString, User> &usersMap,
                       QMap<int, Court> &courtsMap,
                       QMap<QString, training> &trainingsMap)
{
    usersMap = loadUsersFromFile();
    courtsMap = loadCourtsFromFile();
    trainingsMap = loadTrainingsFromFile();
}
