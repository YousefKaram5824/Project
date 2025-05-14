#include "mainpage.h"
#include <QLayout>
#include <QMessageBox>
#include "ui_mainpage.h"

MainPage::MainPage(QMap<QString, User> &usersMapRef,
                   QMap<int, Court> &courtsMapRef,
                   QMap<QString, training> &trainingsMapRef,
                   QMap<QString, QStringList> &notificationsMapRef,
                   QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainPage)
    , usersMap(usersMapRef)
    , courtsMap(courtsMapRef)
    , trainingsMap(trainingsMapRef)
    , notificationsMap(notificationsMapRef)

{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    searchManager = new SearchManager(courtsMap);

    loginManager = new Login(usersMap, this);
    connect(loginManager, &Login::loginSuccessful, this, &MainPage::handleLoginSuccessful);
    connect(loginManager, &Login::loginFailed, this, &MainPage::handleLoginFailed);

    receptionistManager = new Receptionist(usersMap, this);
    connect(receptionistManager,
            &Receptionist::clientNotFound,
            this,
            &MainPage::handleClientNotFound);
    connect(receptionistManager,
            &Receptionist::invalidClientType,
            this,
            &MainPage::handleInvalidClientType);
}

MainPage::~MainPage()
{
    delete ui;
    delete registerWin;
    delete bookCourt;
    delete searchManager;
    delete loginManager;
    delete receptionistManager;
    delete addtraining;
    delete gettraining;
}

void MainPage::on_pushButton_clicked()
{
    registerWin = new Register(usersMap, this);
    registerWin->show();
    registerWin->raise();
    registerWin->activateWindow();
}

void MainPage::on_search_3_clicked()
{
    bookCourt = new BookCourt();
    bookCourt->setCourtMap(this->courtsMap);
    bookCourt->setCurrentUserId(loginManager->getCurrentUserId());
    connect(bookCourt, &BookCourt::courtBooked, this, &MainPage::refreshCourtTable);
    bookCourt->show();
    bookCourt->raise();
    bookCourt->activateWindow();
}

void MainPage::on_add_training_2_clicked()
{
    addtraining = new addTraining(trainingsMap, usersMap, this);
    addtraining->show();
    addtraining->raise();
    addtraining->activateWindow();
}

void MainPage::on_getTrainingbtn_clicked()
{
    QString currentUserId = loginManager->getCurrentUserId();
    gettraining = new GetTraining(trainingsMap, usersMap, currentUserId, notificationsMap, this);
    gettraining->show();
    gettraining->raise();
    gettraining->activateWindow();
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
        ui->holder->setCurrentIndex(4);
        loginManager->getCurrentUserId();
        populateCoachTrainings();
        break;
    case UserType::Receptionist:
        ui->holder->setCurrentIndex(3);
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

void MainPage::handleClientNotFound(const QString &message)
{
    QMessageBox::warning(this, "Error", message);
}

void MainPage::handleInvalidClientType(const QString &message)
{
    QMessageBox::warning(this, "Error", message);
}

void MainPage::on_getStarted_clicked()
{
    ui->holder->setCurrentIndex(1);
}

void MainPage::on_logoutFromRes_clicked()
{
    loginManager->clearCurrentUserId();
    ui->clientID->clear();
    ui->getClientDateOfBirth->clear();
    ui->getClientName->clear();
    ui->getIsVIPData->clear();
    ui->getSubPeriod->clear();
    ui->getPriceData->clear();
    ui->holder->setCurrentIndex(1);
}

void MainPage::on_logOut_2_clicked()
{
    loginManager->clearCurrentUserId();
    ui->holder->setCurrentIndex(1);
}

void MainPage::on_logOut_3_clicked()
{
    loginManager->clearCurrentUserId();
    ui->holder->setCurrentIndex(1);
}

void MainPage::on_logOut_4_clicked()
{
    loginManager->clearCurrentUserId();
    ui->holder->setCurrentIndex(1);
}

void MainPage::on_searchButton_clicked()
{
    ui->holder->setCurrentIndex(7);
}

void MainPage::on_backToClientPage_clicked()
{
    ui->holder->setCurrentIndex(2);
    ui->trainingTableWidget->setRowCount(0);
}

void MainPage::on_trainingButton_clicked()
{
    ui->holder->setCurrentIndex(8);
}

void MainPage::on_commandLinkButton_clicked()
{
    ui->holder->setCurrentIndex(2);
}

void MainPage::on_backToClient_clicked()
{
    ui->holder->setCurrentIndex(2);
    ui->tableWidget->setRowCount(0);
}

void MainPage::refreshCourtTable()
{
    QList<Court> courtList = courtsMap.values();

    displayCourtsInTable(courtList);
}

void MainPage::on_search_2_clicked()
{
    QList<Court> courts = searchManager->searchAll();
    displayCourtsInTable(courts);
}

void MainPage::on_getClientData_clicked()
{
    QString clientId = ui->clientID->text();

    if (clientId.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a client ID");
        return;
    }

    if (clientId.length() < 2 || clientId.left(2).toLower() != "cl") {
        QMessageBox::warning(this, "Invalid Client ID", "You have to search for clients only!");
        return;
    }

    if (receptionistManager->validateClient(clientId)) {
        const User &client = usersMap[clientId];
        receptionistManager->displayClientInfo(client,
                                               ui->getClientName,
                                               ui->getClientDateOfBirth,
                                               ui->getSubPeriod);
        QString vipStatus = client.isVIP ? "Yes" : "No";
        ui->getIsVIPData->setText(vipStatus);
        on_periods_currentTextChanged(ui->periods->currentText());
    }
}

void MainPage::on_periods_currentTextChanged(const QString &period)
{
    int basePrice = 0;

    if (period == "Monthly") {
        basePrice = 200;
    } else if (period == "3 Months") {
        basePrice = 600;
    } else if (period == "6 Months") {
        basePrice = 1200;
    } else if (period == "Yearly") {
        basePrice = 2400;
    }

    QString clientId = ui->clientID->text();
    bool isVIP = false;

    if (!clientId.isEmpty() && usersMap.contains(clientId)) {
        isVIP = usersMap[clientId].isVIP;
    }

    double finalPrice = basePrice;
    if (isVIP) {
        finalPrice = basePrice * 1.10;
    }

    ui->getPriceData->setText(QString::number(finalPrice, 'f', 0) + " L.E.");
}

void MainPage::on_changeVIP_clicked()
{
    QString clientId = ui->clientID->text();

    User &client = usersMap[clientId];
    client.isVIP = !client.isVIP;

    QString notificationMessage;
    if (client.isVIP) {
        notificationMessage
            = "Congratulations! You have been upgraded to VIP status. Enjoy your premium benefits!";
    } else {
        notificationMessage = "Your VIP status has been changed to Regular membership.";
    }

    notificationsMap[clientId].append(notificationMessage);

    QString statusChange = client.isVIP ? "VIP" : "Regular";
    QMessageBox::information(this,
                             "VIP Status Changed",
                             QString("Client %1 is now a %2 member").arg(clientId).arg(statusChange));
    on_getClientData_clicked();
}

void MainPage::on_setSubPeriod_clicked()
{
    QString clientId = ui->clientID->text();

    QString selectedPeriod = ui->periods->currentText();

    if (selectedPeriod.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a subscription period first");
        return;
    }

    User &client = usersMap[clientId];
    client.subscriptionPeriod = selectedPeriod;

    QMessageBox::information(this,
                             "Subscription Period Updated",
                             QString("Client %1's subscription period has been set to %2")
                                 .arg(clientId)
                                 .arg(selectedPeriod));
    ui->periods->setCurrentIndex(-1);
    on_getClientData_clicked();
}

void MainPage::displayCourtsInTable(const QList<Court> &courts)
{
    ui->tableWidget->setRowCount(0);

    ui->tableWidget->setRowCount(courts.size());
    int row = 0;
    for (const Court &court : courts) {
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(court.id));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(court.name));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(court.location));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(court.date.toString("yyyy-MM-dd")));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(court.time.toString("HH:mm")));
        QTableWidgetItem *statusItem = new QTableWidgetItem(court.isBooked ? "Yes" : "No");

        if (court.isBooked) {
            statusItem->setForeground(Qt::red);
        }

        ui->tableWidget->setItem(row, 5, statusItem);
        ++row;
    }

    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeRowsToContents();
    int rowHeight = ui->tableWidget->verticalHeader()->defaultSectionSize();
    int totalHeight = rowHeight * courts.size() + ui->tableWidget->horizontalHeader()->height();
    ui->tableWidget->setMinimumHeight(totalHeight);
}

void MainPage::on_filter_clicked()
{
    QString location = ui->comboBoxcourt->currentText();
    QDate date = ui->datecourt->date();
    QTime time = ui->timecourt->time();

    QList<Court> filtered = searchManager->filterCourts(location, date, time);
    if (!filtered.isEmpty()) {
        displayCourtsInTable(filtered);
    } else {
        Court closest = searchManager->findClosestAvailable(location, date, time);
        if (!closest.id.isEmpty()) {
            QMessageBox::information(this,
                                     "No courts",
                                     "No court at requested time. Showing nearest available.");
            displayCourtsInTable({closest});
        } else {
            QMessageBox::warning(this, "No courts", "No available courts found.");
        }
    }
}

void MainPage::on_profile_clicked()
{
    QString currentId = loginManager->getCurrentUserId();
    ui->workoutTable->setRowCount(0);
    ui->notificationList->clear();

    if (!currentId.isEmpty() && usersMap.contains(currentId)) {
        const User &currentUser = usersMap[currentId];

        ui->getClientName_2->setText(currentUser.username);
        ui->getClientDateOfBirth_2->setText(currentUser.birthDate);
        ui->getSubscriptionPeriod_2->setText(currentUser.subscriptionPeriod);

        int row = 0;
        for (auto it = trainingsMap.begin(); it != trainingsMap.end(); ++it) {
            const training &t = it.value();
            if (t.users.contains(currentId)) {
                ui->workoutTable->setRowCount(row + 1);
                ui->workoutTable->setItem(row, 0, new QTableWidgetItem(t.name));
                QProgressBar *progressBar = new QProgressBar();
                int progress = t.userProgress.value(currentId, 0);
                progressBar->setMinimum(0);
                progressBar->setMaximum(100);
                progressBar->setValue(progress);
                progressBar->setFormat(QString::number(progress) + "%");
                ui->workoutTable->setCellWidget(row, 1, progressBar);
                row++;
            }
            ui->holder->setCurrentIndex(6);
        }
        if (notificationsMap.contains(currentId)) {
            const QStringList &userNotifications = notificationsMap[currentId];

            for (const QString &notification : userNotifications) {
                ui->notificationList->addItem(notification);
            }
        }
    } else {
        QMessageBox::warning(this, "Error", "Could not load user profile data.");
    }
}

void MainPage::populateCoachTrainings()
{
    QString currentCoachId = loginManager->getCurrentUserId();
    ui->trainings->clear();

    for (const auto &training : std::as_const(trainingsMap)) {
        if (training.assigned_coach == currentCoachId) {
            ui->trainings->addItem(training.name);
        }
    }
    ui->trainings->setCurrentIndex(-1);
    ui->DtimlineEdit->clear();
    ui->StimeEdit->clear();
}

void MainPage::on_trainings_currentTextChanged(const QString &trainingName)
{
    ui->clientId->clear();
    ui->clientsTable->setRowCount(0);
    ui->attendTable->setRowCount(0);
    if (!trainingsMap.contains(trainingName))
        return;

    const training &t = trainingsMap[trainingName];

    for (auto it = t.users.begin(); it != t.users.end(); ++it) {
        ui->clientId->addItem(it.key());
    }
    ui->clientId->setCurrentIndex(-1);
    ui->DtimlineEdit->setText(QString::number(t.duration_time));
    ui->StimeEdit->setTime(t.Stime);
    ui->clientsTable->setRowCount(t.users.size());
    int row1 = 0;
    for (auto it = t.users.begin(); it != t.users.end(); ++it) {
        const User &user = usersMap[it.key()];
        ui->clientsTable->setItem(row1, 0, new QTableWidgetItem(user.id));
        QProgressBar *progressBar = new QProgressBar();
        int progress = t.userProgress.value(user.id, 0);
        progressBar->setMinimum(0);
        progressBar->setMaximum(100);
        progressBar->setValue(progress);
        progressBar->setFormat(QString::number(progress) + "%");
        ui->clientsTable->setCellWidget(row1, 1, progressBar);
        row1++;
    }

    QList<QPair<QString, int>> clientAttendance;
    for (auto it = t.users.begin(); it != t.users.end(); ++it) {
        const QString &userId = it.key();
        int attendanceCount = t.attended.value(userId, 0);
        clientAttendance.append(qMakePair(userId, attendanceCount));
    }

    std::sort(clientAttendance.begin(),
              clientAttendance.end(),
              [](const QPair<QString, int> &a, const QPair<QString, int> &b) {
                  return a.second > b.second;
              });

    ui->attendTable->setRowCount(clientAttendance.size());
    for (int row2 = 0; row2 < clientAttendance.size(); ++row2) {
        const QString &userId = clientAttendance[row2].first;
        int attendanceCount = clientAttendance[row2].second;

        ui->attendTable->setItem(row2, 0, new QTableWidgetItem(userId));
        ui->attendTable->setItem(row2, 1, new QTableWidgetItem(QString::number(attendanceCount)));
    }
}

void MainPage::on_search_4_clicked()
{
    ui->trainingTableWidget->setRowCount(0);

    for (const auto &training : std::as_const(trainingsMap)) {
        int row = ui->trainingTableWidget->rowCount();
        ui->trainingTableWidget->insertRow(row);

        ui->trainingTableWidget->setItem(row, 1, new QTableWidgetItem(training.name));
        ui->trainingTableWidget->setItem(row,
                                         2,
                                         new QTableWidgetItem(training.Stime.toString("HH:mm")));
        ui->trainingTableWidget
            ->setItem(row, 3, new QTableWidgetItem(QString::number(training.duration_time)));

        ui->trainingTableWidget->setItem(row,
                                         4,
                                         new QTableWidgetItem(QString::number(training.capacity)));
        ui->trainingTableWidget->setItem(row, 5, new QTableWidgetItem(training.assigned_coach));
    }
}

void MainPage::on_beattended_clicked()
{
    QString currentTraining = ui->trainings->currentText();
    if (currentTraining.isEmpty()) {
        QMessageBox::warning(this, "Error", "No Training Selected");
        return;
    }

    QString clientSelected = ui->clientId->currentText();
    if (clientSelected.isEmpty()) {
        QMessageBox::warning(this, "Error", "No Clients Selected");
        return;
    }

    if (!trainingsMap.contains(currentTraining)) {
        QMessageBox::warning(this, "Error", "Training not found");
        return;
    }

    training &t = trainingsMap[currentTraining];

    int currentAttendance = t.attended.value(clientSelected, 0);
    t.attended[clientSelected] = currentAttendance + 1;

    int currentProgress = t.userProgress.value(clientSelected, 0);
    int newProgress = qMin(100, currentProgress + 2);
    t.userProgress[clientSelected] = newProgress;

    on_trainings_currentTextChanged(currentTraining);
    QMessageBox::information(this,
                             "Success",
                             QString("Attendance recorded. %1 has attended %2 times. Progress: %3%")
                                 .arg(usersMap[clientSelected].username)
                                 .arg(t.attended[clientSelected])
                                 .arg(newProgress));
}
