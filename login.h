#ifndef LOGIN_H
#define LOGIN_H

#include <QLineEdit>
#include <QMap>
#include <QMessageBox>
#include <QObject>
#include "User.h"

enum class UserType { Client, Coach, Receptionist, Manager, Invalid };

class Login : public QObject
{
    Q_OBJECT

public:
    explicit Login(QMap<QString, User> &usersMapRef,
                   QMap<QString, QStringList> &NotificationsMapRef,
                   QObject *parent = nullptr);
    ~Login();

    bool validateLogin(const QString &id, const QString &password);
    UserType getUserType(const QString &username);
    void clearLoginFields(QLineEdit *idField, QLineEdit *passwordField);

    // Static methods to access current user
    static QString getCurrentUserId() { return currentUserId; }
    static void setCurrentUserId(const QString &id) { currentUserId = id; }
    static void clearCurrentUserId() { currentUserId.clear(); }
    bool isCurrentUserVIP() const;

signals:
    void loginSuccessful(UserType userType);
    void loginFailed(const QString &message);

private:
    QMap<QString, User> &usersMap;
    static QString currentUserId; // Static member to store current user's ID
    QMap<QString, QStringList> &NotificationsMap;
};

#endif // LOGIN_H
