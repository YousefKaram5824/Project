#ifndef GETTRAINING_H
#define GETTRAINING_H

#include <QDialog>
#include "User.h"
#include "training.h"
namespace Ui {
class GetTraining;
}

class GetTraining : public QDialog
{
    Q_OBJECT

public:
    explicit GetTraining(QMap<QString, training> &trainingsRef,
                         QMap<QString, User> &usersRef,
                         QString currentUserId,
                         QMap<QString, QStringList> &notificationsMapRef,
                         QWidget *parent = nullptr);
    ~GetTraining();

public:
    Ui::GetTraining *ui;
    QMap<QString, training> &trainingsMap;
    QMap<QString, User> &usersMap;
    QMap<QString, QStringList> &notificationsMap;
    QString currentLoggedInUserId;
private slots:
    void on_pushButton_clicked();
};

#endif // GETTRAINING_H
