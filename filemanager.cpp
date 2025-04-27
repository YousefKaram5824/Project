/*
#include "FileManager.h"
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QMap>
#include "User.h"
*/
#include "FileManager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

void FileManager::save(const QMap<QString, User> &usersMap)
{
    QFile file("E:/Project/users.txt");
    // qDebug() << "Attempting to open file...";
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing.";
        return;
    }
    // qDebug() << "File opened successfully.";
    QTextStream out(&file);

    for (const auto &user : usersMap) {
        out << user.username << ","
            << user.id << ","
            << user.password << ","
            << user.isClient << ","
            << user.birthDate << ","
            << user.subscriptionPeriod << "\n";
    }
   // qDebug() << "Data saved to file.";
    file.close();
}

void FileManager::load(QMap<QString, User> &usersMap)
{
    QFile file("E:/Project/users.txt");
    if (!file.exists()) {
        // If file doesn't exist, create an empty file
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
int lineCount = 0;
    while (!in.atEnd()) {
    QString line = in.readLine();
    lineCount++;
    if (line.trimmed().isEmpty()) continue; // Skip empty lines

    QStringList fields = line.split(',');

    if (fields.size() != 6) {
        qDebug() << "Invalid line format:" << line;
        continue; // Skip invalid lines
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
   // qDebug() << "Loaded" << lineCount << "lines from the file.";
    file.close();
}

