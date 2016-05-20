#ifndef CODECLEANER_H
#define CODECLEANER_H

#include <QString>

class CodeCleaner
{
public:
  CodeCleaner(QString string);

  void process();
  QString getCode();

private:
  void removeDoubleEmptyLines();
  void removeEmptyLinesBeforeClosingBracket();
  void removeEmptyLinesAfterOpeningBracket();
  void removeLineDelimiters();

  QString createSpaceString(unsigned int length);

  QString m_string;
};

#endif // CODECLEANER_H
