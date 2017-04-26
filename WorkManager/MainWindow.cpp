#include <QDebug>
#include <QSettings>
#include <QAction>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "TreeModel.h"
#include "ProxyModel.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "WorkManager", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  if (m_settings->contains("headerState"))
  {
    ui->treeView->header()->restoreState(m_settings->value("headerState").toByteArray());
  }

  m_treeModel = new TreeModel(this);
  m_proxyModel = new ProxyModel(this);

  m_proxyModel->setSourceModel(m_treeModel);

  ui->treeView->setModel(m_proxyModel);
  ui->treeView->expandAll();

  // call this connect after setting the model!
  connect(ui->treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onTreeViewSelectionChanged);

  /*ui->treeView->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->treeView->setDragEnabled(true);
  ui->treeView->setAcceptDrops(true);
  ui->treeView->setDropIndicatorShown(true);*/

  /*m_actionNew = new QAction(tr("add new item"), this);
  //m_actionNew->setShortcut(QKeySequence::New, QKeySequence::Open);
  //m_actionNew->setShortcut(Qt::Key_Control + Qt::Key_N);
  m_actionNew->setShortcut(QString("Strg+N"));
  connect(m_actionNew, &QAction::triggered, this, &MainWindow::addNewItem);*/
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("headerState", ui->treeView->header()->saveState());

  delete m_treeModel;
  delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString& searchString)
{
  m_proxyModel->setSearchString(searchString);
}

void MainWindow::onTreeViewSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
  if (!deselected.isEmpty())
  {
    QModelIndex deselectedIndex = m_proxyModel->mapSelectionToSource(deselected).indexes().first();

    TreeItem *item = static_cast<TreeItem*>(deselectedIndex.internalPointer());
    item->toDoItem()->setDescription(ui->plainTextEdit->toPlainText());
  }

  if (!selected.isEmpty())
  {
    QModelIndex selectedIndex = m_proxyModel->mapSelectionToSource(selected).indexes().first();

    TreeItem *item = static_cast<TreeItem*>(selectedIndex.internalPointer());
    ui->plainTextEdit->setPlainText(item->toDoItem()->description());
  }
}

void MainWindow::addNode(const QModelIndex &modelIndexParent)
{
  TreeItem *item = static_cast<TreeItem*>(modelIndexParent.internalPointer());

  if (m_treeModel->columnCount(modelIndexParent) == 0)
  {
    if (!m_treeModel->insertColumn(0, modelIndexParent))
    {
      return;
    }
  }

  if (!m_treeModel->insertRow(0, modelIndexParent))
  {
    return;
  }

  /*for (int column = 0; column < m_treeModel->columnCount(index); ++column)
  {
    QModelIndex child = m_treeModel->index(0, column, index);
    m_treeModel->setData(child, QVariant("[No data]"), Qt::EditRole);
    if (!m_treeModel->headerData(column, Qt::Horizontal).isValid())
    {
      m_treeModel->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);
    }
  }*/

  ui->treeView->selectionModel()->setCurrentIndex(m_proxyModel->mapFromSource(m_treeModel->index(0, 0, modelIndexParent)), QItemSelectionModel::ClearAndSelect);
}

void MainWindow::on_actionAddChild_triggered()
{
  qDebug() << "actionAddChild";

  QModelIndex index = m_proxyModel->mapToSource(ui->treeView->selectionModel()->currentIndex());

  addNode(index);
}

void MainWindow::on_actionAddSibling_triggered()
{
  qDebug() << "actionAddSibling";

  QModelIndex index = m_proxyModel->mapToSource(ui->treeView->selectionModel()->currentIndex());

  addNode(index.parent());
}

void MainWindow::on_actionMoveUp_triggered()
{
  qDebug() << "actionMoveUp";
}

void MainWindow::on_actionMoveDown_triggered()
{
  qDebug() << "actionMoveDown";
}

void MainWindow::on_actionMoveLeft_triggered()
{
  qDebug() << "actionMoveLeft";
}

void MainWindow::on_actionMoveRight_triggered()
{
  qDebug() << "actionMoveRight";
}

void MainWindow::on_actionDelete_triggered()
{
  qDebug() << "actionDelete";

  QModelIndex index = ui->treeView->selectionModel()->currentIndex();
  if (m_treeModel->removeRow(index.row(), index.parent()))
  {
      //updateActions();
  }
}

void MainWindow::on_pushButton_clicked()
{
  ui->plainTextEditTreeContent->clear();
  ui->plainTextEditTreeContent->setPlainText(m_treeModel->toString());
}
