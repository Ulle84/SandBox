#include <QDebug>

#include "ToDoItem.h"

ToDoItem::ToDoItem()
{

}

ToDoItem::ToDoItem(const QString &title, const QString& description, const QDate &dueDate) :
  m_title(title),
  m_description(description),
  m_dueDate(dueDate)
{
}

QVariant ToDoItem::data(int column) const
{
  if (column == Title)
  {
    return m_title;
  }
  else if (column == DueDate)
  {
    return m_dueDate.toString("yyyy-MM-dd");
  }
  else
  {
    return QVariant();
  }
}

bool ToDoItem::setData(int column, const QVariant& data)
{
  if (column == Title)
  {
    m_title = data.toString();
  }
  else if (column == DueDate)
  {
    m_dueDate = data.toDate();
  }
  else
  {
    // column does not exist
    return false;
  }

  return true;
}

QString ToDoItem::title() const
{
  return m_title;
}

void ToDoItem::setTitle(const QString &title)
{
  m_title = title;
}

QString ToDoItem::description() const
{
  return m_description;
}

void ToDoItem::setDescription(const QString &desciption)
{
  m_description = desciption;
}

QDate ToDoItem::dueDate() const
{
  return m_dueDate;
}

void ToDoItem::setDueDate(const QDate &dueDate)
{
  m_dueDate = dueDate;
}
