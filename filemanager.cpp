/*
#include "FileManager.h"
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QMap>
#include "User.h"
*/
#include "FileManager.h"
#include "Court.h"
#include <QDebug>
#include <QFile>
#include <QList>
#include <QTextStream>

void FileManager::save(const QMap<QString, User> &usersMap)
{
    QFile file("E:/Project/users.txt");

    //"E:/Project/users.txt" PATH of Habiba
    //"Y:/Final Project/users.txt" PATH of keko

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing.";
        return;
    }

    QTextStream out(&file);

    for (const auto &user : usersMap) {
        out << user.username << "," << user.id << "," << user.password << "," << user.isClient
            << "," << user.birthDate << "," << user.subscriptionPeriod << "\n";
    }
    file.close();
}

void FileManager::load(QMap<QString, User> &usersMap)
{
    QFile file("E:/Project/users.txt");

    //"E:/Project/users.txt" PATH of Habiba
    //"Y:/Final Project/users.txt" PATH of keko

    if (!file.exists()) {
        QFile newFile("users.txt");
        newFile.open(QIODevice::WriteOnly);
        newFile.close();
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading.";
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line.trimmed().isEmpty())
            continue;

        QStringList fields = line.split(',');

        if (fields.size() != 6) {
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
        usersMap.insert(user.id, user);
    }
    file.close();
}

QMap<int, Court> FileManager::loadCourtsFromFile(const QString& filePath) {
    QMap<int, Court> courts;
    QFile file(filePath);


    if (!file.exists()) {
        qDebug() << "File does not exist:" << filePath;
        return courts;
    }


    if (file.open(QIODevice::ReadOnly)) {
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
    }
     //qDebug() << "Courts loaded:" << courts.size();
    return courts;
}

void FileManager::saveCourtsToFile(const QString& filePath, const QMap<int, Court>& courts) {
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        for (const Court& court : courts) {
            out << court.id << "," << court.name << "," << court.location << ","
                << court.date.toString("yyyy-MM-dd") << "," << court.time.toString("HH:mm") << ","
                << (court.isBooked ? "true" : "false") << "\n";
        }
        file.close();
    }
}
