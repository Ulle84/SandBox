#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDesktopServices>
#include <QUrl>

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

void MainWindow::on_pushButtonOpen_clicked()
{
   QDesktopServices::openUrl(QUrl::fromLocalFile(ui->lineEdit->text()));
}
