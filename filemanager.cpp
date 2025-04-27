#include "filemanager.h"
#include <QDebug>

FileManager& FileManager::getInstance()
{
    static FileManager instance;
    return instance;
}

void FileManager::saveAllData()
{
    saveToFile(CUSTOMERS_FILE, customers);
    saveToFile(COACHES_FILE, coaches);
    saveToFile(RECEPTIONISTS_FILE, receptionists);
}

void FileManager::loadAllData()
{
    customers = loadFromFile(CUSTOMERS_FILE);
    coaches = loadFromFile(COACHES_FILE);
    receptionists = loadFromFile(RECEPTIONISTS_FILE);
}

void FileManager::saveToFile(const QString& filename, const QVector<QString>& data)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing:" << filename;
        return;
    }

    QTextStream out(&file);
    for (const QString& item : data) {
        out << item << "\n";
    }

    file.close();
}

QVector<QString> FileManager::loadFromFile(const QString& filename)
{
    QVector<QString> data;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading:" << filename;
        return data;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.isEmpty()) {
            data.append(line);
        }
    }

    file.close();
    return data;
}
