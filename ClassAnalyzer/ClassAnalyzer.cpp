#include <QDebug>
#include <QDirIterator>
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QSettings>
#include <QList>
#include <QPair>

#include "ClassAnalyzer.h"

ClassAnalyzer::ClassAnalyzer()
{

}

ClassAnalyzer::~ClassAnalyzer()
{

}

void ClassAnalyzer::parseFolder(const QString& folder)
{
  //qDebug() << "parsing folder: " << folder;

  QDirIterator it(folder, QStringList() << "*.h", QDir::Files, QDirIterator::Subdirectories);

  while (it.hasNext())
  {
    parseFile(it.next());
  }
}

void ClassAnalyzer::removeComments(QString& code)
{
  // multi-line comments
  removeSequences(code, "/*", "*/");

  // single-line comments
  removeSequences(code, "//", "\n", false);
}

void ClassAnalyzer::removeSequences(QString& code, const QString& startTag, const QString& endTag, bool removeEndTag)
{
  int positionStart = code.indexOf(startTag);
  int positionEnd = -1;

  while (positionStart > -1)
  {
    positionEnd = code.indexOf(endTag, positionStart + 1);

    if (positionStart < positionEnd)
    {
      int length = positionEnd - positionStart;

      if (removeEndTag)
      {
        length += endTag.length();
      }

      code = code.remove(positionStart, length);
    }
    else
    {
      positionStart++; // otherwise we will run in endless loop
    }

    positionStart = code.indexOf(startTag, positionStart);

  }
}

void ClassAnalyzer::parseFile(const QString& fileName)
{
  qDebug() << "parsing file: " << fileName;

  QFile file(fileName);

  if (!file.open(QFile::ReadOnly | QFile::Text))
  {
    qDebug() << "could not open file: " << fileName;
  }

  QTextStream in(&file);
  QString code = in.readAll();

  removeComments(code);
  parseNamespaces(code);

  /*QFile fileOut(fileName + "_removedComments");

  if (!fileOut.open(QFile::WriteOnly | QFile::Text))
  {
    qDebug() << "could not open file: " << fileName;
  }

  QTextStream out(&fileOut);
  out << code;
  fileOut.close();*/

  int position = 0;

  while (position > -1)
  {
    position = code.indexOf(QRegExp("\\sclass\\s"), position + 1);

    if (position > -1)
    {
      position += 5;

      int posNextSemicolon = code.indexOf(";", position);
      int posNextOpeningCurlyBracket = code.indexOf("{", position);
      int posNextClosingRoundBracket = code.indexOf(")", position);
      int posNextClosingAngleBracket = code.indexOf(">", position);
      int posNextColon = code.indexOf(":", position);

      if (posNextOpeningCurlyBracket < 0)
      {
        //qDebug() << "no class body found";
        continue;
      }

      if (posNextSemicolon < posNextOpeningCurlyBracket)
      {
        //qDebug() << "ignore forward declaration, typedefs etc.";
        continue;
      }

      if (posNextClosingRoundBracket > -1 && posNextClosingRoundBracket < posNextOpeningCurlyBracket)
      {
        //qDebug() << "ignore parameter etc.";
        continue;
      }

      if (posNextClosingAngleBracket > -1 && posNextClosingAngleBracket < posNextOpeningCurlyBracket)
      {
        if (posNextColon > -1 && posNextColon < posNextOpeningCurlyBracket)
        {
          if (posNextClosingAngleBracket < posNextColon)
          {
            //qDebug() << "ignore template parameters";
            continue;
          }
        }
        else
        {
          //qDebug() << "ignore template parameters";
          continue;
        }
      }

      QString classDeclaration = code.mid(position, posNextOpeningCurlyBracket - position);
      removeSequences(classDeclaration, "<", ">");

      parseClassDeclaration(classDeclaration.simplified());
    }
  }

  qDebug() << "finished parsing file";
}

void ClassAnalyzer::parseClassDeclaration(const QString& classDeclaration)
{
  //qDebug() << "parsing class declaration: " << classDeclaration;

  QString className;
  QStringList baseClassNames;

  if (classDeclaration.contains(" : "))
  {
    QStringList tokens = classDeclaration.split(" : ", QString::SkipEmptyParts);

    if (tokens.size() != 2)
    {
      return;
    }

    className = parseClassName(tokens.first());
    baseClassNames = parseBaseClassNames(tokens.last());
  }
  else
  {
    className = parseClassName(classDeclaration);
  }

  if (className.isEmpty())
  {
    return;
  }

  //Class c(className);

  //m_classes.append(Class(className));

  QString output = "found class: ";
  output.append(className);

  for (auto it = baseClassNames.begin(); it != baseClassNames.end(); it++)
  {
    if (it == baseClassNames.begin())
    {
      output.append(" : ");
    }
    else
    {
      output.append(", ");
    }
    output.append(*it);
  }

  qDebug() << output;
}

QString ClassAnalyzer::parseClassName(const QString& classDeclaration)
{
  QStringList tokens = classDeclaration.split(' ', QString::SkipEmptyParts);

  if (tokens.isEmpty())
  {
    return QString();
  }

  if (tokens.last().isEmpty())
  {
    return QString();
  }

  return tokens.last();
}

QStringList ClassAnalyzer::parseBaseClassNames(const QString& baseClasses)
{
  QStringList baseClassNames;

  QStringList tokens = baseClasses.split(',', QString::SkipEmptyParts);

  for (auto it = tokens.begin(); it != tokens.end(); it++)
  {
    QString baseClassName = parseClassName(*it);

    if (!baseClassName.isEmpty())
    {
      baseClassNames.append(baseClassName);
    }
  }

  return baseClassNames;
}

void ClassAnalyzer::parseNamespaces(const QString& code)
{
  m_namespaces.clear();

  QVector<int> namespacePositions = positions(code, "\\snamespace\\s", true);
  QVector<int> openingCurlyBracketPositions = positions(code, "{");
  QVector<int> closingCurlyBracketPositions = positions(code, "}");

  QVector<int> allCurlyBracketPositions = openingCurlyBracketPositions;
  allCurlyBracketPositions.append(closingCurlyBracketPositions);

  qSort(allCurlyBracketPositions);

  QMap<int, int> curlyBracketPairs;
  for (int i = 0; i < allCurlyBracketPositions.size(); i++)
  {
    if (openingCurlyBracketPositions.contains(allCurlyBracketPositions[i]))
    {
      int nesting = 1;
      for (int j = i + 1; j < allCurlyBracketPositions.size(); j++)
      {
        if (openingCurlyBracketPositions.contains(allCurlyBracketPositions[j]))
        {
          nesting++;
        }
        else
        {
          nesting--;
        }

        if (nesting == 0)
        {
          curlyBracketPairs[allCurlyBracketPositions[i]] = allCurlyBracketPositions[j];
          break;
        }
      }
    }
  }

  qDebug() << curlyBracketPairs;

  // TODO further development
}

QString ClassAnalyzer::getNamespacePrefix(int position)
{
  QString namespacePrefix;

  return namespacePrefix;
}

QVector<int> ClassAnalyzer::positions(const QString& code, const QString& token, bool isRegExp)
{
  QVector<int> positions;

  int position = -1;

  if (isRegExp)
  {
    position = code.indexOf(QRegExp(token));
  }
  else
  {
    position = code.indexOf(token);
  }

  while (position > -1)
  {
    positions.append(position);

    position++;

    if (isRegExp)
    {
      position = code.indexOf(QRegExp(token), position);
    }
    else
    {
      position = code.indexOf(token, position);
    }
  }

  return positions;
}
