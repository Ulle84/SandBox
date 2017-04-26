#include <QDebug>

#include "TreeItem.h"

TreeItem::TreeItem(ToDoItem* toDoItem, TreeItem* parent) :
  m_parentItem(parent),
  m_toDoItem(toDoItem)
{
  if (parent != nullptr)
  {
    parent->appendChild(this);
  }
}

TreeItem::~TreeItem()
{
  delete m_toDoItem;
  qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
  m_childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
  return m_childItems.value(row);
}

QList<TreeItem *> TreeItem::childItems()
{
  return m_childItems;
}

int TreeItem::childCount() const
{
  return m_childItems.count();
}

int TreeItem::row() const
{
  if (m_parentItem)
  {
    return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));
  }

  return 0;
}

int TreeItem::columnCount() const
{
  return ToDoItem::ColumnCount;
}

QVariant TreeItem::data(int column) const
{
  return m_toDoItem->data(column);
}

TreeItem *TreeItem::parent()
{
  return m_parentItem;
}

ToDoItem *TreeItem::toDoItem()
{
  return m_toDoItem;
}

bool TreeItem::insertChildren(int position, int count, int columns)
{
  if (position < 0 || position > m_childItems.size())
  {
    return false;
  }

  for (int row = 0; row < count; ++row)
  {
    TreeItem *item = new TreeItem(new ToDoItem("inserted"), this);
    //m_parentItem->m_childItems.insert(position, item);
    //m_childItems.insert(position, item);
  }

  return true;
}

QString TreeItem::toString(int indentationLevel)
{
  QString string;

  for (int i = 0; i < indentationLevel; ++i)
  {
    string.append("  ");
  }
  string.append(m_toDoItem->title());
  string.append('\n');

  for (auto it = m_childItems.begin(); it != m_childItems.end(); ++it)
  {
    string.append((*it)->toString(indentationLevel + 1));
  }

  return string;
}

bool TreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > m_childItems.size())
    {
        return false;
    }

    for (int row = 0; row < count; ++row)
    {
        delete m_childItems.takeAt(position);
    }

    return true;
}
