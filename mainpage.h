#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>
#include "register.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainPage;
}
QT_END_NAMESPACE

enum class UserType { Client, Coach, Receptionist, Manager, Invalid };

class MainPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainPage(QMap<QString, User> &usersMapRef, QWidget *parent = nullptr);
    ~MainPage();

private slots:
    void on_getStarted_clicked();


    void on_login_clicked();

    void on_logOut_clicked();

    void on_logOut_2_clicked();

    void on_logOut_4_clicked();

    void on_logOut_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainPage *ui;
    Register *registerWin;
    bool validateLogin(const QString &id, const QString &password);
    void clearAll();
    UserType getUserType(const QString &username);
    QMap<QString, User> &usersMap;
};
#endif
