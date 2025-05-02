#ifndef BOOKCOURT_H
#define BOOKCOURT_H

#include <QDialog>

namespace Ui {
class BookCourt;
}

class BookCourt : public QDialog
{
    Q_OBJECT

public:
    explicit BookCourt(QWidget *parent = nullptr);
    ~BookCourt();

private:
    Ui::BookCourt *ui;
};

#endif // BOOKCOURT_H
