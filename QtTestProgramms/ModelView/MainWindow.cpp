#include <QTreeView>
#include <QStandardItemModel>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Model.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  // example 1 - 3 available
  example3();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::selectionChangedSlot(const QItemSelection& newSelection, const QItemSelection& oldSelection)
{
  //get the text of the selected item
  const QModelIndex index = m_treeView->selectionModel()->currentIndex();
  QString selectedText = index.data(Qt::DisplayRole).toString();
  //find out the hierarchy level of the selected item
  int hierarchyLevel=1;
  QModelIndex seekRoot = index;
  while(seekRoot.parent() != QModelIndex())
  {
    seekRoot = seekRoot.parent();
    hierarchyLevel++;
  }
  QString showString = QString("%1, Level %2").arg(selectedText)
      .arg(hierarchyLevel);
  setWindowTitle(showString);
}

void MainWindow::example1()
{
  ui->setupUi(this);
  Model* model = new Model(this);
  ui->tableView->setModel(model);
  ui->treeView->setModel(model);
}

void MainWindow::example2()
{
  QTreeView* treeView = new QTreeView(this);
  setCentralWidget(treeView);
  QStandardItemModel* standardModel = new QStandardItemModel() ;

  QList<QStandardItem *> preparedRow =prepareRow("first", "second", "third");
  QStandardItem *item = standardModel->invisibleRootItem();
  // adding a row to the invisible root item produces a root element
  item->appendRow(preparedRow);

  QList<QStandardItem *> secondRow =prepareRow("111", "222", "333");
  // adding a row to an item starts a subtree
  preparedRow.first()->appendRow(secondRow);

  treeView->setModel(standardModel);
  treeView->expandAll();
}

void MainWindow::example3()
{
  m_treeView = new QTreeView(this);
  setCentralWidget(m_treeView);
  QStandardItemModel* standardModel = new QStandardItemModel() ;
  QStandardItem *rootNode = standardModel->invisibleRootItem();

  //defining a couple of items
  QStandardItem *americaItem = new QStandardItem("America");
  QStandardItem *mexicoItem =  new QStandardItem("Canada");
  QStandardItem *usaItem =     new QStandardItem("USA");
  QStandardItem *bostonItem =  new QStandardItem("Boston");
  QStandardItem *europeItem =  new QStandardItem("Europe");
  QStandardItem *italyItem =   new QStandardItem("Italy");
  QStandardItem *romeItem =    new QStandardItem("Rome");
  QStandardItem *veronaItem =  new QStandardItem("Verona");

  //building up the hierarchy
  rootNode->    appendRow(americaItem);
  rootNode->    appendRow(europeItem);
  americaItem-> appendRow(mexicoItem);
  americaItem-> appendRow(usaItem);
  usaItem->     appendRow(bostonItem);
  europeItem->  appendRow(italyItem);
  italyItem->   appendRow(romeItem);
  italyItem->   appendRow(veronaItem);

  //register the model
  m_treeView->setModel(standardModel);
  m_treeView->expandAll();

  //selection changes shall trigger a slot
  QItemSelectionModel *selectionModel= m_treeView->selectionModel();
  connect(selectionModel, SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
          this, SLOT(selectionChangedSlot(const QItemSelection &, const QItemSelection &)));
}

QList<QStandardItem*> MainWindow::prepareRow(const QString& first, const QString& second, const QString& third)
{
  QList<QStandardItem *> rowItems;
  rowItems << new QStandardItem(first);
  rowItems << new QStandardItem(second);
  rowItems << new QStandardItem(third);
  return rowItems;
}
