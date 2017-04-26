#include <QBrush>
#include <QDebug>
#include <QFont>
#include <QTime>
#include <QTimer>

#include "Model.h"

Model::Model(QObject *parent)
  :QAbstractTableModel(parent)
{
  /*QTimer* timer = new QTimer(this);
  timer->setInterval(1000);
  connect(timer, SIGNAL(timeout()) , this, SLOT(timerHit()));
  timer->start();*/

  for (int r = 0; r < ROWS; ++r)
  {
    for (int c = 0; c < COLS; ++c)
    {
      m_gridData[r][c] = QString("row %1 col %2").arg(r).arg(c);
    }
  }
}

int Model::rowCount(const QModelIndex& parent) const
{
  return ROWS;
}

int Model::columnCount(const QModelIndex& parent) const
{
  return COLS;
}

QVariant Model::data(const QModelIndex& index, int role) const
{
  //return dataReadOnly(index, role);
  //return dataReadOnlyWithRoles(index, role);
  //return dataReadOnlyTime(index, role);
  return dataFromArray(index, role);
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole)
  {
    if (orientation == Qt::Horizontal) {
      switch (section)
      {
      case 0:
        return QString("first");
      case 1:
        return QString("second");
      case 2:
        return QString("third");
      }
    }
  }
  return QVariant();
}

bool Model::setData(const QModelIndex& index, const QVariant& value, int role)
{
  if (role == Qt::EditRole)
  {
    //save value from editor to member m_gridData
    m_gridData[index.row()][index.column()] = value.toString();
    //for presentation purposes only: build and emit a joined string
    QString result;
    for(int row= 0; row < ROWS; row++)
    {
      for(int col= 0; col < COLS; col++)
      {
        result += m_gridData[row][col] + " ";
      }
    }
    emit editCompleted( result );
    emit dataChanged(index, index);
  }
  return true;
}

Qt::ItemFlags Model::flags(const QModelIndex& index) const
{
  return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}

QVariant Model::dataReadOnly(const QModelIndex& index, int role) const
{
  if (role == Qt::DisplayRole)
  {
    return QString("Row%1, Column%2")
        .arg(index.row() + 1)
        .arg(index.column() +1);
  }
  return QVariant();
}

QVariant Model::dataReadOnlyWithRoles(const QModelIndex& index, int role) const
{
  int row = index.row();
  int col = index.column();
  // generate a log message when this method gets called
  qDebug() << QString("row %1, col%2, role %3")
              .arg(row).arg(col).arg(role);

  switch(role){
  case Qt::DisplayRole:
    if (row == 0 && col == 1) return QString("<--left");
    if (row == 1 && col == 1) return QString("right-->");

    return QString("Row%1, Column%2")
        .arg(row + 1)
        .arg(col +1);
    break;
  case Qt::FontRole:
    if (row == 0 && col == 0) //change font only for cell(0,0)
    {
      QFont boldFont;
      boldFont.setBold(true);
      return boldFont;
    }
    break;
  case Qt::BackgroundRole:

    if (row == 1 && col == 2)  //change background only for cell(1,2)
    {
      QBrush redBackground(Qt::red);
      return redBackground;
    }
    break;
  case Qt::TextAlignmentRole:

    if (row == 1 && col == 1) //change text alignment only for cell(1,1)
    {
      return Qt::AlignRight + Qt::AlignVCenter;
    }
    break;
  case Qt::CheckStateRole:

    if (row == 1 && col == 0) //add a checkbox to cell(1,0)
    {
      return Qt::Checked;
    }
  }
  return QVariant();
}

QVariant Model::dataReadOnlyTime(const QModelIndex& index, int role) const
{
  int row = index.row();
  int col = index.column();

  if (role == Qt::DisplayRole)
  {
    if (row == 0 && col == 0)
    {
      return QTime::currentTime().toString();
    }
  }
  return QVariant();
}

QVariant Model::dataFromArray(const QModelIndex& index, int role) const
{

  if (role == Qt::DisplayRole)
  {
    return m_gridData[index.row()][index.column()];
  }
  return QVariant();
}

void Model::timerHit()
{
  //we identify the top left cell
  QModelIndex topLeft = createIndex(0,0);
  //emit a signal to make the view reread identified data
  emit dataChanged(topLeft, topLeft);
}
