#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QPoint>
#include <QMessageBox>
#include <QStringList>

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  file = new QMenu(tr("File"), this);
  QMenu* test = new QMenu("submenu", this);
  FileSave = file->addAction(tr("Save"));
  FileOpen = file->addAction(tr("Open"));
  FileSaveAs = file->addAction(tr("Save as..."));
  QAction* subAction = file->addMenu(test);
  ui->menuBar->addMenu(file);

  service = new QMenu(tr("Service"), this);
  serviceEntry01 = service->addAction(tr("Service Entry 01"));
  ui->menuBar->addMenu(service);

  actionList.append(FileSave);
  actionList.append(FileOpen);
  actionList.append(FileSaveAs);
  actionList.append(serviceEntry01);

  QStringList horizontalHeaderLabels;
  horizontalHeaderLabels.append(tr("menu item"));
  horizontalHeaderLabels.append(tr("enabled"));
  horizontalHeaderLabels.append(tr("visible"));

  for (int i = 0; i < ui->menuBar->actions().length(); i++)
  {
    QMessageBox messageBox;
    messageBox.setText(ui->menuBar->actions().at(i)->text());
    messageBox.exec();
  }

  // { set up table
  ui->tableWidget->setColumnCount(3);
  ui->tableWidget->setHorizontalHeaderLabels(horizontalHeaderLabels);
  ui->tableWidget->setRowCount(actionList.length());

  for (int row = 0; row < actionList.length(); row++)
  {
    for (int column = 0; column < ui->tableWidget->columnCount(); column++)
    {
      QString content;

      if (column == 0)
      {
        //content = actionList.at(row)->menu()->title();
        content = actionList.at(row)->text();
      }
      else
      {
        content = tr("yes");
      }

      QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(content);
      ui->tableWidget->setItem(row, column, tableWidgetItem);
    }
  }

  ui->tableWidget->resizeColumnsToContents();
  ui->tableWidget->resizeRowsToContents();
  // } set up table
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
  if (arg1 == Qt::Checked)
  {
    /*
    service->setEnabled(false);
    FileSave->setVisible(false);
    FileOpen->setEnabled(false);
    */

    for (int i = 0; i < actionList.length(); i++)
    {
      if (ui->tableWidget->item(i, 1)->text() != "yes")
      {
        actionList.at(i)->setEnabled(false);
      }

      if (ui->tableWidget->item(i, 2)->text() != "yes")
      {
        actionList.at(i)->setVisible(false);
      }
    }
  }
  else
  {
    /*service->setEnabled(true);
    FileSave->setVisible(true);
    FileOpen->setEnabled(true);*/

    for (int i = 0; i < actionList.length(); i++)
    {
      actionList.at(i)->setEnabled(true);
      actionList.at(i)->setVisible(true);
    }
  }
}
