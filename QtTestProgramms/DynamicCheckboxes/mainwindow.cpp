#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QLayoutItem>

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->spinBoxHeight, SIGNAL(valueChanged(int)), this, SLOT(setCheckboxes()));
  connect(ui->spinBoxWidth, SIGNAL(valueChanged(int)), this, SLOT(setCheckboxes()));

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::setCheckboxes()
{
  // ToDo more intelligence - delete not all and rebuild all
  // ToDo remember check state of checkboxes

  int columnCount = ui->gridLayoutCheckboxes->columnCount();
  int rowCount = ui->gridLayoutCheckboxes->rowCount();

  for (int column = 0; column < columnCount; column++)
  {
    for (int row = 0; row < rowCount; row++)
    {
      QLayoutItem* layoutItem = ui->gridLayoutCheckboxes->itemAtPosition(row, column);

      if (layoutItem)
      {
        ui->gridLayoutCheckboxes->removeItem(layoutItem);
        delete layoutItem->widget();
        delete layoutItem;
      }
    }
  }


  columnCount = ui->spinBoxWidth->value();
  rowCount = ui->spinBoxHeight->value();

  for (int column = 0; column < columnCount; column++)
  {
    for (int row = 0; row < rowCount; row++)
    {
      QCheckBox* checkBox = new QCheckBox(this);
      ui->gridLayoutCheckboxes->addWidget(checkBox, row, column);
    }
  }
}
