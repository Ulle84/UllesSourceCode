#ifndef CODECLEANER_H
#define CODECLEANER_H

#include <QChar>
#include <QString>

#include "Options.h"

class CodeCleaner
{
public:
  CodeCleaner(QString string);

  void process();
  QString getCode();

  void setOptions(const Options& options);

private:
  void removeDoubleEmptyLines();
  void removeEmptyLinesBeforeClosingBracket();
  void removeEmptyLinesAfterOpeningBracket();
  void removeLineDelimiters();
  void removeUnnecessaryNamespaceStuff();
  void removeUnnecessaryStuff();
  void moveCommaToRightPlace();

  QString createSpaceString(unsigned int length);
  QString createString(QString characters, unsigned int length);

  QString m_string;

  Options m_options;
};

#endif // CODECLEANER_H
