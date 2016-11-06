#include "ToDoItem.h"

ToDoItem::ToDoItem()
{

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
