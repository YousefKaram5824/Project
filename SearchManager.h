/*#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H

#include <QObject>
#include <QTableWidget>
#include <QComboBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QFile>
#include <QTextStream>
#include "Court.h"

class SearchManager : public QObject
{
    Q_OBJECT

public:
    explicit SearchManager(QTableWidget* courtTable, 
                         QComboBox* locationComboBox,
                         QDateEdit* dateEdit,
                         QTimeEdit* timeEdit,
                         QObject *parent = nullptr);

    void insertLocations();
    void searchCourts(const QString& location, const QDate& date, const QTime& time);
    void updateTable(const QList<Court>& courts);
    void loadCourtsFromFile();

private:
    QTableWidget* m_courtTable;
    QComboBox* m_locationComboBox;
    QDateEdit* m_dateEdit;
    QTimeEdit* m_timeEdit;
    QList<Court> m_courts;
};

#endif // SEARCHMANAGER_H
*/
