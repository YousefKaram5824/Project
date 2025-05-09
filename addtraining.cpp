#include "addtraining.h"
#include <QMessageBox>
#include "ui_addtraining.h"

addTraining::addTraining(QMap<QString, training> &trainingsMapRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addTraining)
    , trainingsMap(trainingsMapRef)
{
    ui->setupUi(this);
    // Clear old items first (optional but good practice)
    ui->namecomboBox->clear();

    // Fill with existing training names
    for (const QString &name : trainingsMap.keys()) {
        ui->namecomboBox->addItem(name);
    }
    connect(ui->namecomboBox, &QComboBox::currentTextChanged,
            this, &addTraining::loadTrainingData);
}

addTraining::~addTraining()
{
    delete ui;
}

void addTraining::on_pushButton_3_clicked()
{
    QString trainingN = ui->namecomboBox->currentText();
    int cap = ui->capacitylineEdit->text().toInt();
    QString coname = ui->coachNamelineEdit->text();
    int Dtime = ui->DtimlineEdit->text().toInt();
    QTime Sttime = ui->StimeEdit->time();

    QList<QString> selectedDays;

    if (ui->checkBox_8->isChecked())
        selectedDays << ui->checkBox_8->text();
    if (ui->checkBox_11->isChecked())
        selectedDays << ui->checkBox_11->text();
    if (ui->checkBox_12->isChecked())
        selectedDays << ui->checkBox_12->text();
    if (ui->checkBox_13->isChecked())
        selectedDays << ui->checkBox_13->text();
    if (ui->checkBox_14->isChecked())
        selectedDays << ui->checkBox_14->text();
    if (ui->checkBox_9->isChecked())
        selectedDays << ui->checkBox_9->text();
    if (ui->checkBox_10->isChecked())
        selectedDays << ui->checkBox_10->text();

    training newtraining;
    newtraining.name = trainingN;
    newtraining.capacity = cap;
    newtraining.Stime = Sttime;
    newtraining.duration_time = Dtime;
    newtraining.days = selectedDays;
    newtraining.assigned_coach = coname;
    trainingsMap.insert(trainingN, newtraining);
    if (ui->namecomboBox->findText(trainingN) == -1) {
        ui->namecomboBox->addItem(trainingN);
    }
/*
    QMap<QString, training>::iterator it;
    for (it = trainingsMap.begin(); it != trainingsMap.end(); ++it) {
        qDebug() << "Training Name:" << it.key();
        qDebug() << "  Capacity:" << it.value().capacity;
        qDebug() << "  Start Time:" << it.value().Stime.toString();
        qDebug() << "  Duration:" << it.value().duration_time;
        qDebug() << "  Days:" << it.value().days;
        qDebug() << "  Coach:" << it.value().assigned_coach;
    }
*/
    QMessageBox::information(this, "Success", "Success");
}

void addTraining::loadTrainingData(const QString &trainingName)
{
    if (!trainingsMap.contains(trainingName))
        return; // No data to load for this name

    const training &t = trainingsMap[trainingName];

    ui->capacitylineEdit->setText(QString::number(t.capacity));
    ui->coachNamelineEdit->setText(t.assigned_coach);
    ui->DtimlineEdit->setText(QString::number(t.duration_time));
    ui->StimeEdit->setTime(t.Stime);

    // Clear all checkboxes first
    QList<QCheckBox*> checkboxes = {
        ui->checkBox_8, ui->checkBox_11, ui->checkBox_12,
        ui->checkBox_13, ui->checkBox_14, ui->checkBox_9, ui->checkBox_10
    };
    for (QCheckBox *cb : checkboxes) {
        cb->setChecked(false);
    }

    // Re-check based on saved days
    for (const QString &day : t.days) {
        for (QCheckBox *cb : checkboxes) {
            if (cb->text() == day) {
                cb->setChecked(true);
                break;
            }
        }
    }
}

