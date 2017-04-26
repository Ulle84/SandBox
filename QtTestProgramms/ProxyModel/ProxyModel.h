#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>


class ProxyModel : public QSortFilterProxyModel
{
  Q_OBJECT

public:
  ProxyModel(QObject* parent);

  bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
  bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

  void setSearchString(const QString& searchString);

private:
  QString m_searchString;
};

#endif // PROXYMODEL_H
