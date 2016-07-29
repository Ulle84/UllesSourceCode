#ifndef CODEHELPER_H
#define CODEHELPER_H

#include <QString>

class CodeHelper
{
public:
  static QString nullPointer();
  static QString interfaceName(const QString& className);
  static QString classNameToHeader(const QString& className, bool useBrackets = false);
  // TODO define indent globally
  // TODO define memberPrefix/Postfix globally
};

#endif // CODEHELPER_H
