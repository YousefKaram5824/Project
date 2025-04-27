#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QMainWindow>
#include "User.h"
#include <QMap>

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
    void on_userTypeComboBox_currentIndexChanged(int index);
    void on_pushButton_clicked();

private:
    Ui::Register *ui;
    QMap<QString, User> &usersMap; // <<< هنا أهم حاجة نضيف المرجع
    bool isclient = false;
};

#endif // REGISTER_H
