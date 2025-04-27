#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFile>
#include <QMap>
#include <QString>
#include <QTextStream>
#include <QVector>

class FileManager
{
public:
    static FileManager &getInstance();
    void saveAllData();
    void loadAllData();

private:
    FileManager() {}
    FileManager(const FileManager &) = delete;
    FileManager &operator=(const FileManager &) = delete;

    const QString CUSTOMERS_FILE = "customers.txt";
    const QString COACHES_FILE = "coaches.txt";
    const QString RECEPTIONISTS_FILE = "receptionists.txt";

    QVector<QString> customers;
    QVector<QString> coaches;
    QVector<QString> receptionists;

    void saveToFile(const QString &filename, const QVector<QString> &data);
    QVector<QString> loadFromFile(const QString &filename);
};
#endif
