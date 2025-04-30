#include <QApplication>
#include "filemanager.h"
#include "mainpage.h"

QMap<QString, User> usersMap;
QList<Court> courtsList;
QMap<QString, QMap<QDate, QMap<QTime, Court>>> courtData;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileManager::load(usersMap);
    FileManager::loadcourt(courtsList);

    MainPage mainPage(usersMap);
    User admin;
    admin.id = "admin";
    admin.username = "admin";
    admin.password = "admin";
    admin.isClient = false;
    admin.birthDate = "null";
    admin.subscriptionPeriod = "null";
    usersMap.insert(admin.id, admin);
    mainPage.show();
    int result = a.exec();
    FileManager::save(usersMap);
    FileManager::savecourt(courtsList);

    return result;
}
