#ifndef BOOKCOURT_H
#define BOOKCOURT_H

#include <QDialog>
#include"Court.h"
namespace Ui {
class BookCourt;
}

class BookCourt : public QDialog
{
    Q_OBJECT

public:
    explicit BookCourt(QWidget *parent = nullptr);
    ~BookCourt();
    void setCourtMap(QMap<int, Court> &map);

private slots:
    void on_Book_clicked();

private:
    Ui::BookCourt *ui;
    void bookSelectedCourt(QMap<int, Court> &courtMap);
    QMap<int, Court> *courtMap;
signals:
    void courtBooked();
};

#endif // BOOKCOURT_H
