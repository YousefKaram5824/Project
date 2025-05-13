#include "gettraining.h"
#include <QMessageBox>
#include "ui_gettraining.h"

GetTraining::GetTraining(QMap<QString, training> &trainingsRef,
                         QMap<QString, User> &usersRef,
                         QString currentUserId,
                         QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GetTraining)
    , trainingsMap(trainingsRef)
    , usersMap(usersRef)
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

    //int userIdInt = currentLoggedInUserId.toInt(); // Convert to int

    if (currentTraining.users.contains(currentLoggedInUserId)) {
        QMessageBox::warning(this, "Error", "You are already enrolled in this training.");
        return;
    }
    qDebug() << "Current Trainings Map:";
    for (auto it = trainingsMap.begin(); it != trainingsMap.end(); ++it) {
        qDebug() << "Training ID:" << it.key() << "Capacity:" << it.value().capacity
                 << "Current Users:" << it.value().users.keys();
    }
    if (currentTraining.capacity > currentTraining.users.size()) {
        if (usersMap.contains(currentLoggedInUserId)) {
            User user = usersMap[currentLoggedInUserId];
            currentTraining.users[currentLoggedInUserId] = user;
            QMessageBox::information(this,
                                     "Success",
                                     "Successfully enrolled in '" + trainingName + "'.");
            currentTraining.capacity--;
        } else {
            QMessageBox::critical(this, "Error", "Current user data not found.");
        }
    } else {
        if (usersMap.contains(currentLoggedInUserId)) {
            User user = usersMap[currentLoggedInUserId];
            // ⭐ VIP Check
            if (user.isVIP) {
                currentTraining.VIP_waiting_list.enqueue(user);
                QMessageBox::information(this, "Added to VIP Waiting List",
                                         "This training is full. As a VIP, you've been added to the VIP waiting list.");
            } else {
                currentTraining.waiting_list.enqueue(user);
                QMessageBox::information(this, "Added to Waiting List",
                                         "This training is full. You've been added to the waiting list.");
            }
        } else {
            QMessageBox::critical(this, "Error", "Current user data not found.");
        }
    }

    qDebug() << "Updated Trainings Map:";
    for (auto it = trainingsMap.begin(); it != trainingsMap.end(); ++it) {
        qDebug() << "Training ID:" << it.key()
        << "Capacity:" << it.value().capacity
        << "Current Users:" << it.value().users.keys();
    }

    close();
}
