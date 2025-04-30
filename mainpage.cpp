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

    // Initialize SearchManager
    searchManager = new SearchManager(ui->courtTable,
                                    ui->comboBoxcourt,
                                    ui->datecourt,
                                    ui->timecourt,
                                    this);
}

MainPage::~MainPage()
{
    delete ui;
    delete registerWin;
    delete searchManager;
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

void MainPage::on_pushButton_clicked()
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

void MainPage::on_searchButton_clicked()
{
    ui->holder->setCurrentIndex(3);
}

void MainPage::on_goHomeButton1_clicked()
{
    ui->holder->setCurrentIndex(2);
}

void MainPage::on_backToRes_clicked()
{
    ui->holder->setCurrentIndex(5);
}

void MainPage::on_clientData_clicked()
{
    ui->holder->setCurrentIndex(7);
}

void MainPage::on_getClientData_clicked()
{
    QString clientId = ui->clientID->text();
    
    if (clientId.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a client ID");
        return;
    }

    if (!usersMap.contains(clientId)) {
        QMessageBox::warning(this, "Error", "Client ID not found");
        return;
    }

    const User &client = usersMap[clientId];
    if (!client.isClient) {
        QMessageBox::warning(this, "Error", "The entered ID does not belong to a client");
        return;
    }

    ui->getClientName->setText(client.username);
    ui->getClientDateOfBirth->setText(client.birthDate);
    ui->getSubscriptionPeriod->setText(client.subscriptionPeriod);
}

void MainPage::on_search_2_clicked()
{
    QString location = ui->comboBoxcourt->currentText();
    QDate date = ui->datecourt->date();
    QTime time = ui->timecourt->time();

    searchManager->searchCourts(location, date, time);
}
