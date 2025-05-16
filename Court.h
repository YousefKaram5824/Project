#ifndef COURT_H
#define COURT_H
#include <QDate>
#include <QQueue>
#include <QString>
#include <QTime>

struct Court
{
    QString id;
    QString name;
    QString location;
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    bool isBooked = false;
    QString clientId;
    QDate bookingDate;
    QTime bookingTime;
    QQueue<QString> waitingListVIP;
    QQueue<QString> waitingListNormal;

    Court() = default;

    Court(QString id,
          QString name,
          QString location,
          QDate date,
          QTime time,
          bool isBooked,
          QString clientId,
          QDate bookingDate,
          QTime bookingTime)
        : id(id)
        , name(name)
        , location(location)
        , date(date)
        , time(time)
        , isBooked(isBooked)
        , clientId(clientId)
        , bookingDate(bookingDate)
        , bookingTime(bookingTime)

    {}
};

#endif // COURT_H
