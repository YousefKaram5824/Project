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

bool isclient = 0;
int type=0;
void Register::on_userTypeComboBox_currentIndexChanged()
{
    QString userType = ui->userTypeComboBox->currentText();

    if (userType == "Client") {
        ui->birthDateEdit->setEnabled(true);
        ui->subscriptionPeriodSpinBox->setEnabled(true);
        isclient=1;
        type=1;
    } else {
        ui->birthDateEdit->setEnabled(false);
        ui->subscriptionPeriodSpinBox->setEnabled(false);
    }
    if (userType == "coach")
    {
        type=2;
    }
    if (userType == "Receptionist")
    {
        type=3;
    }
}
QString Register::generateUniqueID(int typee)
{
    QString prefix = "";

    if (type == 1) {
        prefix = "cu";
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
    ui->userTypeComboBox->clear();
    ui->birthDateEdit->clear();
    ui->subscriptionPeriodSpinBox->clear();

}

void Register::on_pushButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString id = generateUniqueID(type);
    QString password = ui->passwordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();
    QString userType = ui->userTypeComboBox->currentText();
    QString birthDateString;
    QString subscriptionPeriodString;
    if (isclient == 1) {
        birthDateString = ui->birthDateEdit->date().toString("yyyy-MM-dd");
        subscriptionPeriodString = QString::number(ui->subscriptionPeriodSpinBox->value());
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

    usersMap.insert(id, newUser);
    /*
    qDebug() << "UsersMap contains:";
    for (auto user : usersMap) {
        qDebug() << "Username:" << user.username << ", ID:" << user.id;
    }
*/
    clearAll();

    QString message = QString("User registered successfully!\nYour ID is: %1").arg(id);
    QMessageBox::information(this, "Success",message);
}
