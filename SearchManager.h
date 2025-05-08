#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H

#include <QList>
#include <QMap>
#include "court.h"

class SearchManager
{
public:
    SearchManager(QMap<int, Court> &courts);

    QList<Court> searchAll() const;
    QList<Court> filterCourts(const QString &location, const QDate &date, const QTime &time) const;
    Court findClosestAvailable(const QString &location, const QDate &date, const QTime &time) const;

private:
    QMap<int, Court> &courtMap;
};

#endif // SEARCHMANAGER_H
