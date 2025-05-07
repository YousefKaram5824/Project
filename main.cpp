#include <QApplication>
#include "filemanager.h"
#include "mainpage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMap<QString, User> usersMap;
    QMap<int, Court> courtsMap;
    FileManager filemanager;
    filemanager.load(usersMap, courtsMap);

    MainPage w(usersMap, courtsMap);
    w.show();
    int result = a.exec();
    filemanager.save(usersMap, courtsMap);

    return result;
}
