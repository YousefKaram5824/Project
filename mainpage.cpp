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
    /*
    searchManager = new SearchManager(ui->courtTable,
                                    ui->comboBoxcourt,
                                    ui->datecourt,
                                    ui->timecourt,
                                    this);
*/
    loginManager = new Login(usersMap, this);
    connect(loginManager, &Login::loginSuccessful, this, &MainPage::handleLoginSuccessful);
    connect(loginManager, &Login::loginFailed, this, &MainPage::handleLoginFailed);

    receptionistManager = new Receptionist(usersMap, this);
    connect(receptionistManager, &Receptionist::clientNotFound, this, &MainPage::handleClientNotFound);
    connect(receptionistManager,
            &Receptionist::invalidClientType,
            this,
            &MainPage::handleInvalidClientType);
}

MainPage::~MainPage()
{
    delete ui;
    delete registerWin;
    // delete searchManager;
    delete loginManager;
    delete receptionistManager;
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

void MainPage::on_login_clicked()
{
    QString username = ui->id->text();
    QString password = ui->password->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Please enter both username and password");
        return;
    }

    loginManager->validateLogin(username, password);
}

void MainPage::handleLoginSuccessful(UserType userType)
{
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
        break;
    }
    loginManager->clearLoginFields(ui->id, ui->password);
}

void MainPage::handleLoginFailed(const QString &message)
{
    QMessageBox::warning(this, "Login Failed", message);
    loginManager->clearLoginFields(ui->id, ui->password);
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

void MainPage::on_searchButton_clicked()
{
    ui->holder->setCurrentIndex(6);
}

void MainPage::on_goHomeButton1_clicked()
{
    ui->holder->setCurrentIndex(2);
}

void MainPage::on_backToRes_clicked()
{
    ui->holder->setCurrentIndex(4);
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

    if (receptionistManager->validateClient(clientId)) {
        const User &client = usersMap[clientId];
        receptionistManager->displayClientInfo(client,
                                               ui->getClientName,
                                               ui->getClientDateOfBirth,
                                               ui->getSubscriptionPeriod);
    }
}

void MainPage::on_search_2_clicked()
{
    QString location = ui->comboBoxcourt->currentText();
    QDate date = ui->datecourt->date();
    QTime time = ui->timecourt->time();

    // searchManager->searchCourts(location, date, time);
}

void MainPage::handleClientNotFound(const QString &message)
{
    QMessageBox::warning(this, "Error", message);
}

void MainPage::handleInvalidClientType(const QString &message)
{
    QMessageBox::warning(this, "Error", message);
}
