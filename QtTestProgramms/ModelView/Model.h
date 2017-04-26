#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>

const int COLS= 3;
const int ROWS= 2;

class Model : public QAbstractTableModel
{
  Q_OBJECT

public:
  Model(QObject *parent);
  int rowCount(const QModelIndex &parent = QModelIndex()) const ;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
      Qt::ItemFlags flags(const QModelIndex & index) const ;

signals:
    void editCompleted(const QString &);


private slots:
  void timerHit();

private:
  QVariant dataReadOnly(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant dataReadOnlyWithRoles(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant dataReadOnlyTime(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QVariant dataFromArray(const QModelIndex &index, int role = Qt::DisplayRole) const;

   QString m_gridData[ROWS][COLS];  //holds text entered into QTableView
};

#endif // MODEL_H
