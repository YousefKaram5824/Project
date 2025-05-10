#ifndef BOOKCOURT_H
#define BOOKCOURT_H

#include <QDialog>
#include "Court.h"
#include "login.h"

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
    void setCurrentUserId(const QString &userId) { currentUserId = userId; }

private slots:
    void on_Book_clicked();

private:
    Ui::BookCourt *ui;
    void bookSelectedCourt(QMap<int, Court> &courtMap);
    QMap<int, Court> *courtMap;
    QString currentUserId;
signals:
    void courtBooked();
};

#endif // BOOKCOURT_H
