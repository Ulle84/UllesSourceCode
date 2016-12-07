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
  enum Attributes
  {
    Title = 0,
    DueDate
  };

  ToDoItem();
  ToDoItem(const QString& title, const QDate& dueDate = QDate());

  QVariant data(int column) const;

  QString title() const;
  void setTitle(const QString& title);

  QString description() const;
  void setDescription(const QString& desciption);

  QDate dueDate() const;
  void setDueDate(const QDate& dueDate);

  static QStringList nameOfAttributes();
  static int numberOfAttributes();

private:
  QString m_title;
  QString m_description;
  QDate m_dueDate;
  static QStringList m_attributes;
};

#endif // TODOITEM_H
