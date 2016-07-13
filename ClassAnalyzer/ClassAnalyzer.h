#ifndef CLASSANALYZER_H
#define CLASSANALYZER_H

#include <QMap>
#include <QList>
#include <QString>
#include <QPair>

#include "Class.h"

class ClassAnalyzer
{
public:
  ClassAnalyzer();
  ~ClassAnalyzer();

  void parseFolder(const QString& folder);

private:
  void removeComments(QString& code);
  void removeSequences(QString& code, const QString& startTag, const QString& endTag, bool removeEndTag = true);
  void parseFile(const QString& fileName);
  void parseClassDeclaration(const QString& classDeclaration);
  QString parseClassName(const QString& classDeclaration);
  QStringList parseBaseClassNames(const QString& baseClasses);
  void parseNamespaces(const QString& code);
  QString getNamespacePrefix(int position);
  QVector<int> positions(const QString& code, const QString& token, bool isRegExp = false);

  QList<Class> m_classes;
  QMap<QString, QPair<int, int>> m_namespaces; // TODO adjust ->
};

#endif // CLASSANALYZER_H
