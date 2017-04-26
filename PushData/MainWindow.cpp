#include <QDebug>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Producer.h"

void callBackFunction(int i)
{
  QThread::msleep(1000);
  qDebug() << i;
}

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  Producer producer;
  producer.registerCallBack(callBackFunction);
  producer.start();
  producer.wait();
}

MainWindow::~MainWindow()
{
  delete ui;
}
