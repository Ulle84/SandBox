#include <QDateTime>
#include <QDebug>
#include <QModelIndex>

#include "ProxyModel.h"
#include "TreeItem.h"

ProxyModel::ProxyModel(QObject* parent) :
  QSortFilterProxyModel(parent)
{

}

bool ProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
  QList<TreeItem*> treeItems;

  treeItems.append(static_cast<TreeItem*>(sourceModel()->index(sourceRow, 0, sourceParent).internalPointer()));

  while (!treeItems.isEmpty())
  {
    if (treeItems.first()->data(0).toString().contains(m_searchString, Qt::CaseInsensitive))
    {
      return true;
    }
    else
    {
      if (treeItems.first()->childCount() > 0)
      {
        treeItems.append(treeItems.first()->childItems());
      }
    }
    treeItems.removeFirst();
  }

  return false;
}

void ProxyModel::setSearchString(const QString& searchString)
{
  m_searchString = searchString;
  setFilterFixedString(searchString);
}

bool ProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
  return sourceModel()->data(left).toString() < sourceModel()->data(right).toString();
}
