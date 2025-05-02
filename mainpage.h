#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>
#include "Receptionist.h"
#include "SearchManager.h"
#include "bookcourt.h"
#include "court.h"
#include "login.h"
#include "register.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainPage;
}
QT_END_NAMESPACE

class MainPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainPage(QMap<QString, User>& usersMapRef, QMap<int, Court>& courtsMapRef, QWidget *parent = nullptr);

    ~MainPage();

private slots:
    void on_getStarted_clicked();
    void on_login_clicked();
    void on_logOut_clicked();
    void on_logOut_2_clicked();
    void on_logOut_4_clicked();
    void on_logOut_3_clicked();
    void on_pushButton_clicked();
    void on_searchButton_clicked();
    void on_goHomeButton1_clicked();
    void on_backToRes_clicked();
    void on_clientData_clicked();
    void on_getClientData_clicked();
   // void on_search_2_clicked();

    // Login slots
    void handleLoginSuccessful(UserType userType);
    void handleLoginFailed(const QString &message);

    // Receptionist slots
    void handleClientNotFound(const QString &message);
    void handleInvalidClientType(const QString &message);

    void on_search_2_clicked();



    void on_filter_clicked();

    void on_search_3_clicked();

private:
    Ui::MainPage *ui;
    Register *registerWin;
    BookCourt *bookCourt;
    SearchManager *searchManager;
    Login *loginManager;
    Receptionist *receptionistManager;
    void clearAll();
    UserType getUserType(const QString &username);
    QMap<QString, User> &usersMap;
    QMap<int, Court>& courtsMap;
    void displayCourtsInTable(const QList<Court>& courts);

    void createEmptyTableWidget();
};

#endif
