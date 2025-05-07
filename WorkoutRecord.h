#ifndef WORKOUTRECORD_H
#define WORKOUTRECORD_H

#include <QString>
#include <QDateTime>

struct WorkoutRecord {
    QDateTime dateTime;
    QString exerciseType;
    int durationMinutes;
    QString notes;
    QString coachFeedback;
    QString coachId;  // ID of the coach who supervised the workout

    WorkoutRecord() = default;

    WorkoutRecord(const QDateTime& dt, const QString& type, int duration, 
                 const QString& notes = "", const QString& feedback = "", 
                 const QString& coach = "")
        : dateTime(dt), exerciseType(type), durationMinutes(duration),
          notes(notes), coachFeedback(feedback), coachId(coach) {}
};

#endif // WORKOUTRECORD_H 