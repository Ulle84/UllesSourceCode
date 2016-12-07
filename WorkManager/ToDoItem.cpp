#include <QDebug>

#include "ToDoItem.h"

QStringList ToDoItem::m_attributes = QStringList() << "title" << "due date";

ToDoItem::ToDoItem()
{

}

ToDoItem::ToDoItem(const QString &title, const QDate &dueDate) :
  m_title(title),
  m_dueDate(dueDate)
{
}

QVariant ToDoItem::data(int column) const
{
  switch (column)
  {
  case Title:
    return title();

  case DueDate:
    return dueDate().toString("yyyy-MM-dd");
  }
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

QStringList ToDoItem::nameOfAttributes()
{
  return m_attributes;
}

int ToDoItem::numberOfAttributes()
{
  return m_attributes.length();
}
