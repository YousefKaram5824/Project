#include "NotificationManager.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QRandomGenerator>

NotificationManager::NotificationManager(QMap<QString, User> &usersMapRef, QObject *parent)
    : QObject(parent)
    , usersMap(usersMapRef)
{
    loadNotifications();
}

NotificationManager::~NotificationManager()
{
    saveNotifications();
}

QString NotificationManager::generateNotificationId()
{
    return QString("notif_%1").arg(QRandomGenerator::global()->generate());
}

void NotificationManager::sendNotification(const QString &senderId, const QString &receiverId, NotificationType type, const QString &message)
{
    if (!usersMap.contains(senderId) || !usersMap.contains(receiverId)) {
        return;
    }

    Notification notification;
    notification.id = generateNotificationId();
    notification.senderId = senderId;
    notification.receiverId = receiverId;
    notification.type = type;
    notification.message = message;
    notification.timestamp = QDateTime::currentDateTime();
    notification.isRead = false;

    notifications.insert(notification.id, notification);
    emit newNotification(notification);
    saveNotifications();
}

QList<Notification> NotificationManager::getNotifications(const QString &userId)
{
    QList<Notification> userNotifications;
    for (const auto &notification : notifications) {
        if (notification.receiverId == userId) {
            userNotifications.append(notification);
        }
    }
    return userNotifications;
}

void NotificationManager::markAsRead(const QString &notificationId)
{
    if (notifications.contains(notificationId)) {
        notifications[notificationId].isRead = true;
        emit notificationRead(notificationId);
        saveNotifications();
    }
}

void NotificationManager::saveNotifications()
{
    QFile file("Y:/Final Project/notifications.txt");
    //"E:/project/notifications.txt" for habiba
    //"Y:/Final Project/notifications.txt" for keko
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing.";
        return;
    }

    QTextStream out(&file);
    for (const auto &notification : notifications) {
        out << notification.id << ","
            << notification.senderId << ","
            << notification.receiverId << ","
            << static_cast<int>(notification.type) << ","
            << notification.message << ","
            << notification.timestamp.toString(Qt::ISODate) << ","
            << notification.isRead << "\n";
    }
    file.close();
}

void NotificationManager::loadNotifications()
{
    QFile file("Y:/Final Project/notifications.txt");
    //"E:/project/notifications.txt" for habiba
    //"Y:/Final Project/notifications.txt" for keko
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing.";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() != 7) continue;

        Notification notification;
        notification.id = parts[0];
        notification.senderId = parts[1];
        notification.receiverId = parts[2];
        notification.type = static_cast<NotificationType>(parts[3].toInt());
        notification.message = parts[4];
        notification.timestamp = QDateTime::fromString(parts[5], Qt::ISODate);
        notification.isRead = (parts[6] == "1");

        notifications.insert(notification.id, notification);
    }
    file.close();
}
