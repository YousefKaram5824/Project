#include "gettraining.h"
#include <QMessageBox>
#include "ui_gettraining.h"

GetTraining::GetTraining(QMap<QString, training> &trainingsRef,
                         QMap<QString, User> &usersRef,
                         QString currentUserId,
                         QMap<QString, QStringList> &notificationsMapRef,
                         QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GetTraining)
    , trainingsMap(trainingsRef)
    , usersMap(usersRef)
    , notificationsMap(notificationsMapRef)
    , currentLoggedInUserId(currentUserId)
{
    ui->setupUi(this);
}

GetTraining::~GetTraining()
{
    delete ui;
}

void GetTraining::on_pushButton_clicked()
{
    QString trainingName = ui->trainingId->text().trimmed();

    if (trainingName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a Training ID (Name).");
        return;
    }

    if (!trainingsMap.contains(trainingName)) {
        QMessageBox::warning(this, "Error", "Training with ID '" + trainingName + "' not found.");
        return;
    }

    if (currentLoggedInUserId.isEmpty()) {
        QMessageBox::warning(this, "Error", "No user is currently logged in.");
        return;
    }

    training &currentTraining = trainingsMap[trainingName];

    if (currentTraining.users.contains(currentLoggedInUserId)) {
        QMessageBox::warning(this, "Error", "You are already enrolled in this training.");
        return;
    }

    if (currentTraining.capacity > 0) {
        if (usersMap.contains(currentLoggedInUserId)) {
            User user = usersMap[currentLoggedInUserId];
            currentTraining.users[currentLoggedInUserId] = user;
            QMessageBox::information(this,
                                     "Success",
                                     "Successfully enrolled in '" + trainingName + "'.");
            currentTraining.capacity--;
            emit trainingAdded();
        } else {
            QMessageBox::critical(this, "Error", "Current user data not found.");
        }
    } else {
        if (usersMap.contains(currentLoggedInUserId)) {
            User user = usersMap[currentLoggedInUserId];

            if (user.isVIP) {
                bool inVIPQueue = std::any_of(currentTraining.VIP_waiting_list.begin(),
                                              currentTraining.VIP_waiting_list.end(),
                                              [&](const User &u) { return u.id == user.id; });
                if (inVIPQueue) {
                    QMessageBox::warning(this,
                                         "Already in Waiting List",
                                         "You are already in the waiting list for this training.");
                    return;
                } else {
                    currentTraining.VIP_waiting_list.enqueue(user);
                    QMessageBox::information(this,
                                             "Added to VIP Waiting List",
                                             "This training is full. As a VIP, you've been added "
                                             "to the VIP waiting list.");
                }
            } else {
                bool inNormalQueue = std::any_of(currentTraining.waiting_list.begin(),
                                                 currentTraining.waiting_list.end(),
                                                 [&](const User &u) { return u.id == user.id; });
                if (inNormalQueue) {
                    QMessageBox::warning(this,
                                         "Already in Waiting List",
                                         "You are already in the waiting list for this training.");
                    return;
                } else {
                    currentTraining.waiting_list.enqueue(user);
                    QMessageBox::information(
                        this,
                        "Added to Waiting List",
                        "This training is full. You've been added to the waiting list.");
                }
            }
        } else {
            QMessageBox::critical(this, "Error", "Current user data not found.");
        }
    }

    close();
}
