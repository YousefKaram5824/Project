#include "login.h"
#include <QLineEdit>

// Initialize static member
QString Login::currentUserId;

Login::Login(QMap<QString, User> &usersMapRef, QObject *parent)
    : QObject(parent)
    , usersMap(usersMapRef)
{}

Login::~Login() {}

UserType Login::getUserType(const QString &username)
{
    if (username.length() < 2) {
        return UserType::Invalid;
    }

    QString prefix = username.left(2).toLower();

    if (prefix == "cl") {
        return UserType::Client;
    } else if (prefix == "co") {
        return UserType::Coach;
    } else if (prefix == "re") {
        return UserType::Receptionist;
    } else if (prefix == "ad") {
        return UserType::Manager;
    }

    return UserType::Invalid;
}

bool Login::validateLogin(const QString &id, const QString &password)
{
    if (!usersMap.contains(id)) {
        emit loginFailed("User ID not found.");
        return false;
    }

    const User &user = usersMap[id];
    if (user.password != password) {
        emit loginFailed("Incorrect password.");
        return false;
    }

    UserType userType = getUserType(id);
    if (userType == UserType::Invalid) {
        emit loginFailed("Invalid user role.");
        return false;
    }

    // Set the current user ID upon successful login
    setCurrentUserId(id);
    emit loginSuccessful(userType);
    return true;
}

void Login::clearLoginFields(QLineEdit *idField, QLineEdit *passwordField)
{
    if (idField)
        idField->clear();
    if (passwordField)
        passwordField->clear();
}

bool Login::isCurrentUserVIP() const
{
    if (!usersMap.contains(currentUserId))
    {
        return false;
    }
    const User &user = usersMap[currentUserId];
    return user.isVIP;
}
