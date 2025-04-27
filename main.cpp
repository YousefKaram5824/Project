#include "mainpage.h"
#include "filemanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileManager::getInstance().loadAllData();
    MainPage w;
    w.show();
    int result = a.exec();
    FileManager::getInstance().saveAllData();
    return result;
}
