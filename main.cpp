#include <QApplication>
#include "filemanager.h"
#include "mainpage.h"

QMap<QString, User> usersMap;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileManager::load(usersMap);
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
    return result;
}
