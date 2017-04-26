#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("blub.sqlite"); // path to database

    if (mydb.open())
    {
        QMessageBox mb;
        mb.setText("database opened");
        mb.exec();
    }

    QSqlQuery query;
    /*query.exec("create table person (id int primary key, "
                    "firstname varchar(20), lastname varchar(20))");

    query.exec("insert into person values(101, 'Danny', 'Young')");
    query.exec("insert into person values(102, 'Christine', 'Holand')");
    query.exec("insert into person values(103, 'Lars', 'Gordon')");
    query.exec("insert into person values(104, 'Roberto', 'Robitaille')");
    query.exec("insert into person values(105, 'Maria', 'Papadopoulos')");*/

    QStringList allTables = mydb.tables();
    qDebug() << "all table names: \n" << allTables.join("\n");

    query.exec("SELECT * FROM person");
    int colFirstName = query.record().indexOf("firstname");
    int colLastName = query.record().indexOf("lastname");

    while (query.next())
    {
        QString firstname = query.value(colFirstName).toString();
        QString lastname = query.value(colLastName).toString();
        qDebug() << "person: " << firstname << " " << lastname;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
