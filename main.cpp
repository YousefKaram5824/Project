#include <QApplication>
#include "filemanager.h"
#include "mainpage.h"

QMap<QString, User> usersMap;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileManager::load(usersMap);
    QMap<int, Court> courtsMap = FileManager::loadCourtsFromFile("E:/Project/courts.txt");

    MainPage w(usersMap, courtsMap);
    User admin;
    admin.id = "admin";
    admin.username = "admin";
    admin.password = "admin";
    admin.isClient = false;
    admin.birthDate = "null";
    admin.subscriptionPeriod = "null";
    usersMap.insert(admin.id, admin);
    w.show();
    int result = a.exec();
    FileManager::save(usersMap);
    FileManager::saveCourtsToFile("E:/Project/courts.txt", courtsMap);



    return result;
}
