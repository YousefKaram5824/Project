#include "SearchManager.h"
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QDebug>
#include <QFile>
#include <QTextStream>

SearchManager::SearchManager(QTableWidget *courtTable,
                             QComboBox *locationComboBox,
                             QDateEdit *dateEdit,
                             QTimeEdit *timeEdit,
                             QObject *parent)
    : QObject(parent)
    , m_courtTable(courtTable)
    , m_locationComboBox(locationComboBox)
    , m_dateEdit(dateEdit)
    , m_timeEdit(timeEdit)
{
    loadCourtsFromFile();
    insertLocations();
}

void SearchManager::loadCourtsFromFile()
{
    QFile file("Y:/Final Project/courts");
    //"E:/Project/courts" PATH of Habiba
    //"Y:/Final Project/courts" PATH of keko
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open courts file for reading";
        return;
    }

    QTextStream in(&file);
    m_courts.clear();

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty()) continue;

        QStringList parts = line.split(", ");
        if (parts.size() >= 5) {
            Court court;
            court.name = parts[1];
            court.location = parts[2];
            court.date = QDate::fromString(parts[3], "yyyy-MM-dd");
            court.time = QTime::fromString(parts[4], "HH:mm");
            court.isBooked = (parts.size() > 5 && parts[5] == "1");
            m_courts.append(court);
        }
    }

    file.close();
    updateTable(m_courts);
}

void SearchManager::insertLocations()
{
    QSet<QString> locations;
    for (const Court &court : m_courts) {
        locations.insert(court.location);
    }

    m_locationComboBox->clear();
    m_locationComboBox->addItem("All Locations");
    for (const QString &location : locations) {
        m_locationComboBox->addItem(location);
    }
}

void SearchManager::searchCourts(const QString& location, const QDate& date, const QTime& time)
{
    QList<Court> filteredCourts;

    for (const Court& court : m_courts) {
        bool matchesLocation = (location == "All Locations" || court.location == location);
        bool matchesDate = (date.isNull() || court.date == date);
        bool matchesTime = (time.isNull() || court.time == time);

        if (matchesLocation && matchesDate && matchesTime) {
            filteredCourts.append(court);
        }
    }

    updateTable(filteredCourts);
}

void SearchManager::updateTable(const QList<Court>& courts)
{
    m_courtTable->setRowCount(0);

    for (const Court& court : courts) {
        int row = m_courtTable->rowCount();
        m_courtTable->insertRow(row);
        m_courtTable->setItem(row, 0, new QTableWidgetItem(court.name));
        m_courtTable->setItem(row, 1, new QTableWidgetItem(court.location));
        m_courtTable->setItem(row, 2, new QTableWidgetItem(court.date.toString("yyyy-MM-dd")));
        m_courtTable->setItem(row, 3, new QTableWidgetItem(court.time.toString("HH:mm")));
        m_courtTable->setItem(row, 4, new QTableWidgetItem(court.isBooked ? "Booked" : "Available"));
    }
}
