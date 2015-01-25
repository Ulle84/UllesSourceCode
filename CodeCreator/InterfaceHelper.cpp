#include <QStringList>
#include <QPlainTextEdit>

#include "InterfaceHelper.h"


QString InterfaceHelper::createVirtualFunctionDeclarations(const QPlainTextEdit* plainTextEdit)
{
  QStringList functions = plainTextEdit->toPlainText().split("\n");

  for (auto it = functions.begin(); it != functions.end(); ++it)
  {
    QString simplified = it->simplified();

    if (simplified.isEmpty())
    {
      continue;
    }
    else
    {
      if (simplified.left(2) == "//")
      {
        *it = simplified.prepend("  ");
      }
      else
      {
        *it = simplified.remove(";").prepend("  virtual ").append(" = 0;");
      }
    }
  }

  return functions.join("\n");
}

QString InterfaceHelper::createFunctionDeclarations(const QPlainTextEdit *plainTextEdit)
{
  QStringList functions = plainTextEdit->toPlainText().split("\n");

  QStringList functionDelarations;

  for (auto it = functions.begin(); it != functions.end(); ++it)
  {
    QString simplified = it->simplified();

    if (simplified.isEmpty() || simplified.left(2) == "//")
    {
      continue;
    }
    else
    {
      *it = simplified.prepend("  ");
      functionDelarations.append(*it);
    }
  }

  return functionDelarations.join("\n");
}
