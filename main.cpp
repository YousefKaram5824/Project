#include <QApplication>
#include "filemanager.h"
#include "mainpage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMap<QString, User> usersMap;
    QMap<int, Court> courtsMap;
    QMap<QString, training> trainingsMap;
    QMap<QString, QStringList> notificationsMap;
    FileManager filemanager;
    filemanager.load(usersMap, courtsMap, trainingsMap, notificationsMap);

    MainPage w(usersMap, courtsMap, trainingsMap, notificationsMap);
    w.show();
    int result = a.exec();
    filemanager.save(usersMap, courtsMap, trainingsMap, notificationsMap);

    return result;
}
