#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include "register.h"

//Habiba
QT_BEGIN_NAMESPACE
namespace Ui {
class MainPage;
}
QT_END_NAMESPACE

enum class UserType { Customer, Coach, Receptionist, Manager, Invalid };

class MainPage : public QMainWindow
{
    Q_OBJECT

public:
    MainPage(QWidget *parent = nullptr);
    ~MainPage();

private slots:
    void on_getStarted_clicked();

    void on_register_2_clicked();

    void on_login_clicked();

    void on_logOut_clicked();

    void on_logOut_2_clicked();

    void on_logOut_4_clicked();

    void on_logOut_3_clicked();

private:
    Ui::MainPage *ui;
    Register *registerWin;
    bool validateLogin(const QString &username, const QString &password);
    UserType getUserType(const QString &username);
};
#endif // MAINPAGE_H
