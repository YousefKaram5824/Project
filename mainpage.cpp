#include "mainpage.h"
#include <QMessageBox>
#include "ui_mainpage.h"
#include <QLayout>

MainPage::MainPage(QMap<QString, User> &usersMapRef, QMap<int, Court> &courtsMapRef, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainPage)
    , usersMap(usersMapRef)
    , courtsMap(courtsMapRef)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    searchManager = new SearchManager(courtsMap);


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
    delete searchManager;
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
    //createEmptyTableWidget();
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

void MainPage::handleClientNotFound(const QString &message)
{
    QMessageBox::warning(this, "Error", message);
}

void MainPage::handleInvalidClientType(const QString &message)
{
    QMessageBox::warning(this, "Error", message);
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
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(court.isBooked ? "Yes" : "No"));
        ++row;
    }


    ui->tableWidget->resizeRowsToContents();
    int rowHeight = ui->tableWidget->verticalHeader()->defaultSectionSize();
    int totalHeight = rowHeight * courts.size() + ui->tableWidget->horizontalHeader()->height();
    ui->tableWidget->setMinimumHeight(totalHeight);
}




/*
void MainPage::createEmptyTableWidget()
{

    if (ui->tableWidget) {
        ui->tableWidget->clear();  // مسح محتويات الجدول
        ui->tableWidget->setRowCount(0);  // إعادة تعيين عدد الصفوف إلى 0
    }

    // إنشاء جدول جديد فارغ
    ui->tableWidget = new QTableWidget(this);
    ui->tableWidget->setRowCount(0);  // جدول فارغ في البداية
    ui->tableWidget->setColumnCount(6); // عدد الأعمدة

    // إضافة العناوين
    ui->tableWidget->setHorizontalHeaderLabels({"ID", "Name", "Location", "Date", "Time", "Booked"});

    // إضافة الجدول إلى الـ Layout
    QLayout *layout = ui->centralwidget->layout(); // الحصول على layout
    QWidget *oldWidget = layout->itemAt(0)->widget();
    if (oldWidget) {
        layout->removeWidget(oldWidget);
        delete oldWidget;
    }
    layout->addWidget(ui->tableWidget);

}
*/

void MainPage::on_search_2_clicked()
{
    QList<Court> courts = searchManager->searchAll();
   // qDebug() << "Number of courts:" << courts.size();
    displayCourtsInTable(courts);
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
            QMessageBox::information(this, "No courts", "No court at requested time. Showing nearest available.");
            displayCourtsInTable({closest});
        } else {
            QMessageBox::warning(this, "No courts", "No available courts found.");
        }
    }
}


