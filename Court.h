#ifndef COURT_H
#define COURT_H
#include <QString>
#include <QDate>
#include <QTime>

struct Court {
    QString id;
    QString name;
    QString location;
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    bool isBooked = false;

    Court() = default;

    Court(QString id, QString name, QString location, QDate date, QTime time, bool isBooked)
        : id(id), name(name), location(location), date(date), time(time), isBooked(isBooked) {}
};

#endif // COURT_H
