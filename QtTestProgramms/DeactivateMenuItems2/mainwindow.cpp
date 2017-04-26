#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QStringList>

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // set column headers
  QStringList headerLabels;
  headerLabels.append(tr("menu item"));
  headerLabels.append(tr("enabled"));
  headerLabels.append(tr("visible"));
  ui->treeWidget->setColumnCount(headerLabels.count());
  ui->treeWidget->setHeaderLabels(headerLabels);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButton_clicked()
{
  ui->treeWidget->clear();
  ui->pushButton->setEnabled(false);
  parseTree(ui->menuBar->actions(), 0);
  ui->pushButton->setEnabled(true);
}

void MainWindow::parseTree(QList<QAction*> actions, QTreeWidgetItem* parent)
{
  for (int i = 0; i < actions.length(); i++)
  {
    QTreeWidgetItem* treeWidgetItem;

    if (parent == 0)
    {
      // top level tree item
      treeWidgetItem = new QTreeWidgetItem(ui->treeWidget);
    }
    else
    {
      treeWidgetItem = new QTreeWidgetItem(parent);
    }

    treeWidgetItem->setText(0, actions.at(i)->text());
    treeWidgetItem->setText(1, tr("yes"));
    treeWidgetItem->setText(2, tr("yes"));


    if (actions.at(i)->menu())
    {
      parseTree(actions.at(i)->menu()->actions(), treeWidgetItem);
    }
  }
}
