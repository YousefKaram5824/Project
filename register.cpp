#include "register.h"
#include "ui_register.h"
#include "User.h"
#include <QMessageBox>

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

bool isclient=0;

void Register::on_userTypeComboBox_currentIndexChanged()
{
    QString userType = ui->userTypeComboBox->currentText();

    if (userType == "Client") {
       ui->birthDateEdit->setEnabled(true);
        ui->subscriptionPeriodSpinBox->setEnabled(true);
       isclient=1;
    } else {
        ui->birthDateEdit->setEnabled(false);
        ui->subscriptionPeriodSpinBox->setEnabled(false);
    }

}

void Register::on_pushButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString id = ui->idLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();
    QString userType = ui->userTypeComboBox->currentText();
    QString birthDateString;
    QString subscriptionPeriodString;
    if(isclient==1)
    {
       birthDateString = ui->birthDateEdit->date().toString("yyyy-MM-dd");
       subscriptionPeriodString = QString::number(ui->subscriptionPeriodSpinBox->value());
    }
    else
    {
        birthDateString="null";
        subscriptionPeriodString="null";
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Error", "Passwords do not match!");
        return;
    }

    if (username.isEmpty() || id.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all required fields.");
        return;
    }

    if (usersMap.contains(id)) {

        QMessageBox::warning(this, "ID Exists", "This ID is already registered. Please choose a different one.");
        return;
    }

    User newUser;
    newUser.username = username;
    newUser.id = id;
    newUser.password = password;
    newUser.isClient = isclient;
    newUser.birthDate = birthDateString;
    newUser.subscriptionPeriod = subscriptionPeriodString;

    usersMap.insert(id, newUser);
/*
    qDebug() << "UsersMap contains:";
    for (auto user : usersMap) {
        qDebug() << "Username:" << user.username << ", ID:" << user.id;
    }
*/
    QMessageBox::information(this, "Success", "User registered successfully!");
}
