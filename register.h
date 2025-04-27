#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QMainWindow>
#include <QMap>
#include "User.h"

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QMap<QString, User> &usersMapRef, QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_userTypeComboBox_currentIndexChanged();
    void on_pushButton_clicked();

private:
    Ui::Register *ui;
    QMap<QString, User> &usersMap;
    bool isclient = false;
    QString generateUniqueID(int typee);
    void clearAll();
};

#endif // REGISTER_H
