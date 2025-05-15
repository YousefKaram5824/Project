#include "FileManager.h"
#include <QDebug>
#include <QFile>
#include <QList>
#include <QTextStream>

bool FileManager::tryOpenFile(QFile &file, const QStringList &paths, QIODevice::OpenMode mode)
{
    for (const QString &path : paths) {
        file.setFileName(path);
        if (file.open(mode)) {
            return true;
        }
    }
    return false;
}

QMap<QString, User> FileManager::loadUsersFromFile()
{
    QMap<QString, User> usersMap;
    QFile file;
    QStringList paths = {":/files/users.txt",
                         "qrc:/files/users.txt",
                         "Y:/Project/users.txt",
                         "E:/Project/users.txt",
                         "C:\\Users\\ASUS\\Documents\\Project_master\\users.txt",
                         "D:/Project/users.txt",
                         "users.txt"};

    if (!tryOpenFile(file, paths, QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading in any path. Creating new file.";
        QFile newFile("users.txt");
        newFile.open(QIODevice::WriteOnly);
        newFile.close();
        return usersMap;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty())
            continue;

        QStringList fields = line.split(',');
        if (fields.size() < 8) {
            qDebug() << "Invalid line format:" << line;
            continue;
        }


        User user;
        user.username = fields[0];
        user.id = fields[1];
        user.password = fields[2];
        user.isClient = (fields[3] == "1");
        user.birthDate = fields[4];
        user.subscriptionPeriod = fields[5];
        user.isVIP = (fields[6] == "1");
        QString startDateStr = fields[7].trimmed();
        if (startDateStr.isEmpty() || startDateStr.toLower() == "null") {
            user.subscriptionStartDate = QDate();
        } else {
            user.subscriptionStartDate = QDate::fromString(startDateStr, Qt::ISODate);
        }
        user.isSubscriptionExpired = (fields.size() >= 9 && fields[8].trimmed() == "1");
        user.isSubscriptionExpired = (fields.size() >= 10 && fields[9].trimmed() == "1");



        usersMap.insert(user.id, user);
    }
    file.close();
    return usersMap;
}

void FileManager::saveUsersToFile(const QMap<QString, User> &usersMap)
{
    QFile file;
    QStringList paths = {":/files/users.txt",
                         "qrc:/files/users.txt",
                         "Y:/Project/users.txt",
                         "E:/Project/users.txt",
                         "C:\\Users\\ASUS\\Documents\\Project_master\\users.txt",
                         "D:/Project/users.txt",
                         "users.txt"};

    if (!tryOpenFile(file, paths, QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing in any path.";
        return;
    }

    QTextStream out(&file);
    for (const auto &user : usersMap) {
        // Save basic user info
        out << user.username << "," << user.id << "," << user.password << "," << user.isClient
            << "," << user.birthDate << "," << user.subscriptionPeriod << "," << user.isVIP  << ","
            << (user.subscriptionStartDate.isValid() ? user.subscriptionStartDate.toString(Qt::ISODate) : "null")
            << "," << (user.isSubscriptionExpired ? "1" : "0")
            << "," << (user.isSubscriptionExpiringSoon ? "1" : "0") << "\n";

    }
    file.close();
}

QMap<int, Court> FileManager::loadCourtsFromFile()
{
    QMap<int, Court> courtsMap;
    QFile file;
    QStringList paths = {"E:/Project/courts.txt",
                         ":/files/courts.txt",
                         "qrc:/files/courts.txt",
                         "Y:/Project/courts.txt",
                         "C:\\Users\\ASUS\\Documents\\Project_master\\courts.txt",
                         "D:/Project/courts.txt",
                         "courts.txt"};
    if (!tryOpenFile(file, paths, QIODevice::ReadOnly)) {
        qDebug() << "Failed to open courts file in any path.";
        return courtsMap;
    }

    QTextStream in(&file);
    int lineNumber = 0;

    qDebug() << "File path used:" << file.fileName();


    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split(',');

       // qDebug() << "Parsed line:" << parts;

        for (QString &part : parts) {
            part = part.trimmed();
        }

        if (parts.size() == 11)
         {

            int id = parts[0].toInt();
            QString name = parts[1];
            QString location = parts[2];
            QDate date = QDate::fromString(parts[3], "yyyy-MM-dd");
            QTime time = QTime::fromString(parts[4], "HH:mm");
            bool isBooked = (parts[5].trimmed() == "1");
            QString idString = QString::number(id);
            QString userId = parts[6];
            QDate bookingDate = QDate::fromString(parts[7], "yyyy-MM-dd");
            QTime bookingTime = QTime::fromString(parts[8], "HH:mm");
            QStringList vipQueue = parts[9].split(";");
            QStringList normalQueue = parts[10].split(";");
            Court court(idString,
                        name,
                        location,
                        date,
                        time,
                        isBooked,
                        userId,
                        bookingDate,
                        bookingTime);
            court.bookingDate = bookingDate;
            court.bookingTime = bookingTime;

            if (!date.isValid() || !time.isValid()) {
                qDebug() << "Invalid date or time in line:" << line;
                continue;
            }

            for (const QString &vip : std::as_const(vipQueue))
                court.waitingListVIP.enqueue(vip);

            for (const QString &normal : std::as_const(normalQueue))
                court.waitingListNormal.enqueue(normal);

            courtsMap.insert(id, court);
            ++lineNumber;
        }
    }

    file.close();

    //qDebug() << "Total courts loaded:" << courtsMap.size();

    return courtsMap;
}

void FileManager::saveCourtsToFile(const QMap<int, Court> &courtsMap)
{
    QFile file;
    QStringList paths = {"E:/Project/courts.txt",
                         ":/files/courts.txt",
                         "qrc:/files/courts.txt",
                         "Y:/Project/courts.txt",
                         "C:\\Users\\ASUS\\Documents\\Project_master\\courts.txt",
                         "D:/Project/courts.txt",
                         "courts.txt"};
    if (!tryOpenFile(file, paths, QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading in any path. Creating new file.";
        return;
    }
    QTextStream out(&file);
    for (auto it = courtsMap.begin(); it != courtsMap.end(); ++it)
    {
        const Court& court = it.value();
        QString vipQueue = court.waitingListVIP.join(";");
        QString normalQueue = court.waitingListNormal.join(";");

        out << court.id << ","
            << court.name << ","
            << court.location << ","
            << court.date.toString("yyyy-MM-dd") << ","
            << court.time.toString("HH:mm") << ","
            << court.isBooked << ","
            << court.clientId << ","
            << court.bookingDate.toString("yyyy-MM-dd") << ","
            << court.bookingTime.toString("HH:mm") << ","
            << vipQueue << ","
            << normalQueue << "\n";
    }
    file.close();
}

QMap<QString, training> FileManager::loadTrainingsFromFile()
{
    QMap<QString, training> trainingsMap;
    QFile file;
    QStringList paths = {":/files/trainings.txt",
                         "qrc:/files/trainings.txt",
                         "E:/Project/trainings.txt",
                         "Y:/Final Project/trainings.txt",
                         "Y:/Project/trainings.txt",
                         "C:/Users/ASUS/Documents/Project_master/trainings.txt",
                         "D:/Project/trainings.txt",
                         "trainings.txt"};

    if (!tryOpenFile(file, paths, QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading in any path. Creating new file.";
        QFile newFile("trainings.txt");
        newFile.open(QIODevice::WriteOnly);
        newFile.close();
        return trainingsMap;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty())
            continue;

        QStringList fields = line.split(',');
        if (fields.size() < 6) {
            qDebug() << "Invalid training line:" << line;
            continue;
        }

        training t;
        t.name = fields[0];
        t.capacity = fields[1].toInt();
        t.Stime = QTime::fromString(fields[2], "HH:mm");
        t.duration_time = fields[3].toInt();
        t.days = fields[4].split('|', Qt::SkipEmptyParts);
        t.assigned_coach = fields[5];

        if (fields.size() >= 7) {
            QStringList userIds = fields[6].split('|', Qt::SkipEmptyParts);
            for (const QString &idStr : std::as_const(userIds)) {
                User dummyUser;
                dummyUser.id = idStr;
                t.users.insert(idStr, dummyUser);
            }
        }
        if (fields.size() >= 8) {
            QStringList waitIds = fields[7].split('|', Qt::SkipEmptyParts);
            for (const QString &uid : std::as_const(waitIds)) {
                User dummyUser;
                dummyUser.id = uid;
                t.waiting_list.append(dummyUser);
            }
        }
        if (fields.size() >= 9) {
            QStringList vipIds = fields[8].split('|', Qt::SkipEmptyParts);
            for (const QString &vipId : std::as_const(vipIds)) {
                User dummyVIP;
                dummyVIP.id = vipId;
                dummyVIP.isVIP = true;
                t.VIP_waiting_list.append(dummyVIP);
            }
        }

        if (fields.size() >= 10) {
            QStringList progressItems = fields[9].split('|', Qt::SkipEmptyParts);
            for (const QString &item : std::as_const(progressItems)) {
                QStringList parts = item.split(':');
                if (parts.size() == 2) {
                    t.userProgress.insert(parts[0], parts[1].toInt());
                }
            }
        }

        if (fields.size() >= 11) {
            QStringList attendedItems = fields[10].split('|', Qt::SkipEmptyParts);
            for (const QString &item : std::as_const(attendedItems)) {
                QStringList parts = item.split(':');
                if (parts.size() == 2) {
                    t.attended.insert(parts[0], parts[1].toInt());
                }
            }
        }

        trainingsMap.insert(t.name, t);
    }

    file.close();
    return trainingsMap;
}

void FileManager::saveTrainingsToFile(const QMap<QString, training> &trainingsMap)
{
    QFile file;
    QStringList paths = {":/files/trainings.txt",
                         "qrc:/files/trainings.txt",
                         "E:/Project/trainings.txt",
                         "Y:/Final Project/trainings.txt",
                         "Y:/Project/trainings.txt",
                         "C:/Users/ASUS/Documents/Project_master/trainings.txt",
                         "D:/Project/trainings.txt",
                         "trainings.txt"};

    if (!tryOpenFile(file, paths, QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing in any path.";
        return;
    }

    QTextStream out(&file);
    for (const auto &t : trainingsMap) {
        out << t.name << "," << t.capacity << "," << t.Stime.toString("HH:mm") << ","
            << t.duration_time << "," << t.days.join('|') << "," << t.assigned_coach;

        QStringList enrolledUserIds;
        for (auto it = t.users.begin(); it != t.users.end(); ++it) {
            enrolledUserIds << (it.key());
        }
        out << "," << enrolledUserIds.join('|');

        QStringList waitingUserIds;
        for (const auto &user : t.waiting_list) {
            waitingUserIds << user.id;
        }
        out << "," << waitingUserIds.join('|');

        QStringList vipWaitingUserIds;
        for (const auto &vipUser : t.VIP_waiting_list) {
            vipWaitingUserIds << vipUser.id;
        }
        out << "," << vipWaitingUserIds.join('|');

        QStringList progressData;
        for (auto it = t.userProgress.begin(); it != t.userProgress.end(); ++it) {
            progressData << (it.key() + ":" + QString::number(it.value()));
        }
        out << "," << progressData.join('|');

        QStringList attendedData;
        for (auto it = t.attended.begin(); it != t.attended.end(); ++it) {
            attendedData << (it.key() + ":" + QString::number(it.value()));
        }
        out << "," << attendedData.join('|');

        out << "\n";
    }
    file.close();
}

QMap<QString, QStringList> FileManager::loadNotificationsFromFile()
{
    QMap<QString, QStringList> notificationsMap;
    QFile file;
    QStringList paths = {":/files/notifications.txt",
                         "qrc:/files/notifications.txt",
                         "E:/Project/notifications.txt",
                         "Y:/Final Project/notifications.txt",
                         "Y:/Project/notifications.txt",
                         "C:/Users/ASUS/Documents/Project_master/notifications.txt",
                         "D:/Project/notifications.txt",
                         "notifications.txt"};

    if (!tryOpenFile(file, paths, QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open notifications file for reading in any path. Creating new file.";
        QFile newFile("notifications.txt");
        newFile.open(QIODevice::WriteOnly);
        newFile.close();
        return notificationsMap;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty())
            continue;

        QStringList parts = line.split(',');
        if (parts.size() < 2) {
            qDebug() << "Invalid notification line:" << line;
            continue;
        }

        QString clientId = parts[0];
        QStringList notifications = parts[1].split('|', Qt::SkipEmptyParts);

        notificationsMap.insert(clientId, notifications);
    }
    file.close();
    return notificationsMap;
}

void FileManager::saveNotificationsToFile(const QMap<QString, QStringList> &notificationsMap)
{
    QFile file;
    QStringList paths = {":/files/notifications.txt",
                         "qrc:/files/notifications.txt",
                         "E:/Project/notifications.txt",
                         "Y:/Final Project/notifications.txt",
                         "Y:/Project/notifications.txt",
                         "C:/Users/ASUS/Documents/Project_master/notifications.txt",
                         "D:/Project/notifications.txt",
                         "notifications.txt"};

    if (!tryOpenFile(file, paths, QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open notifications file for writing in any path.";
        return;
    }

    QTextStream out(&file);
    for (auto it = notificationsMap.begin(); it != notificationsMap.end(); ++it) {
        const QString &clientId = it.key();
        const QStringList &notifications = it.value();

        out << clientId << "," << notifications.join('|') << "\n";
    }
    file.close();
}

// Update the save and load functions
void FileManager::save(const QMap<QString, User> &usersMap,
                       const QMap<int, Court> &courtsMap,
                       const QMap<QString, training> &trainingsMap,
                       const QMap<QString, QStringList> &notificationsMap)
{
    saveUsersToFile(usersMap);
    saveCourtsToFile(courtsMap);
    saveTrainingsToFile(trainingsMap);
    saveNotificationsToFile(notificationsMap);
}

void FileManager::load(QMap<QString, User> &usersMap,
                       QMap<int, Court> &courtsMap,
                       QMap<QString, training> &trainingsMap,
                       QMap<QString, QStringList> &notificationsMap)
{
    usersMap = loadUsersFromFile();
    courtsMap = loadCourtsFromFile();
    trainingsMap = loadTrainingsFromFile();
    notificationsMap = loadNotificationsFromFile();
}
