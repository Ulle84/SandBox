// reference: Qt Documentation - The State Machine Framework

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stateMachine = new QStateMachine();
    state1 = new QState();
    state2 = new QState();
    state3 = new QState();

    state1->addTransition(ui->pushButton, SIGNAL(clicked()), state2);
    state2->addTransition(ui->pushButton, SIGNAL(clicked()), state3);
    state3->addTransition(ui->pushButton, SIGNAL(clicked()), state1);

    stateMachine->addState(state1);
    stateMachine->addState(state2);
    stateMachine->addState(state3);
    stateMachine->setInitialState(state1);

    state1->assignProperty(ui->label, "text", "In state s1");
    state2->assignProperty(ui->label, "text", "In state s2");
    state3->assignProperty(ui->label, "text", "In state s3");

    stateMachine->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
