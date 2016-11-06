#ifndef TODOITEM_H
#define TODOITEM_H

#include <QString>
#include <QDate>

class ToDoItem
{
public:
  ToDoItem();

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

#endif // TODOITEM_H
