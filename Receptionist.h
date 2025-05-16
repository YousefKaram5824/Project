#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

#include <QLabel>
#include <QMap>
#include <QMessageBox>
#include <QObject>
#include "User.h"

class Receptionist : public QObject
{
    Q_OBJECT

public:
    explicit Receptionist(QMap<QString, User> &usersMapRef,
                          QMap<QString, QStringList> &NotificationsMapRef,
                          QObject *parent = nullptr);
    ~Receptionist();

    bool validateClient(const QString &clientId);
    void displayClientInfo(const User &client,
                           QLabel *nameLabel,
                           QLabel *birthDateLabel,
                           QLabel *subPeriodLabel);
    QString getClientInfo(const QString &clientId);
    void checkSubscriptionStatusForUser(const QString &userId);

signals:
    void clientNotFound(const QString &message);
    void invalidClientType(const QString &message);

private:
    QMap<QString, User> &usersMap;
    QMap<QString, QStringList> &NotificationsMap;
};

#endif // RECEPTIONIST_H
