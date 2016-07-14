#include "StringHelper.h"

QString StringHelper::upperCaseFirstLetter(const QString& string)
{
  QString copy = string;

  if (!copy.isEmpty())
  {
    copy[0] = copy[0].toUpper();
  }

  return copy;
}

QString StringHelper::lowerCaseFirstLetter(const QString& string)
{
  QString copy = string;

  if (!copy.isEmpty())
  {
    copy[0] = copy[0].toLower();
  }

  return copy;
}
