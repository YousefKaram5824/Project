#include <QApplication>
#include "filemanager.h"
#include "mainpage.h"

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
