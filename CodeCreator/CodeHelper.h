#ifndef CODEHELPER_H
#define CODEHELPER_H

#include <QString>

class CodeHelper
{
public:
  static QString nullPointer();
  static QString interfaceName(const QString& className);
};

#endif // CODEHELPER_H
