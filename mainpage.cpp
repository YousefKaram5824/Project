#include "mainpage.h"
#include <QMessageBox>
#include "ui_mainpage.h"

MainPage::MainPage(QMap<QString, User> &usersMapRef, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainPage)
    , usersMap(usersMapRef)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
}

MainPage::~MainPage()
{
    delete ui;
    delete registerWin;
}

UserType MainPage::getUserType(const QString &username)
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

void MainPage::on_getStarted_clicked()
{
    ui->holder->setCurrentIndex(1);
}

void MainPage::on_register_2_clicked()
{
    registerWin = new Register(usersMap, this);
    registerWin->show();
    registerWin->raise();
    registerWin->activateWindow();
}

bool MainPage::validateLogin(const QString &id, const QString &password)
{
    if (!usersMap.contains(id)) {
        QMessageBox::warning(this, "Login Failed", "User ID not found.");
        return false;
    }

    const User &user = usersMap[id];
    if (user.password != password) {
        QMessageBox::warning(this, "Login Failed", "Incorrect password.");
        return false;
    }

    UserType userType = getUserType(id);
    if (userType == UserType::Invalid) {
        QMessageBox::warning(this, "Login Failed", "Invalid user role.");
        return false;
    }

    switch (userType) {
    case UserType::Client:
        ui->holder->setCurrentIndex(2);
        break;
    case UserType::Coach:
        ui->holder->setCurrentIndex(3);
        break;
    case UserType::Receptionist:
        ui->holder->setCurrentIndex(4);
        break;
    case UserType::Manager:
        ui->holder->setCurrentIndex(5);
        break;
    default:
        return false;
    }
    clearAll();
    return true;
}

void MainPage::on_login_clicked()
{
    QString username = ui->id->text();
    QString password = ui->password->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Please enter both username and password");
        return;
    }

    if (validateLogin(username, password)) {
    } else {
        clearAll();
    }
}

void MainPage::on_logOut_clicked()
{
    ui->holder->setCurrentIndex(1);
}

void MainPage::on_logOut_2_clicked()
{
    ui->holder->setCurrentIndex(1);
}

void MainPage::on_logOut_3_clicked()
{
    ui->holder->setCurrentIndex(1);
}

void MainPage::on_logOut_4_clicked()
{
    ui->holder->setCurrentIndex(1);
}

void MainPage::clearAll()
{
    ui->id->clear();
    ui->password->clear();
}
