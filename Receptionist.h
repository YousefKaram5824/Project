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
    explicit Receptionist(QMap<QString, User> &usersMapRef, QObject *parent = nullptr);
    ~Receptionist();

    bool validateClient(const QString &clientId);
    void displayClientInfo(const User &client,
                           QLabel *nameLabel,
                           QLabel *birthDateLabel,
                           QLabel *subscriptionLabel,
                           QLabel *budgetLabel);
    QString getClientInfo(const QString &clientId);

signals:
    void clientNotFound(const QString &message);
    void invalidClientType(const QString &message);

private:
    QMap<QString, User> &usersMap;
};

#endif // RECEPTIONIST_H
