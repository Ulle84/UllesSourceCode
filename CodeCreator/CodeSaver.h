#ifndef CODESAVER_H
#define CODESAVER_H

class QString;
class QStringList;

class CodeSaver
{
public:
  CodeSaver();
  bool saveCode(const QString& fileName, const QStringList& content);
};

#endif // CODESAVER_H
