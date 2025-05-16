#ifndef BOOKCOURT_H
#define BOOKCOURT_H

#include <QDialog>
#include "Court.h"

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
    void setCurrentUserId(const QString &userId);
    void setUserVIPStatus(bool isVIP) { isCurrentUserVIP = isVIP; }

private slots:
    void on_Book_clicked();
    void on_cancel_clicked();

private:
    Ui::BookCourt *ui;
    void bookSelectedCourt(QMap<int, Court> &courtMap);
    QMap<int, Court> *courtMap;
    QMap<QString, QStringList> *NotificationsMap;
    QString currentUserId;
    bool isCurrentUserVIP = false;

signals:
    void courtBooked();
};

#endif // BOOKCOURT_H
