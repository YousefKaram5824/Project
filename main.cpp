#include <QApplication>
#include "filemanager.h"
#include "mainpage.h"
//#include "training.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMap<QString, User> usersMap;
    QMap<int, Court> courtsMap;
    QMap<QString, training> trainingsMap;
    FileManager filemanager;
    filemanager.load(usersMap, courtsMap,trainingsMap);

    MainPage w(usersMap, courtsMap,trainingsMap);
    w.show();
    int result = a.exec();
    filemanager.save(usersMap, courtsMap,trainingsMap);

    return result;
}
