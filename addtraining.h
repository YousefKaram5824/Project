#ifndef ADDTRAINING_H
#define ADDTRAINING_H

#include <QDialog>
#include"training.h"
namespace Ui {
class addTraining;
}

class addTraining : public QDialog
{
    Q_OBJECT

public:
    explicit addTraining(QWidget *parent = nullptr);
    ~addTraining();

private:
    Ui::addTraining *ui;
};

#endif // ADDTRAINING_H
