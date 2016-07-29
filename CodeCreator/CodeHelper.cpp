#include <QDebug>

#include "CodeHelper.h"

QString CodeHelper::nullPointer()
{
#if __cplusplus <= 199711L
  return "0";
#else
  return "nullptr";
#endif
}

QString CodeHelper::interfaceName(const QString& className)
{
  QString interfaceName = className;
  if (!interfaceName.endsWith('I'))
  {
    interfaceName.append('I');
  }
  return interfaceName;
}

QString CodeHelper::classNameToHeader(const QString& className, bool useBrackets)
{
  QString header;

  header.append(useBrackets ? "<" : "\"");
  header.append(className);

  if (!useBrackets)
  {
    header.append(".h");
  }

  header.append(useBrackets ? ">" : "\"");



  return header;
}
