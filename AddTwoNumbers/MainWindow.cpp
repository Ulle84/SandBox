#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QtGui/QMessageBox>

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  correctEnteredValues = 0;
  wrongEnteredValues = 0;

  ui->setupUi(this);
  randomNumberGenerator = new RandomNumberGenerator(1, 10);
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(showNewRandomNumber()));
  timer->start(2000);
  showNewRandomNumber();
  updateStatusBar();
}

MainWindow::~MainWindow()
{
  delete ui;
  delete randomNumberGenerator;
}

void MainWindow::showNewRandomNumber()
{
  ui->label->setText(QString("%1").arg(randomNumberGenerator->getRandomNumber()));
}

void MainWindow::updateStatusBar()
{
  ui->statusBar->showMessage(QString("correct: %1, wrong: %2").arg(correctEnteredValues).arg(wrongEnteredValues));
}

void MainWindow::on_lineEdit_returnPressed()
{
  int value = ui->lineEdit->text().toInt();
  int correctValue = randomNumberGenerator->getSumOfLastTwoRandomNumbers();

  if (value == correctValue)
  {
    correctEnteredValues++;
  }
  else
  {
    wrongEnteredValues++;
  }

  updateStatusBar();
  ui->lineEdit->clear();
}
