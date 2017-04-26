#ifndef TODOITEM_H
#define TODOITEM_H

#include <QString>
#include <QDate>
#include <QStringList>
#include <QVariant>
#include <QDate>

class ToDoItem
{
public:
  enum Column
  {
    Title = 0,
    DueDate,
    ColumnCount // this must always be the last element in enum and must be equal to number of columns!
  };

  ToDoItem();
  ToDoItem(const QString& title, const QString& description = QString(), const QDate& dueDate = QDate::currentDate());

  QVariant data(int column) const;
  bool setData(int column, const QVariant& data);

  QString title() const;
  void setTitle(const QString& title);

  QString description() const;
  void setDescription(const QString& desciption);

  QDate dueDate() const;
  void setDueDate(const QDate& dueDate);

private:
  QString m_title;
  QString m_description;
  QDate m_dueDate;
};

#endif
