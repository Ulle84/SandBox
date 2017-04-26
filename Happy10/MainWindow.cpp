#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    analyseDay();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::analyseDay()
{
    const int specialDay = 10;
    QDate today = QDate::currentDate();
    if (today.day() != specialDay)
    {
        ui->lineEdit->setText("nothing to celebrate");
        return;
    }

    QDate rendevousDate(2002, 2, specialDay);
    QDate weddingDay(2011, 9, specialDay);
    QDate linasBirthday(2013, 6, specialDay);

    int rendevousDateMonth = calculateMonth(rendevousDate, today);
    int weddingDayMonth = calculateMonth(weddingDay, today);
    int linasBirthdayMonth = calculateMonth(linasBirthday, today);

    ui->lineEdit->setText(QString("Happy %1/%2/%3!").arg(rendevousDateMonth).arg(weddingDayMonth).arg(linasBirthdayMonth));
}

int MainWindow::calculateMonth(QDate start, QDate end)
{
    if (start.day() != end.day())
    {
        return 0;
    }
    int yearDiff = end.year() - start.year();
    int monthDiff = yearDiff * 12 + end.month() - start.month();
    return monthDiff;
}
