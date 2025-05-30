#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QDialog>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QProgressBar>
#include <QWidget>
#include "Receptionist.h"
#include "SearchManager.h"
#include "addtraining.h"
#include "bookcourt.h"
#include "court.h"
#include "gettraining.h"
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
    explicit MainPage(QMap<QString, User> &usersMapRef,
                      QMap<int, Court> &courtsMapRef,
                      QMap<QString, training> &trainingsMapRef,
                      QMap<QString, QStringList> &notificationsMapRef,
                      QWidget *parent = nullptr);

    ~MainPage();

private slots:
    void on_getStarted_clicked();
    void on_login_clicked();
    void on_logOut_2_clicked();
    void on_logOut_4_clicked();
    void on_logOut_3_clicked();
    void on_pushButton_clicked();
    void on_searchButton_clicked();
    void on_getClientData_clicked();
    void handleLoginSuccessful(UserType userType);
    void handleLoginFailed(const QString &message);
    void handleClientNotFound(const QString &message);
    void handleInvalidClientType(const QString &message);
    void on_search_2_clicked();
    void on_filter_clicked();
    void on_search_3_clicked();
    void on_profile_clicked();
    void on_commandLinkButton_clicked();
    void on_add_training_2_clicked();
    void on_trainings_currentTextChanged(const QString &trainingName);
    void on_backToClientPage_clicked();
    void on_trainingButton_clicked();
    void on_backToClient_clicked();
    void on_search_4_clicked();
    void on_getTrainingbtn_clicked();
    void on_beattended_clicked();
    void on_logoutFromRes_clicked();

    void on_periods_currentTextChanged(const QString &arg1);

    void on_changeVIP_clicked();

    void on_setSubPeriod_clicked();
    void onCancelTraining(const QString &trainingName);

private:
    Ui::MainPage *ui;
    Register *registerWin;
    BookCourt *bookCourt;
    addTraining *addtraining;
    SearchManager *searchManager;
    Login *loginManager;
    GetTraining *gettraining;
    Receptionist *receptionistManager;
    void clearAll();
    UserType getUserType(const QString &username);
    QMap<QString, User> &usersMap;
    QMap<int, Court> &courtsMap;
    QMap<QString, training> &trainingsMap;
    QMap<QString, QStringList> &notificationsMap;
    void displayCourtsInTable(const QList<Court> &courts);
    void createEmptyTableWidget();
    void refreshCourtTable();
    void populateCoachTrainings();
    QHBoxLayout *trainingButtonsLayout;
};

#endif
