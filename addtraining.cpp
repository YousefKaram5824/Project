#include "addtraining.h"
#include <QMessageBox>
#include "ui_addtraining.h"

addTraining::addTraining(QMap<QString, training> &trainingsMapRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addTraining)
    , trainingsMap(trainingsMapRef)
{
    ui->setupUi(this);

    ui->namecomboBox->clear();
    for (const QString &name : trainingsMap.keys()) {
        ui->namecomboBox->addItem(name);
    }

    connect(ui->namecomboBox, &QComboBox::currentTextChanged,
            this, &addTraining::loadTrainingData);

    ui->namecomboBox->setCurrentIndex(-1);
}

addTraining::~addTraining()
{
    delete ui;
}

void addTraining::on_pushButton_3_clicked()
{
    QString trainingN = ui->namecomboBox->currentText().trimmed();
    QString coname = ui->coachNamelineEdit->text().trimmed();
    QString capText = ui->capacitylineEdit->text().trimmed();
    QString durationText = ui->DtimlineEdit->text().trimmed();
    QTime Sttime = ui->StimeEdit->time();


    if (trainingN.isEmpty() || coname.isEmpty() || capText.isEmpty() || durationText.isEmpty()) {
        QMessageBox::warning(this, "Missing Data", "Please fill in all the fields.");
        return;
    }

    QList<QString> selectedDays;
    QList<QCheckBox*> checkboxes = {
        ui->checkBox_8, ui->checkBox_11, ui->checkBox_12,
        ui->checkBox_13, ui->checkBox_14, ui->checkBox_9, ui->checkBox_10
    };
    for (QCheckBox *cb : checkboxes) {
        if (cb->isChecked())
            selectedDays << cb->text();
    }

    if (selectedDays.isEmpty()) {
        QMessageBox::warning(this, "Missing Days", "Please select at least one day.");
        return;
    }

    int cap = capText.toInt();
    int Dtime = durationText.toInt();

    training newtraining;
    newtraining.name = trainingN;
    newtraining.capacity = cap;
    newtraining.Stime = Sttime;
    newtraining.duration_time = Dtime;
    newtraining.days = selectedDays;
    newtraining.assigned_coach = coname;

    bool isUpdate = trainingsMap.contains(trainingN);
    trainingsMap.insert(trainingN, newtraining);

    if (ui->namecomboBox->findText(trainingN) == -1)
        ui->namecomboBox->addItem(trainingN);


    ui->namecomboBox->setCurrentIndex(-1);
    ui->capacitylineEdit->clear();
    ui->coachNamelineEdit->clear();
    ui->DtimlineEdit->clear();
    ui->StimeEdit->setTime(QTime::currentTime());
    for (QCheckBox *cb : checkboxes)
        cb->setChecked(false);

    if (isUpdate)
        QMessageBox::information(this, "Updated", "Training updated successfully.");
    else
        QMessageBox::information(this, "Added", "New training added successfully.");
}

void addTraining::loadTrainingData(const QString &trainingName)
{
    if (!trainingsMap.contains(trainingName))
        return;

    const training &t = trainingsMap[trainingName];

    ui->capacitylineEdit->setText(QString::number(t.capacity));
    ui->coachNamelineEdit->setText(t.assigned_coach);
    ui->DtimlineEdit->setText(QString::number(t.duration_time));
    ui->StimeEdit->setTime(t.Stime);

    QList<QCheckBox*> checkboxes = {
        ui->checkBox_8, ui->checkBox_11, ui->checkBox_12,
        ui->checkBox_13, ui->checkBox_14, ui->checkBox_9, ui->checkBox_10
    };
    for (QCheckBox *cb : checkboxes)
        cb->setChecked(false);

    for (const QString &day : t.days) {
        for (QCheckBox *cb : checkboxes) {
            if (cb->text() == day) {
                cb->setChecked(true);
                break;
            }
        }
    }
}

void addTraining::on_DeletepushButton_clicked()
{
    QString trainingName = ui->namecomboBox->currentText().trimmed();

    if (trainingName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a training to delete.");
        return;
    }

    if (!trainingsMap.contains(trainingName)) {
        QMessageBox::warning(this, "Error", "Training not found.");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm Deletion",
        "Are you sure you want to delete training: " + trainingName + "?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        trainingsMap.remove(trainingName);
        ui->namecomboBox->removeItem(ui->namecomboBox->currentIndex());


        ui->capacitylineEdit->clear();
        ui->coachNamelineEdit->clear();
        ui->DtimlineEdit->clear();
        ui->StimeEdit->setTime(QTime::currentTime());

        QList<QCheckBox*> checkboxes = {
            ui->checkBox_8, ui->checkBox_11, ui->checkBox_12,
            ui->checkBox_13, ui->checkBox_14, ui->checkBox_9, ui->checkBox_10
        };
        for (QCheckBox *cb : checkboxes)
            cb->setChecked(false);

        ui->namecomboBox->setCurrentIndex(-1);
        QMessageBox::information(this, "Deleted", "Training deleted successfully.");
    }
}
