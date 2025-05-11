#ifndef GETTRAINING_H
#define GETTRAINING_H

#include <QDialog>

namespace Ui {
class GetTraining;
}

class GetTraining : public QDialog
{
    Q_OBJECT

public:
    explicit GetTraining(QWidget *parent = nullptr);
    ~GetTraining();

private:
    Ui::GetTraining *ui;
};

#endif // GETTRAINING_H
