#ifndef ADDTRAINING_H
#define ADDTRAINING_H

#include <QDialog>
#include "training.h"
namespace Ui {
class addTraining;
}

class addTraining : public QDialog
{
    Q_OBJECT

public:
    explicit addTraining(QMap<QString, training> &trainingsMapRef, QWidget *parent = nullptr);
    ~addTraining();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::addTraining *ui;
    QMap<QString, training> &trainingsMap;
};

#endif // ADDTRAINING_H
