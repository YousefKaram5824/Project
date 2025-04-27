#include "UserManager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

UserManager::UserManager(const QString &fileName) : fileName(fileName) {
    loadUsers();  // تحميل اليوزرز من الملف عند بدء التشغيل
}

UserManager::~UserManager() {
    saveUsers();  // حفظ اليوزرز في الملف عند غلق البرنامج
}

void UserManager::saveUsers() {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing!";
        return;
    }

    QTextStream out(&file);

    // تخزين كل يوزر في سطر واحد
    for (auto it = users.begin(); it != users.end(); ++it) {
        const User &user = it.value();
        out << user.id << "," << user.username << "," << user.password << ","
            << user.isClient << "," << user.birthDate << "," << user.subscriptionPeriod << "\n";
    }

    file.close();
}

void UserManager::loadUsers() {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading!";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");

        if (parts.size() != 6) {
            continue;  // تخطي السطور الغير مكتملة
        }

        User user;
        user.id = parts[0];
        user.username = parts[1];
        user.password = parts[2];
        user.isClient = (parts[3] == "1");
        user.birthDate = parts[4];
        user.subscriptionPeriod = parts[5];

        users.insert(user.id, user);  // إضافة اليوزر إلى الخريطة
    }

    file.close();
}

void UserManager::addUser(const User &user) {
    users.insert(user.id, user);
}

QMap<QString, User> UserManager::getUsers() const {
    return users;
}
