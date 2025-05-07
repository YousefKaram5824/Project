#include "register.h"
#include <QMessageBox>
#include "User.h"
#include "ui_register.h"

Register::Register(QMap<QString, User> &usersMapRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Register)
    , usersMap(usersMapRef)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

bool isclient = false;
int type = 0;

void Register::on_userTypeComboBox_currentIndexChanged()
{
    QString userType = ui->userTypeComboBox->currentText();
    ui->birthDateEdit->setEnabled(false);
    ui->subscriptionPeriodComboBox->setEnabled(false);
    if (userType == "Client") {
        ui->birthDateEdit->setEnabled(true);
        ui->subscriptionPeriodComboBox->setEnabled(true);
        isclient = true;
        type = 1;
    } else if (userType == "Coach") {
        type = 2;
    } else if (userType == "Receptionist") {
        type = 3;
    }
}
QString Register::generateUniqueID()
{
    QString prefix = "";

    if (type == 1) {
        prefix = "cl";
    } else if (type == 2) {
        prefix = "co";
    } else if (type == 3) {
        prefix = "re";
    }
    int randomNumber = rand() % 10000;
    QString randomString = QString::number(randomNumber);
    return prefix + randomString;
}

void Register::clearAll()
{
    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->confirmPasswordLineEdit->clear();
    ui->userTypeComboBox->setCurrentIndex(-1);
    ui->birthDateEdit->clear();
    ui->subscriptionPeriodComboBox->setCurrentIndex(-1);
}

void Register::on_pushButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString id = generateUniqueID();
    QString password = ui->passwordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();
    QString birthDateString;
    QString subscriptionPeriodString;
    int budget = 0;

    if (isclient) {
        if (ui->subscriptionPeriodComboBox->currentIndex() == -1) {
            QMessageBox::warning(this, "Error", "Subscription Period not selected!");
            return;
        }
        birthDateString = ui->birthDateEdit->date().toString("yyyy-MM-dd");
        QString selectedPeriod = ui->subscriptionPeriodComboBox->currentText();
        if (selectedPeriod == "Monthly") {
            subscriptionPeriodString = "1";
        } else if (selectedPeriod == "3 Months") {
            subscriptionPeriodString = "3";
        } else if (selectedPeriod == "6 Months") {
            subscriptionPeriodString = "6";
        } else if (selectedPeriod == "Yearly") {
            subscriptionPeriodString = "12";
        }
    } else {
        birthDateString = "null";
        subscriptionPeriodString = "null";
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Error", "Passwords do not match!");
        return;
    }

    if (username.isEmpty() || id.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all required fields.");
        return;
    }

    User newUser;
    newUser.username = username;
    newUser.id = id;
    newUser.password = password;
    newUser.isClient = isclient;
    newUser.birthDate = birthDateString;
    newUser.subscriptionPeriod = subscriptionPeriodString;
    newUser.budget = budget;

    usersMap.insert(id, newUser);
    clearAll();

    QString message = QString("User registered successfully!\nYour ID is: %1").arg(id);
    QMessageBox::information(this, "Success", message);
}
