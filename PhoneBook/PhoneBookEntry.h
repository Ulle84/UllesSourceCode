#ifndef PHONEBOOKENTRY_H
#define PHONEBOOKENTRY_H

#include <QString>

class PhoneBookEntry
{
public:
  PhoneBookEntry();
  PhoneBookEntry(const QString& firstName, const QString& lastName, const QString& phoneNumber, const QString& room);

  QString firstName() const;
  QString lastName() const;
  QString phoneNumber() const;
  QString room() const;

  void setFirstName(const QString& firstName);
  void setLastName(const QString& lastName);
  void setPhoneNumber(const QString& phoneNumber);
  void setRoom(const QString& room);

  static int getNumberOfAttributes();

private:
  static const int m_numberOfAttributes = 4;

  QString m_firstName;
  QString m_lastName;
  QString m_phoneNumber;
  QString m_room;
};

#endif // PHONEBOOKENTRY_H
