#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , notificationManager(new NotificationManager(this))
    , notificationWindow(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete notificationWindow;
}

void MainWindow::on_notificationbtn_clicked()
{
    if (!notificationWindow) {
        notificationWindow = new NotificationWindow(notificationManager, currentUserId, this);
    }
    notificationWindow->show();
    notificationWindow->raise();
    notificationWindow->activateWindow();
}
