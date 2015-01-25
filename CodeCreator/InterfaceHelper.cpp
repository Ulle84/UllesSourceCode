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
        if(simplified.contains(" ("))
        {
          simplified.replace(" (", "(");
        }

        if(simplified.contains(") ;"))
        {
          simplified.replace(") ;", ");");
        }

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
      if(simplified.contains(" ("))
      {
        simplified.replace(" (", "(");
      }

      if(simplified.contains(") ;"))
      {
        simplified.replace(") ;", ");");
      }

      functionDelarations.append(simplified.prepend("  "));
    }
  }

  return functionDelarations.join("\n");
}

QString InterfaceHelper::createFunctionImplementations(const QPlainTextEdit *plainTextEdit, const QString &className)
{
  QStringList functionDeclarations = createFunctionDeclarations(plainTextEdit).split("\n");

  QStringList functionImplementations;

  for (auto it = functionDeclarations.begin(); it != functionDeclarations.end(); ++it)
  {
    QString simplified = it->simplified();

    if (!simplified.contains("("))
    {
      continue;
    }

    QStringList splitted1 = simplified.replace(";", "").split("(");

    if (!splitted1[0].contains(" "))
    {
      continue;
    }

    QStringList splitted2 = splitted1[0].split(" ");
    splitted2[splitted2.length() - 1] = splitted2.last().replace(";", "").prepend("::").prepend(className);

    splitted1[0] = splitted2.join(" ");

    QString functionImplementation = splitted1.join("(") + "\n{\n}";
    functionImplementations.append(functionImplementation);
  }

  return functionImplementations.join("\n\n");
}
