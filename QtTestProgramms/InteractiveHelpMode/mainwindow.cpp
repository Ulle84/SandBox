#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QCursor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonActivateHelpMode_clicked()
{
    QWidget *widget = qApp->widgetAt(QCursor::pos());
    QString helpText = widget->property("HelpText").toString();

    QMessageBox messageBox;
    messageBox.setText(helpText);
    messageBox.exec();
}
