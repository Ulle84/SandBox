#include <QDateTime>
#include <QDebug>
#include <QModelIndex>

#include "ProxyModel.h"

ProxyModel::ProxyModel(QObject* parent) :
  QSortFilterProxyModel(parent)
{

}

bool ProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
  //qDebug() << "sourceRow:" << sourceRow;

  QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
  //qDebug() << "index:" << index;

  QVariant data = sourceModel()->data(index);
  //qDebug() << "data:" << data;

  if (!data.toString().contains(filterRegExp()))
  {
    qDebug() << "hide sourceRow:" << sourceRow;
    qDebug() << "indexRow:" << index.row();
    return false;
  }


  return true;
  /*QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
     QModelIndex index1 = sourceModel()->index(sourceRow, 1, sourceParent);
     QModelIndex index2 = sourceModel()->index(sourceRow, 2, sourceParent);

     return (sourceModel()->data(index0).toString().contains(filterRegExp())
             || sourceModel()->data(index1).toString().contains(filterRegExp()))
            && dateInRange(sourceModel()->data(index2).toDate());*/
}

void ProxyModel::setSearchString(const QString& searchString)
{
  setFilterFixedString(searchString);
  //m_searchString = searchString;
  //emit sourceModelChanged();
  //sourceModel()
}

bool ProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
  QVariant leftData = sourceModel()->data(left);
  QVariant rightData = sourceModel()->data(right);

  if (leftData.type() == QVariant::DateTime) {
    return leftData.toDateTime() < rightData.toDateTime();
  } else {
    QRegExp *emailPattern = new QRegExp("([\\w\\.]*@[\\w\\.]*)");

    QString leftString = leftData.toString();
    if(left.column() == 1 && emailPattern->indexIn(leftString) != -1)
      leftString = emailPattern->cap(1);

    QString rightString = rightData.toString();
    if(right.column() == 1 && emailPattern->indexIn(rightString) != -1)
      rightString = emailPattern->cap(1);

    return QString::localeAwareCompare(leftString, rightString) < 0;
  }
}
