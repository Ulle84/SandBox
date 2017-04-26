#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->label->installEventFilter(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

bool MainWindow::eventFilter(QObject* target, QEvent* event)
{
  if (target == ui->label)
  {
    if (event->type() == QEvent::MouseButtonPress)
    {
      QMessageBox messageBox;
      messageBox.setText("See - I told you!");
      messageBox.exec();
      return true;
    }
  }

  return QMainWindow::eventFilter(target, event);
}
