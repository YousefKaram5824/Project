#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QObject>
#include <QMap>
#include <QList>
#include "Notification.h"
#include "User.h"

class NotificationManager : public QObject
{
    Q_OBJECT

public:
    explicit NotificationManager(QMap<QString, User> &usersMapRef, QObject *parent = nullptr);
    ~NotificationManager();

    void sendNotification(const QString &senderId, const QString &receiverId, NotificationType type, const QString &message);
    QList<Notification> getNotifications(const QString &userId);
    void markAsRead(const QString &notificationId);
    void saveNotifications();
    void loadNotifications();

signals:
    void newNotification(const Notification &notification);
    void notificationRead(const QString &notificationId);

private:
    QMap<QString, User> &usersMap;
    QMap<QString, Notification> notifications;
    QString generateNotificationId();
};

#endif // NOTIFICATIONMANAGER_H 