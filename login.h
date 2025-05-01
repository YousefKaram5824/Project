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
    explicit Login(QMap<QString, User> &usersMapRef, QObject *parent = nullptr);
    ~Login();

    bool validateLogin(const QString &id, const QString &password);
    UserType getUserType(const QString &username);
    void clearLoginFields(QLineEdit *idField, QLineEdit *passwordField);

signals:
    void loginSuccessful(UserType userType);
    void loginFailed(const QString &message);

private:
    QMap<QString, User> &usersMap;
};

#endif // LOGIN_H 
