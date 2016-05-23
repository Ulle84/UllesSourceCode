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

    QString temp = splitted2.join(" ");
    splitted1[0] = temp;
    //splitted1[0] = splitted2.join(" "); // not possible -> linker error: Class.obj:-1: error: LNK2019: unresolved external symbol "__declspec(dllimport) public: class QString & __thiscall QString::operator=(class QString &&)" (__imp_??4QString@@QAEAAV0@$$QAV0@@Z) referenced in function "public: virtual bool __thiscall Class::generate(class QString const &)" (?generate@Class@@UAE_NABVQString@@@Z)

    QString functionImplementation = splitted1.join("(") + "\n{\n  // TODO add implementation";

    if (splitted1[0].contains("bool"))
    {
      functionImplementation += "\n  return false;";
    }
    else if (splitted1[0].contains("int"))
    {
      functionImplementation += "\n  return 0;";
    }
    else if (splitted1[0].contains("double"))
    {
      functionImplementation += "\n  return 0.0;";
    }
    else if (splitted1[0].contains("void"))
    {
      // nothing to do
    }
    else
    {
      functionImplementation += "\n  return 0; // TODO enter correct return value";
    }

    functionImplementation += "\n}";
    functionImplementations.append(functionImplementation);
  }

  return functionImplementations.join("\n\n");
}
