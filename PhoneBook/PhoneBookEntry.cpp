#include "PhoneBookEntry.h"

PhoneBookEntry::PhoneBookEntry()
{

}

PhoneBookEntry::PhoneBookEntry(const QString &firstName, const QString &lastName, const QString &phoneNumber, const QString &room) :
  m_firstName(firstName),
  m_lastName(lastName),
  m_phoneNumber(phoneNumber),
  m_room(room)
{

}

QString PhoneBookEntry::firstName()  const
{
  return m_firstName;
}

QString PhoneBookEntry::lastName() const
{
  return m_lastName;
}

QString PhoneBookEntry::phoneNumber() const
{
  return m_phoneNumber;
}

QString PhoneBookEntry::room() const
{
  return m_room;
}

void PhoneBookEntry::setFirstName(const QString &firstName)
{
  m_firstName = firstName;
}

void PhoneBookEntry::setLastName(const QString &lastName)
{
  m_lastName = lastName;
}

void PhoneBookEntry::setPhoneNumber(const QString &phoneNumber)
{
  m_phoneNumber = phoneNumber;
}

void PhoneBookEntry::setRoom(const QString &room)
{
  m_room = room;
}

int PhoneBookEntry::getNumberOfAttributes()
{
  return m_numberOfAttributes;
}
