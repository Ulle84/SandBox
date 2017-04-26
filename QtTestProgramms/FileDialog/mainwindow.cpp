#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButton_clicked()
{
  QString title = ui->lineEdit->text();
  QString filter = ui->lineEdit_2->text();
  QFileDialog::getOpenFileName(this, title, "", filter);
  //QFileDialog fileDialog;
  //fileDialog.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
  QString title = ui->lineEdit->text();
  QString filter = ui->lineEdit_2->text();
  QFileDialog::getSaveFileName(this, title, "", filter);
}
