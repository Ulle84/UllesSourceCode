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
