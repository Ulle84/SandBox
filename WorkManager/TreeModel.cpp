// see http://doc.qt.io/qt-4.8/qt-itemviews-simpletreemodel-example.html

#include <QString>
#include <QDebug>

#include "TreeModel.h"
#include "ToDoItem.h"


TreeModel::TreeModel(QObject *parent)
  : QAbstractItemModel(parent)
{
  m_rootItem = new TreeItem(new ToDoItem());
  setupModelData(m_rootItem);
}

TreeModel::~TreeModel()
{
  delete m_rootItem;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent))
  {
    return QModelIndex();
  }

  TreeItem *parentItem;

  if (!parent.isValid())
  {
    parentItem = m_rootItem;
  }
  else
  {
    parentItem = static_cast<TreeItem*>(parent.internalPointer());
  }

  TreeItem *childItem = parentItem->child(row);
  if (childItem)
  {
    return createIndex(row, column, childItem);
  }
  else
  {
    return QModelIndex();
  }
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
  if (!index.isValid())
  {
    return QModelIndex();
  }

  TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
  TreeItem *parentItem = childItem->parent();

  if (parentItem == m_rootItem)
  {
    return QModelIndex();
  }

  return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
  TreeItem *parentItem;
  if (parent.column() > 0)
  {
    return 0;
  }

  if (!parent.isValid())
  {
    parentItem = m_rootItem;
  }
  else
  {
    parentItem = static_cast<TreeItem*>(parent.internalPointer());
  }

  return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
  if (parent.isValid())
  {
    return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
  }
  else
  {
    return m_rootItem->columnCount();
  }
}

Qt::DropActions TreeModel::supportedDropActions() const
{
  // TODO copy?
  return  Qt::CopyAction | Qt::MoveAction;
}

QString TreeModel::toString()
{
  return m_rootItem->toString(0);
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
  /*if (!index.isValid())
  {
    return 0;
  }

  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;*/

  /*Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

       if (index.isValid())
           return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
       else
           return Qt::ItemIsDropEnabled | defaultFlags;*/

  if (!index.isValid())
  {
    return 0;
  }

  return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }

  if (role == Qt::DisplayRole)
  {
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    return item->data(index.column());
  }
  else
  {
    return QVariant();
  }
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
  {
    if (section == ToDoItem::Title)
    {
      return tr("title");
    }
    else if (section == ToDoItem::DueDate)
    {
      return tr("due date");
    }
  }

  return QVariant();
}

void TreeModel::setupModelData(TreeItem *parent)
{
  TreeItem* a = new TreeItem(new ToDoItem("alpha", "adesc"), parent);
  TreeItem* a1 = new TreeItem(new ToDoItem("alpha1", "a1desc"), a);
  TreeItem* a2 = new TreeItem(new ToDoItem("alpha2", "a2desc"), a);
  TreeItem* a3 = new TreeItem(new ToDoItem("alpha3", "a3desc"), a);

  TreeItem* b = new TreeItem(new ToDoItem("beta", "bdesc"), parent);
  TreeItem* b1 = new TreeItem(new ToDoItem("beta1", "b1desc"), b);
  TreeItem* b2 = new TreeItem(new ToDoItem("beta2", "b2desc"), b);
  TreeItem* b3 = new TreeItem(new ToDoItem("beta3", "b3desc"), b);
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex& parent)
{
  TreeItem *parentItem = getItem(parent);

  beginInsertRows(parent, position, position + rows - 1);
  bool success = parentItem->insertChildren(position, rows, m_rootItem->columnCount());
  endInsertRows();

  return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex& parent)
{
  qDebug() << "removeRows own impl";

  TreeItem *parentItem = getItem(parent);
  bool success = true;

  beginRemoveRows(parent, position, position + rows - 1);
  success = parentItem->removeChildren(position, rows);
  endRemoveRows();

  return success;
}

TreeItem* TreeModel::getItem(const QModelIndex &index) const
{
  if (index.isValid())
  {
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    if (item)
    {
      return item;
    }
  }

  return m_rootItem;
}
