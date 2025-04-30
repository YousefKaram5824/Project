#ifndef COURT_H
#define COURT_H
#include <QString>
#include <QDate>
#include <QTime>

struct Court {
    QString id;
    QString name;
    QString location;
    QDate date;
    QTime time;
    bool isBooked;
};
#endif // COURT_H
