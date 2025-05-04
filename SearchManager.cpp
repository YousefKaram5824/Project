#include "searchmanager.h"
#include "court.h"

SearchManager::SearchManager(QMap<int, Court>& courts) : courtMap(courts) {
}

QList<Court> SearchManager::searchAll() const {
    return courtMap.values();
}

QList<Court> SearchManager::filterCourts(const QString& location, const QDate& date, const QTime& time) const {
    QList<Court> result;
    QString trimmedLocation = location.trimmed();

    for (const Court& court : courtMap) {
        if (court.location.trimmed() == trimmedLocation
            && court.date == date
            && court.time == time
            && !court.isBooked)
        {
            result.append(court);
        }
    }
    return result;
}

Court SearchManager::findClosestAvailable(const QString& location, const QDate& date, const QTime& time) const {
    Court closest;
    qint64 minDiff = LLONG_MAX;

    for (const Court& court : courtMap) {
        if (court.location == location && !court.isBooked) {
            qint64 dateDiff = date.daysTo(court.date);
            qint64 timeDiff = QTime(0, 0).secsTo(time) - QTime(0, 0).secsTo(court.time);
            qint64 totalDiff = qAbs(dateDiff * 86400 + timeDiff);

            if (totalDiff >= 0 && totalDiff < minDiff) {
                minDiff = totalDiff;
                closest = court;
            }
        }
    }

    return closest;
}
