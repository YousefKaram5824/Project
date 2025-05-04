#ifndef NOTIFICATIONWINDOW_H
#define NOTIFICATIONWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "Notification.h"
#include "NotificationManager.h"

namespace Ui {
class NotificationWindow;
}

class NotificationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NotificationWindow(NotificationManager *notificationManager, const QString &userId, QWidget *parent = nullptr);
    ~NotificationWindow();

private slots:
    void updateNotifications();
    void handleNewNotification(const Notification &notification);
    void markAsRead(const QString &notificationId);

private:
    Ui::NotificationWindow *ui;
    NotificationManager *notificationManager;
    QString userId;
    QVBoxLayout *notificationLayout;
    QMap<QString, QWidget*> notificationWidgets;
    void createNotificationWidget(const Notification &notification);
};

#endif // NOTIFICATIONWINDOW_H 