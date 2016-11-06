#include "PhoneBook.h"

PhoneBook::PhoneBook(QObject *parent) :
  QAbstractTableModel(parent)
{
  // TODO remove TestCode
  m_entries.append(PhoneBookEntry("Marielle", "Belitz", "111", "AAA"));
  m_entries.append(PhoneBookEntry("Lina", "Belitz", "222", "BBB"));
  m_entries.append(PhoneBookEntry("Samuel", "Belitz", "333", "CCC"));
}

int PhoneBook::rowCount(const QModelIndex &parent) const
{
  return m_entries.length();
}

int PhoneBook::columnCount(const QModelIndex &parent) const
{
  return PhoneBookEntry::getNumberOfAttributes();
}

QVariant PhoneBook::data(const QModelIndex &index, int role) const
{
  if (role == Qt::DisplayRole)
  {
    switch (index.column())
    {
    case 0:
      return m_entries[index.row()].firstName();

    case 1:
      return m_entries[index.row()].lastName();

    case 2:
      return m_entries[index.row()].phoneNumber();

    case 3:
      return m_entries[index.row()].room();
    }
  }
  return QVariant();
}

QVariant PhoneBook::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole)
  {
    if (orientation == Qt::Horizontal) {
      switch (section)
      {
      case 0:
        return QString("first name");
      case 1:
        return QString("second name");
      case 2:
        return QString("telephone number");
      case 3:
        return QString("room");
      }
    }
  }
  return QVariant();
}

bool PhoneBook::setData(const QModelIndex &index, const QVariant &value, int role)
{
  return true;
}

Qt::ItemFlags PhoneBook::flags(const QModelIndex &index) const
{
  return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}

void PhoneBook::readFromFile(const QString &fileName)
{
  // TODO using FileHelper and parse contacts
}
