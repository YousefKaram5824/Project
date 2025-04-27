#include <QApplication>
#include "filemanager.h"
#include "mainpage.h"

QMap<QString, User> usersMap;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FileManager::load(usersMap);
    MainPage mainPage(usersMap);
    mainPage.show();

    // Register w(usersMap);
    // w.show();

    int result = a.exec();

    FileManager::save(usersMap);

    return result;
}
