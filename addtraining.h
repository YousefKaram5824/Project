#ifndef ADDTRAINING_H
#define ADDTRAINING_H

#include <QDialog>
#include "User.h"
#include "training.h"
namespace Ui {
class addTraining;
}

class addTraining : public QDialog
{
    Q_OBJECT

public:
    explicit addTraining(QMap<QString, training> &trainingsMapRef,
                         QMap<QString, User> &usersMapRef,
                         QWidget *parent = nullptr);
    ~addTraining();

private slots:
    void on_pushButton_3_clicked();
    void loadTrainingData(const QString &trainingName);
    void on_DeletepushButton_clicked();

private:
    Ui::addTraining *ui;
    QMap<QString, training> &trainingsMap;
    QMap<QString, User> &usersMap;
    void populateCoachesComboBox();
};

#endif // ADDTRAINING_H
