#include "NotificationWindow.h"
#include "ui_NotificationWindow.h"
#include <QDateTime>
#include <QMessageBox>

NotificationWindow::NotificationWindow(NotificationManager *notificationManager, const QString &userId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NotificationWindow)
    , notificationManager(notificationManager)
    , userId(userId)
{
    ui->setupUi(this);
    notificationLayout = ui->notificationLayout;

    connect(notificationManager, &NotificationManager::newNotification,
            this, &NotificationWindow::handleNewNotification);

    updateNotifications();
}

NotificationWindow::~NotificationWindow()
{
    delete ui;
}

void NotificationWindow::updateNotifications()
{
    // Clear existing widgets
    for (auto widget : notificationWidgets) {
        notificationLayout->removeWidget(widget);
        delete widget;
    }
    notificationWidgets.clear();

    // Add new notifications
    QList<Notification> notifications = notificationManager->getNotifications(userId);
    for (const auto &notification : notifications) {
        createNotificationWidget(notification);
    }
}

void NotificationWindow::handleNewNotification(const Notification &notification)
{
    if (notification.receiverId == userId) {
        createNotificationWidget(notification);
    }
}

void NotificationWindow::createNotificationWidget(const Notification &notification)
{
    QWidget *notificationWidget = new QWidget(this);
    QVBoxLayout *widgetLayout = new QVBoxLayout(notificationWidget);
    widgetLayout->setSpacing(5);

    // Create message label
    QLabel *messageLabel = new QLabel(notification.message, notificationWidget);
    messageLabel->setWordWrap(true);
    messageLabel->setStyleSheet("color: white;");

    // Create timestamp label
    QLabel *timestampLabel = new QLabel(notification.timestamp.toString("yyyy-MM-dd hh:mm:ss"), notificationWidget);
    timestampLabel->setStyleSheet("color: #888888; font-size: 10px;");

    // Create mark as read button
    QPushButton *markAsReadButton = new QPushButton("Mark as Read", notificationWidget);
    markAsReadButton->setStyleSheet(
        "QPushButton {"
        "    background: transparent;"
        "    border: 1px solid #DC3E22;"
        "    border-radius: 3px;"
        "    color: white;"
        "    padding: 2px 5px;"
        "}"
        "QPushButton:hover {"
        "    background: rgba(220, 62, 34, 0.1);"
        "}"
    );

    connect(markAsReadButton, &QPushButton::clicked, [this, notification]() {
        markAsRead(notification.id);
    });

    // Add widgets to layout
    widgetLayout->addWidget(messageLabel);
    widgetLayout->addWidget(timestampLabel);
    widgetLayout->addWidget(markAsReadButton);

    // Set notification widget style
    notificationWidget->setStyleSheet(
        "QWidget {"
        "    background: rgba(0, 0, 0, 0.2);"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "}"
    );

    // Add to main layout
    notificationLayout->addWidget(notificationWidget);
    notificationWidgets.insert(notification.id, notificationWidget);
}

void NotificationWindow::markAsRead(const QString &notificationId)
{
    notificationManager->markAsRead(notificationId);
    updateNotifications();
} 